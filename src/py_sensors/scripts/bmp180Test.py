#!/usr/bin/python

from bmp180.bmp180 import bmp180

bmp = bmp180(0x77)

while True:
    print("Temp: " + str(bmp.get_temp()) + " Celcius")
    print("Pressure: " + str(bmp.get_pressure()) + " Pascal")
    print("Altitude: " + str(bmp.get_altitude()) + " meter")
