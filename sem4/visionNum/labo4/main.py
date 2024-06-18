import numpy as np
import numpy.typing as npt
from matplotlib import pyplot as plt
from typing import Tuple
from PIL import Image
from typing import List
import time
from random import randint
from enum import Enum

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

def rgb_to_gray(img: Img) -> Img:
    m=np.zeros((img.shape[0],img.shape[1]))
    for x in range(img.shape[0]):
        for y in range(img.shape[1]):
            m[x][y]=0.2989*img[x][y][0] + 0.5870*img[x][y][1] + 0.1140*img[x][y][2]
    return m.astype(np.uint8)

hotel=rgb_to_gray(load_img("/home/luclaptop/hepia/sem4/visionNum/isc_visnu_public/chapitre_04/hotel.png"))
noisy_hotel=rgb_to_gray(load_img("/home/luclaptop/hepia/sem4/visionNum/isc_visnu_public/chapitre_04/noisy_hotel.png"))


class Isotropy(Enum):
    ISO_90 = 1
    ISO_45 = 2

class Orientation(Enum):
    HORIZONTALE = 1
    VERTICALE = 2

def xcorr(img: Img, kernel: Img) -> Img:
    res = np.zeros(img.shape)
    it = np.nditer(img, flags=["multi_index"])
    k_half = int(kernel.shape[0]/2)
    while not it.finished:
        i, j = it.multi_index
        roi = img[i-k_half:i+k_half+1, j-k_half:j+k_half+1]
        if roi.shape == kernel.shape:
            res[i, j] = np.sum(np.multiply(roi, kernel))
        it.iternext()
    res = np.where(res < 0, 0, res)
    res = np.where(res > 255, 255, res)
    return res.astype(np.uint8)

def laplace(img: Img, isotropy: Isotropy) -> Img:
    if isotropy == Isotropy.ISO_45:
        kernel=np.array([[-1,-1,-1],[-1,8,-1],[-1,-1,-1]])
    else:
        kernel=np.array([[0,-1,0],[-1,4,-1],[0,-1,0]])
    return xcorr(img, kernel)

def blur_avg(img: Img, blur_size: int) -> Img:
    k = 1/(blur_size*blur_size)*np.ones((blur_size,blur_size))
    return xcorr(img, k)

def sharpen(img: Img, isotropy: Isotropy) -> Img:
    tmp=blur_avg(img, 7)
    tmp=laplace(tmp, isotropy)
    m=img + tmp*-1
    return m

def gauss_kernel(length: int=3, sigma: float=1.0) -> Img:
    half = (length - 1) / 2
    x_axis = np.linspace(-half, half, length)
    gauss = np.exp(-0.5 * np.square(x_axis) / np.square(sigma))
    kernel = np.outer(gauss, gauss)
    return kernel / np.sum(kernel)

def sobel(img: Img, orientation: Orientation) -> Img:
    if Orientation.HORIZONTALE == orientation :
        k = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])
    elif Orientation.VERTICALE == orientation :
        k = np.array([[1,2,1],[0,0,0],[-1,-2,-1]])
    return xcorr(img, k)

def main():
    fig, axes = plt.subplots(2)
    s_v = sobel(hotel, Orientation.VERTICALE)
    s_h = sobel(hotel, Orientation.HORIZONTALE)
    h = load_img("/home/luclaptop/hepia/sem4/visionNum/isc_visnu_public/chapitre_04/hotel.png")
    show_img(h,axes[0])
    blue_filter = (s_v + s_h)
    h[:,:,0] = np.where(blue_filter > 100, 0, h[:,:,0])
    h[:,:,1] = np.where(blue_filter > 100, 0, h[:,:,1])
    h[:,:,2] = np.where(blue_filter > 100, 255, h[:,:,2])
  
    show_img(h,axes[1])
    plt.show()

if __name__ == "__main__":
    main()