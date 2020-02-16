from adafruit_motorkit import MotorKit
import RPi.GPIO as gpio
import time
import cv2
from PIL import Image
from picamera import PiCamera
import loadpic

camera = PiCamera()
model = loadpic.loadmodel("CNNPOKER2.model")

gpio.setwarnings(False)
kit = MotorKit()
gpio.setmode(gpio.BCM)
gpio.setup(21,gpio.IN)
preparePin = 21
def spit():
    start = time.time()
    kit.motor4.throttle = -1.0
    ''' some experiment data with repect to maple back cards'''
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
    file_name = "/home/pi/Desktop/motortestimg.jpg"

    #get image
    camera.start_preview()
    camera.capture(file_name)
    camera.stop_preview()

    image = cv2.imread(file_name)
    image_crop = image[0:720, 320:960]
    cv2.imwrite(file_name, image_crop)

    #recognize value
    cardpic = loadpic.loadpic(file_name)
    result = loadpic.guess(model, cardpic)

    #spit
    spit()
    return result.item()

def recog():
    file_name = "/home/pi/Desktop/motortestimg.jpg"

    #get image
    camera.start_preview()
    camera.capture(file_name)
    camera.stop_preview()

    image = cv2.imread(file_name)
    image_crop = image[0:720, 320:960]
    cv2.imwrite(file_name, image_crop)

    #recognize value
    cardpic = loadpic.loadpic(file_name)
    cardval = loadpic.guess(model, cardpic)
    return cardval
    
    
