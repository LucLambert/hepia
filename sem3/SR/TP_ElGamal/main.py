import math
import hashlib
import random

def Calculate_A(g,a,p):
    return Expo_mod(g,a,p)

def Find_g(p):
    tmp = [1]
    cmp_res = [i for i in range(1,p)]
    for g in range(2, p):
        for i in range(1,p-1):
            tmp.append(Modulo(g**i,p))
        tmp.sort()
        if tmp == cmp_res:
            return g
        else :
            tmp = [1]

def Signature_ElGamal(g, a, p, k, m):
    # 𝑌≡𝑔k𝑚𝑜𝑑(𝑝)
    Y = Expo_mod(g, k, p)
    # 𝑆=(𝑚−𝑎𝑌)k—1𝑚𝑜𝑑(𝑝−1)
    S = (m-a*Y)*Inv_mod(k, p-1)
    S = Modulo(S,p-1)
    return Y, S

def Verif(m, Y, S, pub_key):
    #est vrai⇔𝐴^Y*𝑌^S=𝑔^m 𝑚𝑜𝑑(𝑝)
    Modulo(pub_key[2]**Y*Y**S, pub_key[0])
    n = Expo_mod(pub_key[1], m, pub_key[0])
    return Modulo(pub_key[2]**Y*Y**S, pub_key[0]) == n

def Expo_mod(g,a,p):
    #convertir l'exponent a en binaire
    b = format(a,"b")
    #reverse b
    b = b[::-1]
    res = 1
    for i in range(len(b)):
        if b[i] == "1":
            res *= Modulo(g**2**i, p)
    return Modulo(res, p)

#Crible ératosthène Recursif
def Crible(p):
    tab = [i for i in range(1,p+1)]

    def inner(tab, n):
        for elem in tab:
            if (elem % n == 0) and (elem != n):
                tab.remove(elem)
        n += 1
        if n >= p:
            return tab
        return inner(tab, n)
    
    return inner(tab, 2)

def Modulo(a, b):
    q = a // b
    return a - q*b

def Inv_mod(n, mod):
    a,u,b,v = Euclide_etendue(n, mod)
    if u < 0 :
        return b + u
    return u

def Euclide_etendue(q, r):
    if pgcd(q, r) != 1:
        raise ValueError("les paramètres ne sont pas premiers entre eux, il est impossible de réaliser l'algorithme d' euclide étendu.")
    #init tab
    tab = [q, r, Modulo(q,r), (1,0), q//r, (0,1), (1,0)]

    while Modulo(tab[0],tab[1]) != 0 :
        tab[0] = tab[1]
        tab[1] = tab[2]
        tab[2] = Modulo(tab[0],tab[1])
        tab[3] = tab[5]
        tab[4] = tab[0] // tab[1]
        tab[5] = tab[6]
        tab[6] = (tab[3][0] - tab[4]*tab[5][0], tab[3][1] - tab[4]*tab[5][1])
    return q,  tab[5][0], r, tab[5][1]
        
def pgcd(a, b):
    if b == 0:
        return a
    else:
        result = a % b
        return pgcd(b, result)

def Sign(file):
    # opening and hashing file
    f = open(file, 'r')
    content = f.read()
    f.close()
    md5 = hashlib.md5()
    md5.update(content.encode('utf-8'))
    h = md5.digest()

    # making int value from file 
    m = int.from_bytes(h, "big")
    #m is to big take too much time for Expo Mod
    m %= 10**6
    #sign file 
    #choose p
    tab_of_prim = Crible(500)
    p = tab_of_prim[-1]
    #choose a, g, k
    a = random.randint(1, p)
    g = Find_g(p)
    # k should be prime with p-1 
    while True : 
        k = random.randint(1, p-1)
        if pgcd(k, (p-1)) == 1:
            break

    pub_key = (p, g, Calculate_A(g,a,p))
    Y, S = Signature_ElGamal(g, a, p, k, m)
    return Y, S, m, pub_key

Y, S, m, pub_key = Sign('file.txt')
print("file.txt have been signed")

if Verif(m, Y, S, pub_key):
        print("file.txt have been verified")    
    



