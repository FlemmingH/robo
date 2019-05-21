import smbus
import time
from datetime import datetime
from datetime import timedelta
# for RPI version 1, use “bus = smbus.SMBus(0)”
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x04
MotorL = 1
MotorR = 2
L1 = 0
L2 = 0
R1 = 0
R2 = 0
time0 = datetime.now()
step = 0

class key:
    def __init__(self, T, L, R):
        self.T = T
        self.L = L
        self.R = R
keys = []

key1=key(2,255,255)
keys.append(key1)
key2=key(6,255,0)
keys.append(key2)
key3=key(8,0,255)
keys.append(key3)
key4=key(12,0,0)
keys.append(key4)

def resetTime():
    time0 = datetime.now()
    

def writeSpeed(LSpeed,RSpeed):
    if LSpeed >= 0:
        L1=LSpeed
        L2=0
    else:
        L2=abs(LSpeed)
        L1=0
    if RSpeed >= 0:
        R1=RSpeed
        R2=0
    else:
        R2=abs(RSpeed)
        R1=0
    bus.write_i2c_block_data(address,L1,[L2,R1,R2])
    

def writeNumber(value):
    bus.write_byte(address, value)
# bus.write_byte_data(address, 0, value)
    return -1

def readNumber():
    number = bus.read_byte(address)
# number = bus.read_byte_data(address, 1)
    return number

resetTime()
while True:
    dTime = datetime.now()-time0
    if dTime.seconds>keys[step].T:
        if len(keys)>step-1:
            writeSpeed(keys[step].L,keys[step].R)
            step +=1
            
   
"""
    var = input("Enter 1 – 9: ")
    if not var:
        continue

    if var > '1':
        writeSpeed(128,-201)
    else:
        writeNumber(1)
    print ("RPI: Hi Arduino, I sent you ", var)
# sleep one second
    time.sleep(1)
    
    
    print ("dTime: ", dTime.seconds)
    
    number = readNumber()
    print ("Arduino: Hey RPI, I received a digit ", number)
    print
    """