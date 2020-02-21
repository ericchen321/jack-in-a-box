# -*- coding: utf-8 -*-
# author: Bole Ma, Eric Chen
# training based on KNN model

import sklearn
# Standard scientific Python imports
import matplotlib.pyplot as plt
import os
import skimage.io
import numpy as np

# Import datasets, classifiers and performance metrics
from sklearn import datasets, svm, metrics
from sklearn.model_selection import train_test_split

from skimage.feature import hog
import numpy as np
import os
import scipy.ndimage
from skimage.feature import hog
from skimage import data, color, exposure
from sklearn.model_selection import  train_test_split
from sklearn.neighbors import KNeighborsClassifier

# save training model
import joblib

def load_dataset_hog(width):
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
                df = hog(training_digit_image, orientations=8, pixels_per_cell=(8,8), cells_per_block=(8, 8))
                # extract digit's Histogram of Gradients (HOG)
                features_list.append(df)
                features_label.append(label)

    # store features array into a numpy array
    X_hog = np.array(features_list)
    y_hog = np.array(features_label)

    return X_hog, y_hog

X_hog, y_hog = load_dataset_hog(64)

# Split data into train and test subsets
X_train, X_test, y_train, y_test = train_test_split(
    X_hog, y_hog, test_size=0.15, shuffle=True)

knn = KNeighborsClassifier(n_neighbors=3)

# Commented out IPython magic to ensure Python compatibility.
print(X_train.shape, y_test.shape)
print(X_test.shape, y_train.shape)

# get the model accuracy
knn.fit(X_train, y_train)

predicted = knn.predict(X_test)
model_score = knn.score(X_test, y_test)

print(f"KNN score: {model_score}")

print("Classification report for classifier %s:\n%s\n"
       % (knn, metrics.classification_report(y_test, predicted)))

# save trained model
joblib.dump(knn, './training_model/knn_model_partial.pkl')

# get the model accuracy
knn.fit(X_hog, y_hog)
joblib.dump(knn, './training_model/knn_model_full.pkl')