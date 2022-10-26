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

inp1 = GPIO.input(pin1)
inp2 = GPIO.input(pin2)
inp3 = GPIO.input(pin3)
inp4 = GPIO.input(pin4)

str = str(inp1)+str(inp2)+str(inp3)+str(inp4)

if str == '0000':
  #stable state
else if str == '0001':
  #continue making like this
