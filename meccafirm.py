import time
import pyfirmata
from pyfirmata import Arduino, util, ANALOG, DIGITAL, INPUT, OUTPUT, SERVO, PWM
MECCAFIRM_DEVICE='/dev/ttyACM0'
print "connecting to %s" % MECCAFIRM_DEVICE
board = Arduino(MECCAFIRM_DEVICE)
print "connected to %s" % MECCAFIRM_DEVICE

if __name__=='__main__':
    time.sleep(2)
    pin = board.get_pin('d:3:o')
    pin.mode=SERVO
    for i in range(3):
        print "send command to %s" % MECCAFIRM_DEVICE
        pin.write(i*10)
        time.sleep(4)

