import numpy as np 
from PIL import Image

import numpy.typing as npt
from typing import Tuple

Img = npt.NDArray[np.uint8]

PATH="../isc_visnu_public/chapitre_01/gunslinger.png"

def ex1() -> None:
    m=load_img(PATH)
    print("size:", np.shape(m)[0],"x", np.shape(m)[1])
    print("type: ", np.shape(m)[2])
    show_img(m)

def load_img(path: str) -> Img:
    with Image.open(path) as im:
        m = np.array(im)
        return m

def show_img(img: Img) -> None:
    im = Image.fromarray(img)
    im.show()

def ex2() -> Img:
    m=np.ones((300,300),dtype=np.uint8)
    m*=127
    m[:,13:16] = 255
    m[13:16,:] = 255
    show_img(m)
    return m

def ex3() -> None:
    m=np.zeros((300,300,3),dtype=np.uint8)
    m[:,:,1]=255
    show_img(m)

    m1=m
    m1[0:100,0:100,1]=0
    m1[0:100,0:100,0]=255

    m1[100:200,100:200,0]=255
    m1[100:200,100:200,2]=255

    m1[200:300,200:300,1]=0
    m1[200:300,200:300,2]=255
    show_img(m1)

    m2=m
    m2[:,:,1]=255
    m2[:,:,0]=0
    m2[:,:,2]=0
    m2[149:151,:,1]=0
    m2[149:151,:,0]=255
    m2[:,149:151,1]=0
    m2[:,149:151,0]=255
    show_img(m2)

def ex4() -> None:
    m=np.zeros((300,300,3),dtype=np.uint8)
    t=np.arange(0,255,(255/300))
    t1=np.arange(255,0,-(255/300))
    for i in range(150):
        m[i,:,0]=t
        m[150+i,:,1]=t1
    
    show_img(m)

def ex5() -> None:
    m=np.zeros((300,300),dtype=np.uint8)
    im=ex2()
    m[:]=im[:,::-1]
    show_img(m)
    m[:]=m[::-1,:]
    show_img(m)
    m[:]=m[:,::-1]
    show_img(m)

def roi(img: Img, top_left: Tuple[int, int], size: Tuple[int, int]) -> Img:
    m=np.array(size,dtype=np.uint8)
    m=img[top_left[0]:top_left[0]+size[0],top_left[1]:top_left[1]+size[1]]
    return m
    
def ex6():
    im=load_img(PATH)
    m=roi(im,(400,200),(400,300))
    show_img(m)

def ex7():
    im=ex2()
    m=np.resize(im, (150,150))
    m1=np.resize(im, (450,450))
    #show_img(m)
    #show_img(m1)
    m2=resize_smaller(im,2)
    #show_img(m2)
    m3=resize_larger(im,3)
    show_img(m3)
    img=load_img(PATH)
    resized = resize_smaller(img, 4)
    back_to_original = resize_larger(resized, 4)
    show_img(back_to_original)

def resize_smaller(img: Img, factor: int) -> Img:
    if(len(img.shape)==3):
        m=np.zeros((img.shape[0]//factor, img.shape[1]//factor,3),dtype=np.uint8)
    else:
        m=np.zeros((img.shape[0]//factor, img.shape[1]//factor),dtype=np.uint8)
    m=img[::factor,::factor]
    return m

def resize_larger(img: Img, factor: int) -> Img:
    if(len(img.shape)==3):
        m=np.zeros((img.shape[0]*factor, img.shape[1]*factor,3),dtype=np.uint8)
    else:
        m=np.zeros((img.shape[0]*factor, img.shape[1]*factor),dtype=np.uint8)
    m[::factor,::factor]=img[:]
    for i in range(m.shape[0]):
        for y in range(m.shape[1]):
            m[i,y]=img[i//factor,y//factor]
    return m

# ex1()
# ex2()
# ex3()
# ex4()
# ex5()
# ex6()
# ex7()