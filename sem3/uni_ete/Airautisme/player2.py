import pycom
import time

from LIS2HH12 import LIS2HH12
acc = LIS2HH12()

# coding: utf-8
import socket           # Import socket module

SERVER_ADDRESS = "192.168.38.46"  # à modifier pour l'ip de l'ordi qui fait serveur
SERVER_PORT = 30921

s = socket.socket()     # Create a socket object
cpt = 0
s.connect((SERVER_ADDRESS, SERVER_PORT)) # Establish connection
while True : 
    accel = acc.acceleration()
    # print(accel[2])
    # time.sleep(0.1)
    if accel[2] < -3 :
        msg = "ping2"
        s.send(msg.encode("ASCII"))             # Connection initializer
        print("Message : {} sent".format(msg))
        # s.close()  # Close connection to server