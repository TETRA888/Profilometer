import serial
import time

# Open the serial connection
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
time.sleep(2)  # Give the connection a moment to initialize

# Send the start command to the Arduino
ser.write(b'START\n')
print("Start command sent to Arduino")

# Read the data sent back by the Arduino (if needed)
while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        if line.startswith("DATA:"):
            try:
                _, values = line.split("DATA:")
                x, y, z = map(float, values.split(","))
                print(f"X: {x}, Y: {y}, Z: {z}")
            except ValueError:
                print("Parsing error!")
