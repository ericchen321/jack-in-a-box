import RPi.GPIO as gpio
import time
gpio.setwarnings(False)
#kit = MotorKit() NOTE: nullify motoring for now
gpio.setmode(gpio.BCM)
gpio.setup(21,gpio.IN)
preparePin = 21
piin = 1
piout = 2
cardout = [3,4,5,6,7,8] # the first element would be least significant bit when outputting

def main():
    try:
        # set up ports
        gpio.setup(piin,gpio.IN)
        gpio.setup(piout,gpio.OUT)
        for i in cardout:
            gpio.setup(i,gpio.OUT)  
  
        print("started")
        while (1):
            gpio.output(piout, gpio.HIGH)
            time.sleep(0.75)
            gpio.output(piout, gpio.LOW)
            time.sleep(0.75)

    except Exception as e:
        print("Ending the program.")
        gpio.cleanup()
    return

if __name__ == '__main__':
    main()