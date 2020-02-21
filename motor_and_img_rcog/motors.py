from adafruit_motorkit import MotorKit
import RPi.GPIO as gpio
import time
import cv2
from PIL import Image
from picamera import PiCamera
import loadpic
import pm
import ml_knn_predict

gpio.setwarnings(False)
kit = MotorKit()
gpio.setmode(gpio.BCM)
gpio.setup(21,gpio.IN)
preparePin = 21
def spit():
    start = time.time()
    kit.motor4.throttle = -1.0
    # some experiment data with repect to maple back cards
    # 0.14 will be a little jam, but stable
    # 0.15 can drop cards sometime
    while (time.time() - start < 0.13):
        pass
    kit.motor4.throttle = 0.0
    return

def k():
    try:
        while(1):
            spit()
            time.sleep(3)
    except KeyboardInterrupt:
             kit.motor4.throttle = 0.0
             print("keyboard interrupt detected.")

def p():
    try:
        while(gpio.input(preparePin) == 0):
            spit()
            time.sleep(3.5)
        return
    except KeyboardInterrupt:
        print('stopped')
        kit.motor4.throttle = 0.0
        return
    

def r_s():
    #recognize card value
    card_val = recog("ML_KNN") # use KNN for now

    #spit
    spit()
    return card_val

# image recognition. Captures image from camera
# and return the digit recognized;
# The method will overwrite "motortestimg.jpg"
# under the current directory;
# flag should be "TF" or "PM" or "ML_KNN"
def recog(flag):
    filename = "motortestimg.jpg"

    # get and crop image to fit need of recognition algorithm
    if flag == 'TF':
        loadpic.savepic(filename, 320, 640, 0, 720)
    elif flag == 'PM':
        loadpic.savepic(filename, 420, 800, 100, 600)   # crop image to speed up matching
    elif flag == 'ML_KNN':
        loadpic.savepic(filename, 0, 1280, 0, 1024)

    #recognize value
    if flag == 'TF':
        cardpic = loadpic.loadpic(filename)
        cardval = ml_tf.guess(ml_tf.model, cardpic)
        return cardval
    elif flag == 'PM':
        match_ret_val = pm.match(filename)
        if match_ret_val == "error":
            return 0
        else:
            return int(match_ret_val[9:11])
    elif flag == 'ML_KNN':
        return ml_knn_predict.guess(filename)
    else:
        return 0
    
