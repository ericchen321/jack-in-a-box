from adafruit_motorkit import MotorKit
import RPi.GPIO as gpio
import time
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
    while (time.time() - start < 0.12):
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

