import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)


GPIO.setup(pin1,GPIO.IN)
GPIO.setup(pin2,GPIO.IN)
GPIO.setup(pin3,GPIO.IN)
GPIO.setup(pin4,GPIO.IN)

