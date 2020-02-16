import cv2
import tensorflow as tf
import numpy as np 
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
    card_val = card_map[pred.argmax()]
    print("The guessed value is " + card_val)
    return pred.argmax() + 1

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
