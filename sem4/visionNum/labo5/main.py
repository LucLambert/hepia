import cv2
import matplotlib.pyplot as plt
import numpy as np

plt.style.use('dark_background')

img = cv2.imread("hepia.png")
print(img)

struc_elem = cv2.getStructuringElement(cv2.MORPH_RECT, (3,3))

img_erode = cv2.erode(img, struc_elem)
img_dilate = cv2.dilate(img, struc_elem)

struc_elem = cv2.getStructuringElement(cv2.MORPH_RECT, (5,5))

img_open = cv2.morphologyEx(img, cv2.MORPH_OPEN, struc_elem)
img_close = cv2.morphologyEx(img, cv2.MORPH_CLOSE, struc_elem)
img_open_close = cv2.morphologyEx(img_open, cv2.MORPH_CLOSE, struc_elem)
img_close_open = cv2.morphologyEx(img_close, cv2.MORPH_OPEN, struc_elem)

img_erode2 = cv2.erode(img_close_open, struc_elem)
img_dilate2 = cv2.dilate(img_close_open, struc_elem)
img_bound_int = img_close_open - img_erode2
img_bound_ext = img_dilate2 - img_close_open

fig, axes = plt.subplots(5,2)
axes[0][0].imshow(img)
axes[0][0].set_title("origine")

axes[1][0].imshow(img_erode)
axes[1][0].set_title("érosion")

axes[1][1].imshow(img_dilate)
axes[1][1].set_title("dilatation")

axes[2][0].imshow(img_open)
axes[2][0].set_title("open")

axes[2][1].imshow(img_close)
axes[2][1].set_title("close")

axes[3][0].imshow(img_open_close)
axes[3][0].set_title("open-close")

axes[3][1].imshow(img_close_open)
axes[3][1].set_title("close-open")

axes[4][0].imshow(img_bound_int)
axes[4][0].set_title("bound-int")

axes[4][1].imshow(img_bound_ext)
axes[4][1].set_title("bound-ext")

plt.show()
