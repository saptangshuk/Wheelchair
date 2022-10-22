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

