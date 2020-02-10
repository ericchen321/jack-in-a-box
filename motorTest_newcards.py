from adafruit_motorkit import MotorKit
import RPi.GPIO as gpio
import time
gpio.setwarnings(False)
kit = MotorKit()
gpio.setmode(gpio.BCM)
gpio.setup(21,gpio.IN)
preparePin = 21
piin = 1
piout = 2
cardout = [3,4,5,6,7,8] # the first element would be least significant bit when outputting
def spit():
    start = time.time()
    kit.motor4.throttle = -1.0
    ''' some experiment data with repect to maple back cards'''
    # 0.14 will be a little jam, but stable
    # 0.15 can drop cards sometime
    while (time.time() - start < 0.151):
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
def readcard():
    # TODO: fill this out

def main():
    try:
        gpio.setup(piin,gpio.IN)
        gpio.setup(piout,gpio.OUT)
        for i in cardout:
            gpio.setup(i,gpio.OUT)    
        while (1):
            print("Waiting for DE1 to ask")
            while(gpio.input(piin) == gpio.LOW):
                pass
            print("DE1 asks me to deal!")
            result = readcard()
            print("Camera read is successful.")
            for j in range (6):
                gpio.output(cardout[j], (result >> j) & 0x01)
            gpio.output(piout,gpio.HIGH)
            print("Told DE1 the result and piout is high")
            while(gpio.input(piin) == gpio.HIGH):
                pass
            print("DE1 got the result.")
            gpio.output(piout,gpio.LOW)
    except Exception as e:
        print("Ending the program.")
        gpio.cleanup()
    return

if __name__ == '__main__':
    main()