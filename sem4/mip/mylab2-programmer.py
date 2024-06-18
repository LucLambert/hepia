'''
Script de programmation pour le bootloader myLab2 du cours MIP

Christian Abegg, HEPIA
'''


import argparse
import binascii
import sys
try:
    import serial
except:
    print("pyserial est requis: pip3 install pyserial")

DEFAULT_PORT = '/dev/ttyUSB0'
BL_ERR_CODE = {'0': 'Success', 1: 'Erreur générale', '2': 'Commande invalide',
               '3': 'Checksum global incorrect', '4': 'Checksum de bloc incorrect',
               '5': 'Erreur lors de l’effacement', '6': 'Erreur lors de l’écriture',
               '7': 'Taille des données invalide', '8': 'Offset invalide',
               '9': 'Argument(s) invalide(s)',
               '99': 'Pas de réponse'}
LPC1769_PARTID = 0x26113f37
LPC1769_FLASH_SIZE = 0x80000
APP_OFFSET = 0x4000
MAX_PROG_SIZE = LPC1769_FLASH_SIZE - APP_OFFSET

def show_error(error_code):
    if error_code != 0:
        return "Erreur {} lors de la commande: {}".format(error_code, BL_ERR_CODE.get(error_code, '---'))

def raise_error(error_code):
    raise Exception(show_error(error_code))

