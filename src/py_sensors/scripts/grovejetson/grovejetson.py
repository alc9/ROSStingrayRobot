#!/usr/bin/env python
"""
5v - Red
GND - Black
Not Connected - White
D2 - Yellow
When there is water on the board - LOW
Otherwise - HIGH
"""
import Jetson.GPIO as GPIO
class grovejetson():
    def __init__(self,pin):
        GPIO.setmode(GPIO.BOARD)
        self.pin_=pin
    
    @property
    def value(self):
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(self.pin_,GPIO.IN)
        return GPIO.input(self.pin_)
        """
        if GPIO.input(self.pin_)==GPIO.LOW:
            return True
        else:
            return False
        """
