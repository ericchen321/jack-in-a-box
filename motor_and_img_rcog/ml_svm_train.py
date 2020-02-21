# -*- coding: utf-8 -*-
# author: Bole Ma, Eric Chen
# training based on SVM model

import sklearn
# Standard scientific Python imports
import matplotlib.pyplot as plt
import os
import skimage.io
import numpy as np

# Import datasets, classifiers and performance metrics
from sklearn import datasets, svm, metrics
from sklearn.model_selection import train_test_split

# save training model
import joblib

def load_dataset(width):
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
    x_data  = np.array(features_list)
    y_data = np.array(features_label)

    return x_data, y_data

x_data, y_data = load_dataset(64)

# To apply a classifier on this data, we need to flatten the image, to
# turn the data in a (samples, feature) matrix:
n_samples = len(y_data)
x_data = x_data.reshape((n_samples, -1))

# Create a classifier: a support vector classifier
classifier = svm.SVC(gamma=0.001, verbose=True)

# Split data into train and test subsets
X_train, X_test, y_train, y_test = train_test_split(
    x_data, y_data, test_size=0.15, shuffle=True)

print(X_train.shape, y_test.shape)
print(X_test.shape, y_train.shape)

# Commented out IPython magic to ensure Python compatibility.
# We learn the digits on the first half of the digits
classifier.fit(X_train, y_train)

print('All classified')

# Now predict the value of the digit on the second half:
predicted = classifier.predict(X_test)

print("Classification report for classifier %s:\n%s\n"
      % (classifier, metrics.classification_report(y_test, predicted)))

# save trained model
joblib.dump(classifier, './training_model/svm_model_partial.pkl')
