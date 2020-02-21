# author: 
# machine-learning based recognition using Tensorflow

import tensorflow as tf

model = loadmodel("CNNPOKER2.model")

def loadmodel(addr):
    global model
    model = tf.keras.models.load_model(addr)
    return model

def guess(model, image):
    global model
    pred = model.predict(image)
    card_val = card_map[pred.argmax()]
    print("The guessed value is " + card_val)
    return pred.argmax() + 1