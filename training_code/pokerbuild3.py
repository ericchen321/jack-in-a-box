from __future__ import absolute_import, division, print_function, unicode_literals
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, Activation, Flatten, Conv2D, MaxPooling2D
AUTOTUNE = tf.data.experimental.AUTOTUNE
import IPython.display as display
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import os
import pathlib
data_dir = pathlib.Path("C:\\Users\\liujq\\Downloads\\croppedcardpics")
image_count = len(list(data_dir.glob('*/*.jpg')))
CLASS_NAMES = np.array([item.name for item in data_dir.glob('*') if (item.name != "pokerbuild3.py" and item.name != "__pycache__")])
image_generator = tf.keras.preprocessing.image.ImageDataGenerator(
                    rescale=1/255.0,
                    rotation_range=45,
                    width_shift_range=.15,
                    height_shift_range=.15,
                    brightness_range=(0.3, 0.8),
                    shear_range=30.0,
                    zoom_range=0.3
                    )
train_data_gen = image_generator.flow_from_directory(directory=str(data_dir),
                                                     color_mode='grayscale',
                                                     batch_size=32,
                                                     class_mode = 'binary',
                                                     shuffle=True,
                                                     target_size=(128, 128))

model = Sequential()
# 3 convolutional layers
model.add(Conv2D(32, (3, 3), input_shape = (128,128,1) ))
model.add(Activation("relu"))
model.add(MaxPooling2D(pool_size=(2,2)))


model.add(Conv2D(64, (3, 3)))
model.add(Activation("relu"))
model.add(MaxPooling2D(pool_size=(2,2)))


model.add(Conv2D(64, (3, 3)))
model.add(Activation("relu"))
model.add(MaxPooling2D(pool_size=(2,2)))
model.add(Dropout(0.25))

# 2 hidden layers
model.add(Flatten())
model.add(Dense(128))
model.add(Activation("relu"))

model.add(Dense(128))
model.add(Activation("relu"))

# The output layer with 13 neurons, for 13 classes
model.add(Dense(13))
model.add(Activation("softmax"))

# Compiling the model using some basic parameters
model.compile(loss="sparse_categorical_crossentropy",optimizer="adam",metrics=["accuracy"])

history = model.fit(train_data_gen, epochs = 80)
model_json = model.to_json()
with open("model.json", "w") as json_file :
	json_file.write(model_json)

model.save_weights("model2.h5")
print("Saved model to disk")

model.save('CNNPOKER2.model')
