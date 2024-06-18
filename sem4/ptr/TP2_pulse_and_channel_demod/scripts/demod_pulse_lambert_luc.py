import numpy as np
import matplotlib.pyplot as plt
fig, ax = plt.subplots()

fc = 23000
fs = 138000

# signal modulé de référence. Les données d'origine sont: 
# 1,2,3,...,23 codés sur 5 bits (MSB)

s1_mod_n=np.loadtxt("ref_frame_h0_echo_snr100.txt")
s2_mod_n=np.loadtxt("ref_frame_h2_echo_snr7.txt")

wiener1 = np.loadtxt("wiener_filter_h0_echo_snr100.txt")
wiener2 = np.loadtxt("wiener_filter_h2_echo_snr7.txt")

# DEMODULATION
def demodulation(s_mod_n, wiener):

    s_mod_n_cfr = np.zeros(s_mod_n.shape)
    for k in range(s_mod_n.shape[0]):
        s_mod_n_cfr[k]=s_mod_n[k]*np.cos(2*np.pi*fc/fs*k)

    rrc=np.loadtxt("rrc_filter.txt")
    #filtering...
    s_mod_n_lpf = np.convolve(s_mod_n_cfr, rrc)
    s_mod_n_lpf = s_mod_n_lpf[17:s_mod_n_lpf.shape[0]-17]

    s_mod_n_w = np.convolve(s_mod_n_lpf, wiener, mode='valid')

    soft_dec = np.zeros(s_mod_n_w.shape[0]//6)
    cpt=0
    for i in range(0,s_mod_n_w.shape[0],6):
        soft_dec[cpt]=s_mod_n_w[i]
        cpt+=1

    soft_dec_bin = np.where(soft_dec > 0, 1 , 0)
    bits = np.zeros(soft_dec_bin.shape[0]//2)
    for k in range(bits.shape[0]):
        bits[k] = s_mod_n_w[12*k] + s_mod_n_w[12*k+6] > 0

    rgb = np.zeros(bits.shape[0]//5,dtype=np.uint8)
    c = 0
    for b in range(0,bits.shape[0],5):
        bit_0 = int(bits[b])
        bit_1 = int(bits[b+1])
        bit_2 = int(bits[b+2])
        bit_3 = int(bits[b+3])
        bit_4 = int(bits[b+4])
        rgb[c]=bit_0<<4 | (bit_1<<3) | (bit_2<<2) | (bit_3<<1) | bit_4 
        c+=1

    return s_mod_n, s_mod_n_cfr, s_mod_n_lpf, s_mod_n_w, soft_dec, bits, rgb


def display(s_mod_n,s_mod_n_cfr,s_mod_n_lpf,s_mod_n_w,soft_dec,bits):
    plt.figure(1)
    plt.clf()
    plt.plot(s_mod_n)

    plt.figure(2)
    plt.clf()
    plt.subplot(3,1,1)
    plt.plot(s_mod_n_cfr)
    plt.title("Signal after carrier frequency removing")

    plt.subplot(3,1,2)
    spectrum_mod_n_cfr = np.abs(np.fft.fftshift(np.fft.fft(s_mod_n_cfr)))
    plt.title("Spectrum after carrier frequency removing")
    plt.plot(spectrum_mod_n_cfr)

    plt.subplot(3,1,3)
    plt.plot(np.abs(np.fft.fftshift(np.fft.fft(s_mod_n_lpf))))
    plt.title("Spectrum after low-pass filtering")

    plt.figure(3)
    plt.clf()
    plt.subplot(3,1,1)
    plt.plot(s_mod_n_w)
    plt.title("Signal after Wiener filtering")

    plt.subplot(3,1,2)
    plt.plot(s_mod_n_w)
    for i in range(0,s_mod_n_w.shape[0],6):
        plt.scatter(i,soft_dec[i//6],c='r',marker='x')
    plt.title("Soft decisions")


    plt.subplot(3,1,3)
    plt.plot(bits)
    plt.title("Bits recovered")

    plt.show()


if __name__ == "__main__":
    s_mod_n1, s_mod_n_cfr1, s_mod_n_lpf1, s_mod_n_w1, soft_dec1, bits1, rgb1 = demodulation(s1_mod_n,wiener1)
    print("demod values sig1 : ", rgb1)
    display(s_mod_n1,s_mod_n_cfr1,s_mod_n_lpf1,s_mod_n_w1,soft_dec1,bits1)

    s_mod_n2, s_mod_n_cfr2, s_mod_n_lpf2, s_mod_n_w2, soft_dec2, bits2, rgb2 = demodulation(s2_mod_n,wiener2)
    print("demod values sig2 : ", rgb2)
    display(s_mod_n2,s_mod_n_cfr2,s_mod_n_lpf2,s_mod_n_w2,soft_dec2,bits2)

