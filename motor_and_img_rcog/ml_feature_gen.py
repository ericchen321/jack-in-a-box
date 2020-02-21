# Eric Chen, Bole Ma
# generate training set for card value recognition

import pathlib
import os
import numpy as np
import math
from matplotlib import pyplot as plt
import skimage
import skimage.feature
import skimage.io
import skimage.util
from skimage import data
from skimage.feature import corner_harris, corner_subpix, corner_peaks
from skimage.transform import rotate, rescale, rescale, downscale_local_mean, warp, AffineTransform

# generate square images from rectangle images
def gen_square_images(filepath_in, filepath_out, square_width):
    image = skimage.io.imread(filepath_in)
    num_rows = image.shape[0]
    num_cols = image.shape[1]
    pad_left = (square_width - num_cols) // 2
    pad_right = square_width - num_cols - pad_left
    pad_top = (square_width - num_rows) // 2
    pad_bot = square_width - num_rows - pad_top
    image_padded = skimage.util.pad(image, [(pad_top, pad_bot), (pad_left, pad_right)])
    skimage.io.imsave(filepath_out, skimage.img_as_uint(image_padded))

# apply following xforms on input image:
# shear -6 to 6 deg, 6 deg increment;
# rotate -30 to 30 deg, 10 deg increment;
# scale 0.75 to 1.125, 0.125 increment
# x translation -20 to 20 px, 10 px increment
# y translation -20 to 20 px, 10 px increment
# produce 128x128 output images of format:
# train_<digit>_<shear_deg>_<rot_deg>_<scaling_factor>_<x_trans>_<y_trans>.jpeg
def gen_training_images_128x128():
    digits = ["01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13"]
    for digit in digits:
        print(f"processing digit {digit}")
        image = skimage.io.imread("training_set/square_unscaled/template_" + digit + ".jpeg")
        width = image.shape[0]  # assume square image
        os.system(f"mkdir -p training_set/128x128/{digit}")

        # shear
        shear_deg = -6
        while shear_deg <= 6:
            shear_rad = math.radians(shear_deg)
            
            # rotate
            rot_deg = -30
            while rot_deg <= 30:
                image_rotated = rotate(image, rot_deg, center=(width//2, width//2))

                # scale
                scale_factor = 0.75
                while scale_factor <= 1.125:
                    
                    # x-translate
                    x_trans = -20
                    while x_trans <= 20:
                        
                        # y-translate
                        y_trans = -20
                        while y_trans <= 20:
                            tform = AffineTransform(scale=(scale_factor, scale_factor), rotation=0, shear=shear_rad,
                                translation=(x_trans, y_trans))
                            image_translated = warp(image_rotated, tform.inverse)

                            # resize to 128x128
                            image_resized = skimage.transform.resize(image_translated, (128, 128), clip=True, anti_aliasing=True)

                            #print(len(image_resized[np.nonzero(image_resized > 0)])/(128*128))
                            #image_resized = 256 * image_resized
                            skimage.io.imsave(f"training_set/128x128/{digit}/train_{digit}_{shear_deg}_{rot_deg}_{scale_factor}_{x_trans}_{y_trans}.png", image_resized)
                            y_trans += 10
                        
                        x_trans += 10

                    scale_factor += 0.125

                rot_deg += 10
            
            shear_deg += 6

# apply following xforms on input image:
# shear -6 to 6 deg, 6 deg increment;
# rotate -30 to 30 deg, 15 deg increment;
# scale 0.75 to 1.125, 0.125 increment
# x translation -20 to 20 px, 20 px increment
# y translation -20 to 20 px, 20 px increment
# produce 64x64 output images of format:
# train_<digit>_<shear_deg>_<rot_deg>_<scaling_factor>_<x_trans>_<y_trans>.jpeg
def gen_training_images_64x64():
    digits = ["01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13"]
    for digit in digits:
        print(f"processing digit {digit}")
        image = skimage.io.imread("training_set/square_unscaled/template_" + digit + ".jpeg")
        width = image.shape[0]  # assume square image
        os.system(f"mkdir -p training_set/64x64/{digit}")

        # shear
        shear_deg = -6
        while shear_deg <= 6:
            shear_rad = math.radians(shear_deg)
            
            # rotate
            rot_deg = -30
            while rot_deg <= 30:
                image_rotated = rotate(image, rot_deg, center=(width//2, width//2))

                # scale
                scale_factor = 0.75
                while scale_factor <= 1.125:
                    
                    # x-translate
                    x_trans = -20
                    while x_trans <= 20:
                        
                        # y-translate
                        y_trans = -20
                        while y_trans <= 20:
                            tform = AffineTransform(scale=(scale_factor, scale_factor), rotation=0, shear=shear_rad,
                                translation=(x_trans, y_trans))
                            image_translated = warp(image_rotated, tform.inverse)

                            # resize to 64x64
                            image_resized = skimage.transform.resize(image_translated, (64, 64), clip=True, anti_aliasing=True)

                            #print(len(image_resized[np.nonzero(image_resized > 0)])/(128*128))
                            #image_resized = 256 * image_resized
                            skimage.io.imsave(f"training_set/64x64/{digit}/train_{digit}_{shear_deg}_{rot_deg}_{scale_factor}_{x_trans}_{y_trans}.png", image_resized)
                            y_trans += 20
                        
                        x_trans += 20

                    scale_factor += 0.125

                rot_deg += 10
            
            shear_deg += 6

# apply following xforms on input image:
# shear -6 to 6 deg, 6 deg increment;
# rotate -30 to 30 deg, 15 deg increment;
# scale 0.75 to 1.125, 0.125 increment
# x translation -20 to 20 px, 20 px increment
# y translation -20 to 20 px, 20 px increment
# produce 32x32 output images of format:
# train_<digit>_<shear_deg>_<rot_deg>_<scaling_factor>_<x_trans>_<y_trans>.jpeg
def gen_training_images_32x32():
    digits = ["01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13"]
    for digit in digits:
        print(f"processing digit {digit}")
        image = skimage.io.imread("training_set/square_unscaled/template_" + digit + ".jpeg")
        width = image.shape[0]  # assume square image
        os.system(f"mkdir -p training_set/32x32/{digit}")

        # shear
        shear_deg = -6
        while shear_deg <= 6:
            shear_rad = math.radians(shear_deg)
            
            # rotate
            rot_deg = -30
            while rot_deg <= 30:
                image_rotated = rotate(image, rot_deg, center=(width//2, width//2))

                # scale
                scale_factor = 0.75
                while scale_factor <= 1.125:
                    
                    # x-translate
                    x_trans = -20
                    while x_trans <= 20:
                        
                        # y-translate
                        y_trans = -20
                        while y_trans <= 20:
                            tform = AffineTransform(scale=(scale_factor, scale_factor), rotation=0, shear=shear_rad,
                                translation=(x_trans, y_trans))
                            image_translated = warp(image_rotated, tform.inverse)

                            # resize to 32x32
                            image_resized = skimage.transform.resize(image_translated, (32, 32), clip=True, anti_aliasing=True)

                            #print(len(image_resized[np.nonzero(image_resized > 0)])/(128*128))
                            #image_resized = 256 * image_resized
                            skimage.io.imsave(f"training_set/32x32/{digit}/train_{digit}_{shear_deg}_{rot_deg}_{scale_factor}_{x_trans}_{y_trans}.png", image_resized)
                            y_trans += 20
                        
                        x_trans += 20

                    scale_factor += 0.125

                rot_deg += 10
            
            shear_deg += 6

# clear all transformed images
def clear_training_images():
    digits = ["01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13"]
    for digit in digits:
        os.chdir("./training_set/" + digit)
        os.system("rm *.png")
        os.chdir("../../")