class MyLab2:
    def __init__(self, serialport, verbose=False, timeout=1):
        self.v = verbose
        self.connected = False
        if timeout == -1:
            self.timeout = 0
        elif timeout == 0:
            self.timeout = None
        else:
            self.timeout = timeout
        try:
            self.port = serial.Serial(serialport, baudrate=115200, bytesize=8,
                                      stopbits=1, parity=serial.PARITY_NONE, timeout=self.timeout)

            # Empty buffer in case some char are left in FTDI device
            self.port.timeout = 0.01
            for i in range(16):
                self.port.read()
            self.port.timeout = self.timeout

            self.partid = self.get_part_id()
            self.serial = self.get_serial()
            if self.partid and self.serial:
                self.connected = True

        except Exception as e:
            print("Impossible d'établir la connexion à la carte: {}".format(e))
            self.port = None
            self.connected = False
            if sys.platform.startswith('win') and 'PermissionError' in str(e):
                print("Windows refuse l'accès au port série spécifié. "
                      "Vérifiez que vous n'avez pas d'autres applications qui utilisent ce port.")

    def run_cmd(self, cmd, wait_answer=True):
        send_buf = "{}\r\n".format(cmd).encode()
        if self.v: print(">>> {}".format(send_buf))
        self.port.write(send_buf)
        self.last_cmd = cmd
        if not wait_answer:
            return 0, None
        retcode = self.port.readline()
        if self.v: print("<<< {}".format(retcode))
        retcode = retcode.strip().decode()
        if retcode == "OK":
            # Read answer
            if cmd.startswith("GETID") or cmd.startswith("GETSERIAL"):
                retvalue = self.port.readline()
                if self.v: print("<<< {}".format(retvalue))
                return 0, retvalue.strip().decode()
            else:
                return 0, None
        else:
            if not retcode:
                return '99', None
            err = retcode.split(",")[-1]
            return err, None

    def get_answer(self):
        retcode = self.port.readline()
        if self.v: print("<<< {}".format(retcode))
        retcode = retcode.strip().decode()
        if retcode == "OK":
            return 0, None
        else:
            if not retcode:
                return '99', None
            err = retcode.split(",")[-1]
            return err, None

    def get_part_id(self):
        code, val = self.run_cmd("GETID")
        return val

    def get_serial(self):
        code, val = self.run_cmd("GETSERIAL")
        return val

    def write_program(self, filename, blocksize=1024, fuzzing=False):
        if not self.partid or int(self.partid, 16) != LPC1769_PARTID:
            raise Exception("Part id non reconnu: {}".format(self.partid))
        try:
            with open(filename, 'rb') as file:
                bindata = file.read()
        except Exception as e:
            print("Impossible d'ouvrir le fichier '{}': {}".format(filename, e))
            return

        if len(bindata) > MAX_PROG_SIZE:
            raise Exception("Taille du fichier binaire trop grande: {} (le maximum est de {})".format(len(bindata),
                                                                                                      MAX_PROG_SIZE))

        binfile_crc = binascii.crc32(bindata)
        binfile_length = len(bindata)
        nb_blocs = binfile_length//blocksize + 1
        print("Envoi {} à la myLab2, taille: {}, CRC32: {}, bs={}".format(filename,
                                                                          binfile_length,
                                                                          hex(binfile_crc),
                                                                          blocksize))
        _r, _ = self.run_cmd("PROG,0x{:08x},0x{:08x},0x{:08x}".format(APP_OFFSET, binfile_length, binfile_crc))
        if _r:
            raise_error(_r)
        remaining_size = binfile_length
        position = 0
        for block in range(nb_blocs):
            if remaining_size < blocksize:
                blocksize = remaining_size
            blockcrc = binascii.crc32(bindata[position:(position+blocksize)])
            if self.v:
                print("Envoi bloc {:3d}/{:3d}  (0x{:08x} à 0x{:08x})".format(block+1, nb_blocs,
                                                                             position,
                                                                             position + blocksize - 1))
            else:
                print("\r{:3d}% ".format(int(position / binfile_length * 100)), end='')
            self.run_cmd("DATA,0x{:04x},0x{:08x}".format(blocksize, blockcrc), wait_answer=False)

            # send the data
            blockdata = bindata[position:(position + blocksize)]
            is_fuzz = False
            if fuzzing and block == 3:
                # TODO: Meilleur fuzzing
                blockdata = b'\x02' + bindata[position+1:(position+blocksize)]
                is_fuzz = True
            self.port.write(blockdata)
            _r, _ = self.get_answer()
            if _r:
                print(show_error(_r))
                if is_fuzz:
                    print("Note: le fuzzing était actif sur ce bloc")
                return
            if is_fuzz:
                print("!!! Fuzzing actif lors de l'envoi de ce bloc, mais la carte a quand même validé le CRC !!!")
            # if ok....
            position += blocksize
            remaining_size -= blocksize
            if not self.v:
                print("\r{:3d}% ".format(int(position/binfile_length*100)), end='')

        if not self.v:
            print()
        _r, _ = self.run_cmd("CHECK")
        if _r:
            raise_error(_r)
        else:
            print("Vérification OK")

    def __str__(self):
        if not self.connected:
            return "Pas de connexion au bootloader myLab2-MIP"
        return "Connecté au bootloader myLab2-MIP:\nPartID: {}\nSerial: {}".format(self.partid,
                                                                                      self.serial)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Programmeur pour bootloader myLab2 MIP')
    parser.add_argument('--port', default=DEFAULT_PORT,
                        help='Port série à utiliser pour la communication, "{}" par défaut'.format(DEFAULT_PORT))
    parser.add_argument('--fuzzing', action="store_true",
                        help='Introduit des erreurs lors de la programmation')
    parser.add_argument('--verbose', dest="verbose", action="store_true",
                        help='Mode verbeux')
    parser.add_argument('binfile', default='',
                        help='Programme à écrire, au format bin')
    parser.add_argument('--blksize', default=1024, type=int,
                        help='Taille des blocs lors de l\'envoi')
    parser.add_argument('--timeout', default=2, type=int,
                        help='Durée en secondes après laquelle la réponse doit être reçue. 0=attente infinie')
    args = parser.parse_args()
    ml2 = MyLab2(args.port, verbose=args.verbose, timeout=args.timeout)
    print(ml2)
    if not ml2.connected:
        sys.exit(1)
    try:
        ml2.write_program(args.binfile, blocksize=args.blksize, fuzzing=args.fuzzing)
    except Exception as e:
        print("Erreur lors de la programmation: {}".format(e))
