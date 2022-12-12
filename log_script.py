#!/usr/bin/env python3

import serial
from datetime import datetime as dt

serial_port = '/dev/ttyXXXXXXXX' # Add right port here
baud_rate = 9600

path = f"{str(dt.now())}.log"
ser = serial.Serial(serial_port, baud_rate)

with open(path, 'w+') as f:
    while True:
        line = ser.readline()
        line = line.decode('utf-8')
        f.writelines([line.strip(), " t = %s \n" % (dt.now())])