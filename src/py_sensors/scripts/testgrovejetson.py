#!/usr/bin/python

from grovejetson.grovejetson import grovejetson
#40
grovesensor=grovejetson(40)
while True:
    # 0 = wet, 1 = dry
    print(grovesensor.value)
