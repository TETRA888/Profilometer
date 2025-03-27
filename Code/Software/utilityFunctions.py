import serial
import time
from graphplot3d import plot_data

# This function will simply establish a serial connection between the microcontroller
# and the Raspberry Pi
def connect():
    print("Connecting") # Debugging code
    return serial.Serial('/dev/cu.usbmodem1422201', 115200, timeout=1)

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

    filename = "profileData.csv"

    with open(filename, 'w') as file:
        file.write("X,Y,Z\n") #CSV Header format

        ser.write(b'START\n')
        if ser.in_waiting > 0:

            scanning = True
            while scanning:
                if ser.in_waiting > 0:
                    line = ser.readline().decode('utf-8').strip()
                    
                    # Check for end of scan signal
                    if line == "DATA_COLLECTION_COMPLETE":
                        scanning = False
                        print("Scanning complete... Saving data")
                        break
                        
                    # Process data points
                    if line.startswith("DATA:"):
                        try:
                            _, values = line.split("DATA:")
                            x, y, z = map(float, values.split(","))
                            print(f"X: {x}, Y: {y}, Z: {z}")
                            
                            # Write to CSV file
                            file.write(f"{x},{y},{z}\n")
                            
                        except ValueError:
                            print("Parsing Error")
        
    print(f"Data saved to {filename}")
    plot_data(filename)
    return filename

# Function that will send the calibrate function to the microcontroller
# @param ser is a reference to the serial port that will be used to read 
# the unicode transmission format 8 bit data from (utf-8)
def startCalibrate(ser):
    print("Calibrating") # Debugging code
    ser.write(b'CALIBRATE\n')
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        if line.startswith("CALIBRATION_SUCCESSFUL"):
            print("Calibration Successful")
        elif line.startswith("CALIBRATION_FAILED"):
            print("Calibration Failed")
        else:
            print("Unknown Response")

# Function that simply sends the HOME command to the microcontroller
# @param ser is a reference to the serial port that will be used to read 
# the unicode transmission format 8 bit data from (utf-8)
def startHome(ser):
    print("Homing") # Debugging code
    ser.write(b'HOME\n')
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        if line.startswith("HOME_COMPLETE"):
            print("Homing Complete")
        else:
            print("Unknown Response")

def sendData(): #ADD ACTUAL FUNCTIONALITY ONCE GRAPH IS COMPLETE
    print("Sending Data via Rest Api")

def scanMoveless(ser):
    print("Scanning without moving")
    ser.write(b'SCANMOVELESS\n')

def moveScanless(ser):
    print("Moving without scanning")
    ser.write(b'MOVESCANLESS\n')

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