# -*- coding: utf-8 -*-
# author: Bole Ma, Eric Chen
# testing based on KNN model

import joblib
import sklearn
import traceback
import demo
import numpy as np 
import skimage
import skimage.feature
import skimage.io
from skimage.filters import threshold_otsu
from skimage.segmentation import clear_border
from skimage.measure import label, regionprops
from skimage.morphology import closing, square
from skimage.color import label2rgb
from skimage.transform import resize
import matplotlib.pyplot as plt 
import matplotlib.patches as mpatches

knn = joblib.load('training_model/knn_model_full.pkl')
digits = []

# preprocess a raw image from Pi camera
# return the preprocessed 64x64 image
def preprocess_digit_image(image):
    # construct b/w test image
    img =  skimage.io.imread(image, as_gray=True)
    img = img > skimage.filters.threshold_otsu(img)
    if demo.show_plots is True:
        plt.imshow(img)
        plt.title("binary")
        plt.show()

    # flip bits in img
    img = np.invert(img)

    # crop out unnecessary parts
    img = closing(img, square(3))
    # remove border stuff
    cleared = clear_border(img)
    # label image regions
    label_image = label(cleared)

    # find region that has the digit
    # the region should satisfy the following criteria, listed
    # in order of comparison:
    # 1) larger than 260x140
    # 2) the one that's most upper-right
    region_list = []
    for region in regionprops(label_image):
        # take regions with large enough areas
        minr, minc, maxr, maxc = region.bbox
        if (maxc - minc) >= 260 and (maxr - minr) >= 100:
            region_list.append(region)
    if len(region_list) == 0:
        print("ERROR: preprocess_digit_image: cannot find a region large enough!")
        return
    region_digit = None
    region_digit_minc, region_digit_maxc, region_digit_minr, region_digit_maxr = 0, 0, 0, 0
    for region in region_list:
        minc = region.bbox[1]
        if minc >= region_digit_minc:
            region_digit = region
            region_digit_minr, region_digit_minc, region_digit_maxr, region_digit_maxc = region.bbox
    assert region_digit is not None
    # deal with "10"
    for region in regionprops(label_image):
        # find if any region could be "1"
        minr, minc, maxr, maxc = region.bbox
        if maxr <= region_digit_minr and minr>=(region_digit_minr-110) and (maxr-minr)>=25 and (maxr-minr)<=50:
            region_digit_minr = minr
            break
    region_digit = cleared[region_digit_minr:region_digit_maxr, region_digit_minc:region_digit_maxc]
    #plt.imshow(region_digit)
    #plt.title("cropped")
    #plt.show()

    # add padding to produce 512x512 square image
    num_rows = region_digit.shape[0]
    num_cols = region_digit.shape[1]
    pad_left = (512 - num_cols) // 2
    pad_right = 512 - num_cols - pad_left
    pad_top = (512 - num_rows) // 2
    pad_bot = 512 - num_rows - pad_top
    region_digit_padded = skimage.util.pad(region_digit, [(pad_top, pad_bot), (pad_left, pad_right)])
    #plt.imshow(region_digit_padded)
    #plt.title("padded")
    #plt.show()

    # resize it to 64x64
    region_digit_padded = 255 * region_digit_padded; region_digit_padded = region_digit_padded.astype(np.uint8) # from bool to uint8
    region_digit_resized = skimage.transform.resize(region_digit_padded, (64, 64), clip=True, anti_aliasing=True) # produce a float64 image
    region_digit_resized = 255 * region_digit_resized; region_digit_resized = region_digit_resized.astype(np.uint8) # from float64 to uint8
    if demo.show_plots is True:
        plt.imshow(region_digit_resized)
        plt.title("64x64")
        plt.show()
    return region_digit_resized

# extract feature from a given 64x64 
# preprocessed test image;
# return HOG descriptor for the image
def extract_feature(digit_image):
    return skimage.feature.hog(digit_image, orientations=8, pixels_per_cell=(8, 8), cells_per_block=(8, 8))

# return the predicted card value for test data 
# df, the HOG descriptor for an image
def predict_digit(df):
    predict = knn.predict(df.reshape(1,-1))
    likelihood = knn.predict_proba(df.reshape(1,-1))[0]
    print(f"Predicted {predict} with likelihood = {likelihood}")
    return int(predict[0])

# guess the digit of given raw test image
# return the card face value (1 to 13)
def guess(digit_image):
    try:
        # load your image from file 
        image_preprocessed = preprocess_digit_image(digit_image)
        if image_preprocessed is None:
            return 10    # got an error from preproceesing; just return 10

        # extract featuress
        df = extract_feature(image_preprocessed)
        # apply k-NN model created in the previous training stage
        predict = predict_digit(df)

        #hogs = list(map(lambda x: feature_extraction(x), digits))
        #predictions = list(map(lambda x: predict(x), hogs))
        return predict
    except Exception as e:
        traceback.print_exc()
        return 10

