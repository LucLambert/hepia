# -*- coding: utf-8 -*-
"""
Created on 18.2.2022

@author: VP
"""

import numpy as np
import matplotlib.pyplot as plt

S=np.array([1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1])


noisy_signal=np.loadtxt("signal.txt")
num_noisy=np.where(noisy_signal>0, 1, -1)


correl=np.zeros(S.shape[0]*5)
for i in range(correl.shape[0]):
    S_decode = 1 if S[(i//5)%S.shape[0]] == 1 else -1
    correl[i]=S_decode

cor=np.correlate(noisy_signal, correl)

plt.clf()
plt.subplot(3,1,1).plot(noisy_signal)
plt.title("Noisy signal received")

plt.subplot(3,1,2).plot(cor)
plt.title("Correlation with S")

result = np.where(cor == np.amax(cor))
print(result[0])
plt.show()

byte = np.ndarray(8, dtype=np.uint8)
cpt=7

for i in range(0,16*8*5,5):
    byte[cpt] = 1 if num_noisy[i+160]==1 else 0
    cpt -= 1
    if cpt < 0:
        ch=0
        for y in range(8):
            ch += byte[y]*(2**y)
        print(chr(ch),end="")
        cpt = 7

print()

# plt.subplot(3,1,3).plot() 
# plt.title("Recovered bits")