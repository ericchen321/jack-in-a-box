# author:
# OpenCV stuff to preprocess images for recognition

import cv2
import numpy as np 
from picamera import PiCamera
import demo

camera = PiCamera()
camera.resolution = (1280, 1024)

card_map = {
0 : 'A',
1 : '2',
2 : '3',
3 : '4',
4 : '5',
5 : '6',
6 : '7',
7 : '8',
8 :'9',
9 : '10',
10 : 'J',
11 : 'Q',
12 : 'K'
}

# save image on camera to disk
# with given filename, initial
# x, dx, initial y and dy.
def savepic(filename, x_init, dx, y_init, dy):
    #get and save image
    camera.start_preview()
    camera.capture(filename)
    camera.stop_preview()
    # show raw image dimension
    image = cv2.imread(filename)
    # get dimensions of image
    dimensions = image.shape
    # height, width, number of channels in image
    height = image.shape[0]
    width = image.shape[1]
    channels = image.shape[2]
    print('Image Dimension    : ',dimensions)
    print('Image Height       : ',height)
    print('Image Width        : ',width) 
    # change image to specified dimension
    image_cropped = image[y_init:(y_init+dy), x_init:(x_init+dx)]
    if demo.show_plots is True:
        cv2.imshow("cropped image", image_cropped)
    cv2.imwrite(filename, image_cropped)

# load an image with given filename;
# return the image
def loadpic(addr):
    img = cv2.imread(addr, cv2.IMREAD_GRAYSCALE)
    img = cv2.resize(img,(128,128))
    img = img.reshape(-1,128,128,1)
    img = img /255.0
    return img