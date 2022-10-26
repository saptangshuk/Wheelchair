import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

pin1 = 11
pin2 = 13
pin3 = 15
pin4 = 16

GPIO.setup(pin1,GPIO.IN)
GPIO.setup(pin2,GPIO.IN)
GPIO.setup(pin3,GPIO.IN)
GPIO.setup(pin4,GPIO.IN)

out1 = GPIO.input(pin1)
out2 = GPIO.input(pin2)
out3 = GPIO.input(pin3)
out4 = GPIO.input(pin4)

str = str(out1)+str(out2)+str(out3)+str(out4)

if str == '0000':
  #stable state
else if str == '0001':
  #continue making like this
