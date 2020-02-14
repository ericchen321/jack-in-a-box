from adafruit_motorkit import MotorKit
import time
kit = MotorKit()
def roll(direction = 1):
    start = time.time()
    kit.motor3.throttle = direction
    while (time.time() - start < 0.25):
        pass
    kit.motor3.throttle = 0.0
    return
'''
try:
    while(1):
        spinOneSecond(1.0)
        time.sleep(3)
        spinOneSecond(-1.0)
        time.sleep(3)
except KeyboardInterrupt:
         kit.motor1.throttle = 0.0
         print("keyboard interrupt detected.")
'''
