import numpy as np
import numpy.typing as npt
from matplotlib import pyplot as plt
from typing import Tuple
from PIL import Image
from typing import List


Img = npt.NDArray[np.uint8]

radio_dark="/home/luclaptop/hepia/sem4/visionNum/isc_visnu_public/chapitre_02/radio_dark.png"
gunslinger="/home/luclaptop/hepia/sem4/visionNum/isc_visnu_public/chapitre_01/gunslinger.png"
forest="/home/luclaptop/hepia/sem4/visionNum/isc_visnu_public/chapitre_02/forest.png"
radio_light="/home/luclaptop/hepia/sem4/visionNum/isc_visnu_public/chapitre_02/radio_light.png"

def load_img(path: str) -> Img:
    with Image.open(path) as im:
        m = np.array(im)
        return m


def show_img(img: Img, axis:plt.axis)->None:
    if(len(img.shape)!=3):
        plt.imshow(img,cmap="gray", vmin=0, vmax=255)
    else:
        plt.imshow(img)
    plt.show()


def ex1()->None:
    im1=load_img(radio_dark)
    im2=load_img(gunslinger)
    show_img(im1)
    show_img(im2)


def negatif(img: Img) -> Img:
    m=np.zeros((img.shape[0], img.shape[1]),dtype=np.uint8)
    m = 255 - img
    return m


def ex2()->None:
    show_img(negatif(load_img(forest)))


def seuil(img: Img, valeur: int) -> Img:
    m=np.zeros((img.shape[0], img.shape[1]),dtype=np.uint8)
    for x in range(img.shape[0]):
        for y in range(img.shape[1]):
            m[x,y]=255 if img[x,y] >= valeur else 0
    return m


def ex3()->None:
    show_img(seuil(load_img(forest), 150))


def normalize(img: Img, new_range: Tuple[int, int] = (0, 255)) -> Img:
    m=np.zeros((img.shape[0], img.shape[1]),dtype=np.uint8)
    a=(new_range[1]-new_range[0])/(np.amax(img)-np.amin(img))
    m=(img-np.amin(img))*a+new_range[0]
    return m

def ex4():
    show_img(normalize(load_img(radio_dark)))

def log(img: Img, c: float) -> Img:
    m=np.zeros((img.shape[0], img.shape[1]),dtype=np.uint8)
    m=c*np.log(1 + img)
    return m

def ex5():
    show_img(log(load_img(forest),1.0))

def gamma(img: Img, c: float, g: float) -> Img:
    m=np.zeros((img.shape[0], img.shape[1]),dtype=np.uint8)
    m=c*img**g
    return m

def ex6():
    show_img(gamma(load_img(forest),1.0,4.0))

def hist_1(img: Img) -> List[int]:
    h=[0]*256
    for x in range(img.shape[0]):
        for y in range(img.shape[1]):
            i=img[x,y]
            h[i]+=1
    return h

def hist_2(img: Img) -> List[int]:
    t1, t2 = np.histogram(img, bins=np.arange(256))
    return t1

def hist_cumul(ls:List[int])->List[int]:
    c=[0]*len(ls)
    for i in range(len(ls)):
        for j in range(i):
            c[i]+=ls[j]
    return c

def show_hist_cumul(h:List[int])->None:
    x=range(255)
    fig, ax1 = plt.subplots()
    for i in range(len(h)):
        ax1.bar(i, h[i])

    ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis
    ax2.plot(x, hist_cumul(h))
    plt.show()

def ex7():
    h=hist_1(load_img(forest))
    #for i in range(len(h)):
        #plt.bar(i,h[i])
    #plt.show()

    h1=hist_2(load_img(forest))
    #show_hist_cumul(h1)

    h2=hist_2(negatif(load_img(forest)))
    #show_hist_cumul(h2)

    h3=hist_2(seuil(load_img(forest),150))
    show_hist_cumul(h3)

    h4=hist_2(log(load_img(forest),1.0))
    show_hist_cumul(h4)

    h5=hist_2(gamma(load_img(forest),1.0,4.0))
    show_hist_cumul(h5)

    h6=hist_2(load_img(radio_dark))
    show_hist_cumul(h6)

    h7=hist_2(normalize(load_img(radio_dark)))
    show_hist_cumul(h7)

def equalize(img: Img):
    h_old=hist_cumul(hist_2(img))
    I_max=np.amax(h_old)
    h_new=[]*len(h_old)
    for i in range(len(h_old)):
        h_new=h_old[i]//I_max
    show_hist_cumul(h_new)

def ex8():
    equalize(load_img(radio_light))

def bitwise(img: Img, bit_pos: int) -> Img:
    m=np.zeros((img.shape[0], img.shape[1]),dtype=np.uint8)
    for x in range(img.shape[0]):
        for y in range(img.shape[1]):
            m[x,y] = img[x,y] & (1<<bit_pos)
    return normalize(m)

def ex9():
    show_img(bitwise(load_img(forest), 4))

def main():
    fig, axes = plt.subplots(2,2)
    show_img(img, axes[0][0])
    #ex1()
    #ex2()
    #ex3()
    #ex4()
    #ex5()
    #ex6()
    #ex7()
    #ex8()
    #ex9()

if __name__ == "__main__":
    main()