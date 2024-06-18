import numpy as np
import numpy.typing as npt
from matplotlib import pyplot as plt
from typing import Tuple
from PIL import Image
from typing import List
import time
from random import randint

Img = npt.NDArray[np.uint8]

def load_img(path: str) -> Img:
    with Image.open(path) as im:
        m = np.array(im)
        return m


def show_img(img: Img, axes:plt.axis)->None:
    if(len(img.shape)!=3):
        axes.imshow(img,cmap="gray", vmin=0, vmax=255)
    else:
        axes.imshow(img)

lena=load_img("/home/luclaptop/hepia/sem4/visionNum/isc_visnu_public/chapitre_03/lena.png")
testpattern1024=load_img("/home/luclaptop/hepia/sem4/visionNum/isc_visnu_public/chapitre_03/testpattern1024.png")



def xcorr(img: Img, kernel: Img) -> Img:
    it=np.nditer(img, flags=['multi_index'] ,itershape=img.shape)
    it_k=np.nditer(kernel, flags=['multi_index'], itershape=kernel.shape)
    m=np.zeros(img.shape)
    while it.iternext():
        x, y= it.multi_index
        it_k.reset()
        res=0
        while it_k.iternext():
            i, j= it_k.multi_index
            if (((x-kernel.shape[0]//2+i)>=0) and ((x-kernel.shape[0]//2+i)<img.shape[0])) and (((y-kernel.shape[1]//2+j)>=0) and ((y-kernel.shape[1]//2+j)<img.shape[1])):
                res+=kernel[i][j]*img[x-kernel.shape[0]//2+i][y-kernel.shape[1]//2+j]
        res=0 if res<0 else res
        res=255 if res>255 else res
        m[x][y]=res

    return m.astype(np.uint8)


def blur_avg(img: Img, blur_size: int) -> Img:
    k = 1/(blur_size*blur_size)*np.ones((blur_size,blur_size))
    return xcorr(img, k)

def noise(img: Img, white_p: float, black_p: float) -> Img:
    m=np.zeros(img.shape, dtype=np.uint8)
    for x in range(img.shape[0]):
        for y in range(img.shape[1]):
            r = randint(0,100)
            if r<int(white_p*100):
                m[x,y] = 255
            else:
                m[x,y] = img[x,y]

    for x in range(img.shape[0]):
        for y in range(img.shape[1]):
            r = randint(0,100)
            if r<int(black_p*100):
                m[x,y] = 0
    return m

def blur_median2(img: Img, median_size: int) -> Img:
    res=np.zeros(img.shape)
    it = np.nditer(img, flags=["multi_index"])
    while not it.finished:
        i,j=it.multi_index
        k_half=median_size//2
        roi=img[i-k_half:i+k_half+1,j-k_half:j+k_half+1]
        if roi.shape==(median_size,median_size):
            res[i,j]=np.median(roi)
        it.iternext()

    np.where(res<0,0,res)
    np.where(res>255,255,res)
    return res.astype(np.uint8)

def blur_median(img: Img, median_size: int) -> Img:
    it=np.nditer(img, flags=['multi_index'] ,itershape=img.shape)
    m=np.zeros(img.shape)
    while it.iternext():
        x, y= it.multi_index
        res=0
        offset=median_size//2
        k=img[x-offset:x+offset+1][y-offset:y+offset+1]
        if k.shape==(median_size,median_size):
            res=int(np.median(k))
        m[x][y]=res
    return m.astype(np.uint8)

def ex1():
    convolve_img = xcorr(lena, 1/9*np.ones((3,3)))
    fig, axes = plt.subplots(1,2)
    show_img(lena, axes[0])
    show_img(convolve_img, axes[1])
    plt.show()


def ex2():
    fig, axes = plt.subplots(5,2)
    perf_k = [0,3,7,11]
    perf_t1 = [0]*4
    perf_t2 = [0]*4

    start = time.time()
    show_img(lena, axes[0][0])
    end = time.time()

    perf_t1[0] = end-start

    start = time.time()
    show_img(blur_avg(lena, 3), axes[1][0])
    end = time.time()

    perf_t1[1] = end-start

    start = time.time()
    show_img(blur_avg(lena, 7), axes[2][0])
    end = time.time()

    perf_t1[2] = end-start

    start = time.time()
    show_img(blur_avg(lena, 11), axes[3][0])
    end = time.time()

    perf_t1[3] = end-start

    start = time.time()
    show_img(testpattern1024, axes[0][1])
    end = time.time()

    perf_t2[0] = end-start

    start = time.time()
    show_img(blur_avg(testpattern1024, 3), axes[1][1])
    end = time.time()

    perf_t2[1] = end-start

    start = time.time()
    show_img(blur_avg(testpattern1024, 7), axes[2][1])
    end = time.time()

    perf_t2[2] = end-start

    start = time.time()
    show_img(blur_avg(testpattern1024, 11), axes[3][1])
    end = time.time()

    perf_t2[3] = end-start

    axes[4][0].plot(perf_k, perf_t1)
    axes[4][0].set_xlabel("kernel size")
    axes[4][0].set_ylabel("secondes")

    axes[4][1].plot(perf_k, perf_t2)
    axes[4][1].set_xlabel("kernel size")
    axes[4][1].set_ylabel("secondes")
    plt.show()

def ex4():
    fig, axes = plt.subplots(3)
    show_img(testpattern1024, axes[0])
    noise_pattern = noise(testpattern1024, 0.1, 0.1)
    show_img(noise_pattern, axes[1])
    blur_noise_pattern = blur_avg(noise_pattern, 3)
    show_img(blur_noise_pattern, axes[2])
    plt.show()

def ex5():
    fig, axes = plt.subplots(2,2)
    axes[0][0].set_title("original")
    show_img(testpattern1024, axes[0][0])
    noise_pattern = noise(testpattern1024, 0.1, 0.1)
    axes[0][1].set_title("bruité")
    show_img(noise_pattern, axes[0][1])
    blur_avg_noise_pattern = blur_avg(noise_pattern, 3)
    axes[1][0].set_title("bruité moyenné")
    show_img(blur_avg_noise_pattern, axes[1][0])
    axes[1][1].set_title("bruité médian")
    blur_median_noise_pattern = blur_median2(noise_pattern, 3)
    show_img(blur_median_noise_pattern, axes[1][1])
    plt.show()


def main():
    #ex1()
    #ex2()
    #ex4()
    ex5()

if __name__ == "__main__":
    main()
