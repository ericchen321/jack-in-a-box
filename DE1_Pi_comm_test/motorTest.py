from adafruit_motorkit import MotorKit
import time
kit = MotorKit()
def spinOneSecond():
    start = time.time()
    kit.motor1.throttle = 1.0
    while (time.time() - start < 0.165):
        pass
    kit.motor1.throttle = 0.0
    return
try:
    while(1):
        spinOneSecond()
        time.sleep(3)
except KeyboardInterrupt:
         kit.motor1.throttle = 0.0
         print("keyboard interrupt detected.")
