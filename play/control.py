import RPi.GPIO as gpio
import time
import motors as m
import traceback
gpio.setwarnings(False)
gpio.setmode(gpio.BCM)
gpio.setup(21,gpio.IN)
preparePin = 21
piin = 12
piout_command = 17
cardout = [27,4,5,6,7,8] # the first element would be least significant bit when outputting
piin_dealerOrPlayer = 9

# return face value of card read
def readcard():
    return m.r_s()

def main():
    try:
        # set up ports
        gpio.setup(piin,gpio.IN)
        gpio.setup(piout_command,gpio.OUT)
        for i in cardout:
            gpio.setup(i,gpio.OUT)  
        gpio.setup(piin_dealerOrPlayer,gpio.IN)

        while (1):
            # tell DE1 the Pi is ready
            gpio.output(piout_command,gpio.LOW)

            # wait for DE1 to issue DEAL
            print("/////////////Waiting for DE1 to ask/////////////")
            while(gpio.input(piin) == gpio.LOW):
                pass
            print("DE1 asks me to deal!")

            # check to whom to deal
            if (gpio.input(piin_dealerOrPlayer) == gpio.HIGH):
                print("Dealing to DEALER!")
            else:
                print("Dealing to PLAYER!")

            result = readcard()

            print("Camera read: " + str(result))
            for j in range (6):
                gpio.output(cardout[j], (result >> j) & 0x01)

            # issue acknowledge to DE1
            gpio.output(piout_command,gpio.HIGH)
            print("Told DE1 the result and piout_command is high")

            # wait for DE1 to acknowledge
            while(gpio.input(piin) == gpio.HIGH):
                pass
            print("DE1 got the result.")

    except Exception as e:
        traceback.print_exc()
        print("Ending the program.")
        gpio.cleanup()
    return

if __name__ == '__main__':
    main()
