#!/usr/bin/env python3

import json
import serial
import firebase_admin
from firebase_admin import db
from datetime import datetime as dt

cred_obj = firebase_admin.credentials.Certificate("secrets.json")
default_app = firebase_admin.initialize_app(cred_obj, {
    "databaseURL": "https://embarcados-ef757-default-rtdb.firebaseio.com/"
})

ref = db.reference("/")
ref.set({
    "uno": {},
    "esp": {},
    "nano": {},
})

serial_port_uno = '/dev/ttyACM0' # Add right port here
serial_port_esp = '/dev/ttyUSB1' # Add right port here
serial_port_nano = '/dev/ttyUSB0' # Add right port here
baud_rate = 9600

ser_uno = serial.Serial(serial_port_uno, baud_rate)
ser_nano = serial.Serial(serial_port_nano, baud_rate)
ser_esp = serial.Serial(serial_port_esp, baud_rate)

def main():
    while True:
        write_log(ser_uno, "uno")
        #write_log(ser_esp, "esp")
        #write_log(ser_nano, "nano")
    
def write_log(board, board_name):
    ref_local = db.reference(f"/{board}")

    with open(f"logs/{board_name}/{str(dt.now())}.log", 'w+') as f:
        line = board.readline()
        line = line.decode('utf-8')

        data = { "message": line.strip() }
        json_object = json.dumps(data, indent=4)

        for _, value in json_object.items():
            ref_local.push().set(value)

        f.write(json_object)
        f.close()

main()