# author: Bole Ma, Eric Chen, Hussein Moghnieh
# modified based on code from https://towardsdatascience.com/scanned-digits-recognition-using-k-nearest-neighbor-k-nn-d1a1528f0dea

import numpy as np
import os
import scipy.ndimage
import skimage.io
from skimage.feature import hog
from skimage import data, color, exposure
from sklearn.model_selection import  train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.externals import joblib
import autokeras as ak
from tensorflow.keras.utils import to_categorical

def train(width):
    digits = ["01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13"]
    features_list = []
    features_label = []
    # load labeled training / test data
    # loop over the 13 directories where each directory stores the images of a digit
    for digit in digits:
        label = digit
        training_directory = f'./training_set/{width}x{width}/{label}/'
        for filename in os.listdir(training_directory):
            if filename.endswith('.png') :
                training_digit_image = skimage.io.imread(training_directory + filename)
                # training_digit = color.rgb2gray(training_digit
        
                features_list.append(training_digit_image / 255)
                features_label.append(label)

    # store features array into a numpy array
    x_train  = np.array(features_list)
    y_train = to_categorical(np.array(features_label))

    # Initialize the image classifier.
    clf = ak.ImageClassifier(max_trials=10) # It tries 10 different models.
    # Feed the image classifier with training data.
    clf.fit(x_train, y_train)