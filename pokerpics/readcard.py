import loadpic as lp
from picamera import PiCamera
from time import sleep
import loadpic as lp
import mt2 as m
model = lp.loadmodel(lp.cnnmodel)
camera = PiCamera()
def readandspit():
    camera.start_preview()
    sleep(2)
    camera.capture('/home/pi/Desktop/pokerpics/pokerimg.jpg')
    camera.stop_preview()
    img = lp.loadpic('/home/pi/Desktop/pokerpics/pokerimg.jpg')
    read = lp.guess(model,img)
    return read
    
