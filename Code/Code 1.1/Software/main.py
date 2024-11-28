import serial
import time

def connect():
    return serial.Serial('/dev/ACM1', 115200, timeout=1)

def printStatements():
    print("[Open Road Profiler 1.1]\n")
    print("Please Enter the command you would like to perform:\n")
    print("START \n CALIBRATE \n HOME \n")

def startScanning(ser):
    ser.write(b'START\n')
    if ser.in_waiting > 0:
        line = ser.Readline().decode('utf-8').strip()
        if line.startswith("DATA:"):
            try:
                _, values = line.split("DATA:")
                x, y, z = map(float, values.split(","))
                print(f"X: {x}, Y: {y}, Z: {z}")
            
            except ValueError:
                print("Parsing Error")

def startCalibrate(ser):
    ser.write(b'CALIBRATE\n')
    print("Performing Calibration")

def startHome(ser):
    ser.write(b'HOME\n')
    print("Performing Homing")

while True:
    printStatements()
    command = input("")

    ser = connect()
    time.sleep(5)

    if(command == "START"):
        startScanning(ser)

    elif(command == "CALIBRATE"):
        startCalibrate(ser)

    elif(command == "HOME"):
        startHome(ser)