import csv
import serial
from datetime import datetime
import random
import time

arduino = serial.Serial("/dev/cu.usbmodem1101", timeout = 1)
arduino.readline()
csvfile = open('data.csv', 'a', newline = '')
counter = 1
while counter <= 1000:

    writer = csv.writer(csvfile)
    datet = str(datetime.now())
    datet = datet.replace('-', '/')
    datet = datet[:13] + ':00:00'
    
    junction = 1
    
    noOfVehicles = int(arduino.readline().rstrip())
    randomID = random.randrange(0, 9999)
    if noOfVehicles != -1: 
        row = [datet, junction, noOfVehicles, randomID]
        print(row)
        writer.writerow(row)
        counter += 1
    time.sleep(0.1)
    
csvfile.close()




