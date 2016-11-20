import time
import pyfirmata
from pyfirmata import Arduino, util, ANALOG, DIGITAL
MECCAFIRM_DEVICE='/dev/ttyACM1'
print "connecting to %s" % MECCAFIRM_DEVICE
board = Arduino(MECCAFIRM_DEVICE)
print "connected to %s" % MECCAFIRM_DEVICE
time.sleep(0.5)
board.analog[3].mode=ANALOG
board.digital[5].mode=DIGITAL
for i in range(5):
    print "send command to %s" % MECCAFIRM_DEVICE
    board.analog[3].write(10)
    board.digital[5].write(i%2)
    time.sleep(2.5)

