import serial
import time

# This function will simply establish a serial connection between the microcontroller
# and the Raspberry Pi
def connect():
    print("Connecting") # Debugging code
    return serial.Serial('COM4', 115200, timeout=1)

# Archieved functions
def printStatements():
    print("[Open Road Profiler 1.1]\n")
    print("Please Enter the command you would like to perform:\n")
    print("START \n CALIBRATE \n HOME \n")

# Function that will send the start scanning command to the microcontroller
# @param ser is a reference to the serial port that will be used to read 
# the unicode transmission format 8 bit data from (utf-8)
def startScanning(ser):
    print("Scanning") # Debugging code
    ser.write(b'START\n')
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        if line.startswith("DATA:"):
            try:
                _, values = line.split("DATA:")
                x, y, z = map(float, values.split(","))
                print(f"X: {x}, Y: {y}, Z: {z}")
            
            except ValueError:
                print("Parsing Error")

# Function that will send the calibrate function to the microcontroller
# @param ser is a reference to the serial port that will be used to read 
# the unicode transmission format 8 bit data from (utf-8)
def startCalibrate(ser):
    print("Calibrating") # Debugging code
    ser.write(b'CALIBRATE\n')

# Function that simply sends the HOME command to the microcontroller
# @param ser is a reference to the serial port that will be used to read 
# the unicode transmission format 8 bit data from (utf-8)
def startHome(ser):
    print("Homing") # Debugging code
    ser.write(b'HOME\n')

# Debugging code that can be used without the gui running
# while True:
#     printStatements()
#     command = input("")

#     ser = connect()
#     time.sleep(5)

#     if(command == "START"):
#         startScanning(ser)

#     elif(command == "CALIBRATE"):
#         startCalibrate(ser)

#     elif(command == "HOME"):
#         startHome(ser)

def sendData(): #ADD ACTUAL FUNCTIONALITY ONCE GRAPH IS COMPLETE
    print("Sending Data via Rest Api")

def scanMoveless(ser):
    print("Scanning without moving")
    ser.write(b'SCANMOVELESS\n')

def moveScanless(ser):
    print("Moving without scanning")
    ser.write(b'MOVESCANLESS\n')
