from adafruit_motorkit import MotorKit
import RPi.GPIO as gpio
import time
gpio.setwarnings(False)
#kit = MotorKit() NOTE: nullify motoring for now
gpio.setmode(gpio.BCM)
gpio.setup(21,gpio.IN)
preparePin = 21
piin = 12
piout_command = 17
cardout = [27,4,5,6,7,8] # the first element would be least significant bit when outputting
piin_dealerOrPlayer = 9

# used for the mock game
mock_cards = [1, 11, 1, 9, 1]  # A, Q, A, 9, A

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

# return face value of card read
def readcard(mock_cards_counter):
    # TODO: stub; for now, iterate through mock_cards[]
    card_val = mock_cards[mock_cards_counter]
    return card_val

def main():
    try:
        # set up ports
        gpio.setup(piin,gpio.IN)
        gpio.setup(piout_command,gpio.OUT)
        for i in cardout:
            gpio.setup(i,gpio.OUT)  
        gpio.setup(piin_dealerOrPlayer,gpio.IN)

        # set up counter for array of mock dealt cards TODO: remove later
        mock_cards_counter = 0

        while (1):
            # tell DE1 the Pi is ready
            gpio.output(piout_command,gpio.LOW)

            # wait for DE1 to issue DEAL
            print("Waiting for DE1 to ask")
            while(gpio.input(piin) == gpio.LOW):
                pass
            print("DE1 asks me to deal!")

            # check to whom to deal
            if (gpio.input(piin_dealerOrPlayer) == gpio.HIGH):
                print("Dealing to DEALER!")
            else:
                print("Dealing to PLAYER!")

            # TODO: routine to deal card

            # read card and issue card face value
            result = readcard(mock_cards_counter)
            # TODO: remove the following after readcard implemented
            mock_cards_counter = mock_cards_counter + 1
            if mock_cards_counter>4:
                mock_cards_counter = 0

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
        print("Ending the program.")
        gpio.cleanup()
    return

if __name__ == '__main__':
    main()