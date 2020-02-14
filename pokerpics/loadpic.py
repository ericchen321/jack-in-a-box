import cv2
import tensorflow as tf
import numpy as np
cnnmodel = "CNNPOKER.model"
def loadpic(addr):
    img = cv2.imread(addr, cv2.IMREAD_GRAYSCALE)
    img = cv2.resize(img,(128,128))
    img = img.reshape(-1,128,128,1)
    img = img /255.0
    return img
def loadmodel(addr):
    model = tf.keras.models.load_model(addr)
    return model
def guess(model, image):
    pred = model.predict(image)
    print(pred.argmax() + 1)
