#  <div align="center"> Open Road Profiler (ORP) </div>

The **Open Road Profiler (ORP)** is an advanced, open-source system engineered to map the degradation of theoretical road designs for Caltrans. This precision gantry platform leverages a robust integration of **computer vision**, **LiDAR sensing**, and 
**optical measurement** technologies, including a Garmin LiDAR-Lite v3HP, a 64MP high-resolution camera, and a Class-3B precision laser, to capture sub-millimeter road surface deformations under simulated traffic loads.

## Table of Contents
- [Purpose](#purpose)
- [Future Work](#future-work-and-integrating-into-openusd-for-more-efficient-road-degradation-tracking-in-california)
- [Core Team](#core-team)
- [Electrical System Design](#high-level-electrical-system-design-overview)
  - [Schematic Overview](#electronic-schematic-overview)
  - [Assembled Electronics](#assembled-data-acquisition-electronics-overview)
- [Software System Design](#high-level-software-system-design-overview)
  - [Simple GUI for Version 1.1](#simple-gui-for-version-11)
  - [Sample Software Code](#sample-software-code)
  - [Sample Firmware Code](#sample-firmware-code)
- [Mechanical Design](#mechanical-frame-cad-design-overview)
  - [Assembled Frame](#assembled-sample-frame)
  - [Mounted Electronics](#electronics-mounted-on-frame)
- [Documentation](#documentation-and-implementation)
- [Tech Stack and Specs](#tech-stack-and-specs)
- [Parts](#parts)
- [Historical Context](#profiler-from-30-years-ago)

## Purpose

Purpose-built to work with the **Heavy Vehicle Simulator (HVS) system**, the ORP delivers end-to-end **systems engineering** for tracking pavement wear under simulated traffic conditions. Through repeated verification via external encoder sensors and validation via a 24/7 HVS Crew, the ORP system collects accurate degradation metrics, creating highly detailed point clouds and digital maps of road surfaces. These insights are pivotal in optimizing roads for the state of California. The end goal of this project is to enable all road research labs in the world with the ability to accurately assess how their road design degrades and performs overtime.

<p align="center">
  <img src="https://github.com/user-attachments/assets/80c31641-4dbb-49a7-ad4e-a4b5ba6d7d86" alt="1-s2 0-S1996681417300354-gr6">
</p>
<div align="center"> Figure 1.0 (Heavy Vehicle Simulator) </div>

## Future Work and Integrating into OpenUSD for more efficient road degradation tracking in California
To integrate ORP’s point cloud data into OpenUSD, the UsdGeomPoints schema will be used to represent sub-millimeter road surface deformations. Each point will include attributes like position (X,Y,ZX,Y,Z), normals, color, and custom degradation metrics. The data pipeline starts with preprocessing raw outputs from ORP (e.g., .txt, .ply), which are then converted into USD files using Python’s USD libraries. Surface reconstruction algorithms, such as Poisson reconstruction, can transform point clouds into detailed meshes stored as UsdGeomMesh. Time-series visualization of road degradation over simulated traffic cycles will leverage USD’s animation capabilities, enabling dynamic analysis. Once generated, USD files can be validated with tools like USDView or NVIDIA Omniverse for real-time visualization and shared for collaborative research. This pipeline enables scalable, accurate modeling of road performance, paving the way for global adoption in road research.

# Core Team
- **Asad Melibaev**
  [GitHub Profile](https://github.com/TETRA888)

# <div align ="center"> High-Level Electrical System Design Overview </div>
![ElectricalSystemDiagram(1)](https://github.com/user-attachments/assets/d2793204-312c-4bae-87c7-b930093b7640)
### <div align="center"> Figure 2.0 (Abstract overview of the electronic connections) </div>

# <div align ="center"> Electronic Schematic Overview </div>
![image](https://github.com/user-attachments/assets/e47172af-e0ef-41ed-a5eb-c84660c2853c)
### <div align="center"> Figure 2.1 (Schematic of the single axial gantry control) </div>

# <div align ="center"> Assembled Data Acquisition Electronics Overview </div>
![image](https://github.com/user-attachments/assets/57f5ed04-3421-409e-b34d-de18fb0aa7bf)
### <div align="center"> Figure 2.2 (Assembled electronics) </div>

# <div align ="center"> High-Level Software System Design Overview </div>
<p align = "center">
<img src = "https://github.com/user-attachments/assets/fe528e88-6bc0-46dd-bb4b-45c65ca7cced" alt="1-s2 0-S1996681417300354-gr6">
</p>

### <div align="center"> Figure 3.0 (Data flow) </div>


## Simple Gui for version 1.1
![image](https://github.com/user-attachments/assets/679ff62e-25ae-47dd-9d94-3f559744e15a)

## Sample Software Code
```python
import serial
import time
import numpy as np
import open3d as o3d

# Open the serial connection
ser = serial.Serial('/dev/ACM1', 115200, timeout=1)
time.sleep(2)  # Give the connection a moment to initialize

# Send the start command to the Arduino
ser.write(b'START\n')
print("Start command sent to Arduino")

# Function to load point data from a text file
def load_point_data(file_path):
    points_data = np.loadtxt(file_path, delimiter=' ', dtype=float)
    return points_data

# Read the data sent back by the Arduino
data_points = []

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        if line.startswith("DATA:"):
            try:
                _, values = line.split("DATA:")
                x, y, z = map(float, values.split(","))
                print(f"X: {x}, Y: {y}, Z: {z}")
                # Store the data points
                data_points.append((x, y, z))
            except ValueError:
                print("Parsing error!")

    # Break out of the loop if you want to stop reading (you can define a condition)
    if len(data_points) >= 100:  # for example, stop after 100 points
        break

# Convert collected points to NumPy array
points_data = np.array(data_points)

# Ensure the data is in the correct shape
if points_data.shape[1] != 3:
    raise ValueError("Each line in the data must contain 3 values: x, y, z")

# Create Open3D point cloud
pcd = o3d.geometry.PointCloud()
pcd.points = o3d.utility.Vector3dVector(points_data)

# Estimate normals for the point cloud
pcd.estimate_normals(search_param=o3d.geometry.KDTreeSearchParamHybrid(radius=0.1, max_nn=30))

# Perform Poisson reconstruction
mesh, densities = o3d.geometry.TriangleMesh.create_from_point_cloud_poisson(pcd, depth=9)

# Visualize the result
o3d.visualization.draw_geometries([mesh])

# Optionally save the mesh to a file
o3d.io.write_triangle_mesh("output_mesh.ply", mesh)

# Close the serial connection
ser.close()
```

## Sample Firmware Code
```cpp
/*
* Submilimeter X-Axis gantry control code by Asad Melibaev
* This code will be broken down into a multi-file program once debugging and further testing is completed
*/

#include <AccelStepper.h> // Stepper motor library with fine controls
#include <math.h>
#define PI 3.14159265358979323846
#define RC 0.1466275659824047 // Rotary calibration constant calculated by A.M
#define CN 1.33351439541 // Conversion constant calculated by A.M

/*
* Connect corresponding pins to the DM542 stepper motor driver 
*/
const int stepPin = 13;    // STEP pin connected to pin 13
const int dirPin = 12;     // DIR pin connected to pin 12
const int enablePin = 9;   // EN pin connected to pin 9 (optional)

/*
Connect corresponding encoder pins to the microcontroller
*/
const int encoderPinA = 21; // Encoder Channel A
const int encoderPinB = 20; // Encoder Channel B

/*
* Create the stepper object with driver mode enabled by setting the first param to 1
*/
AccelStepper stepper(1, stepPin, dirPin);

/*
* Encoder variables will be constantly changing therefore are set to volatile
* This ensures the compiler does not optimize or store stuff in cache
*/
volatile long encoderPosition = 0; // Current position
volatile bool lastAState = LOW;     // Last state of encoder pin A
volatile int offsetFromExpected = 0;

/*
* Update encoder vars as soon as position changes
*/
void updateEncoder() {
    bool currentAState = digitalRead(encoderPinA);
    bool currentBState = digitalRead(encoderPinB);

    if (currentAState != lastAState) { // Only update on change of state
        if (currentBState == currentAState) {
            encoderPosition++; // Clockwise
        } else {
            encoderPosition--; // Counterclockwise
        }
    }

    lastAState = currentAState; // Update last state

    // Void returns nothin 
}

/*
* Adjusts stepper motor location to correct an offset caused during movement
* @param offsetFromExpected is the amount of steps that the position is offset by
*/
void correctLocation(int offsetFromExpected){
    stepper.moveTo(offsetFromExpected); // Set target position
    while (stepper.distanceToGo() != 0) { // Move until the target position is reached and verified by encoder
        stepper.run(); // Run the stepper motor
    }

    // Void returns nothing
}

/*
* This function verifies that the accuracy is within the submilimeter tolerence and if its not it adjusts the offsetFromExpected value
@ param distance: is the distance in mm
@ param pulses: is the amount of pulses that have been sent to the stepper motor
*/
void verifiedAccuracy(int distance, int pulses){
  double TOLERANCE = 0.1; // in mm

  if (fabs(encoderPosition * RC - distance) > TOLERANCE){
    offsetFromExpected = pulses*CN - encoderPosition;
  }

  // Void Returns nothing
}

/*
* This function moves the rail by the specified distance in mm
@param distance: Is the distance that it will move in mm
*/
void move_rail_x(int distance) {
    int pulses = (distance / (2 * PI * 28)) * 3200; // Calculate pulses for the given distance // 0.1466 mm per pulse to be exact
    stepper.moveTo(pulses); // Set target position
    while (stepper.distanceToGo() != 0) { // Move until the target position is reached and verified by encoder
        stepper.run(); // Run the stepper motor
    }

    /*
    verifiedAccuracy(distance, pulses);

    if (offsetFromExpected != 0){
      correctLocation(offsetFromExpected);
      offsetFromExpected = 0;
    }
    */

    // Void returns nothing
}

/*
* Initialize required pins, interrupts, and serial communication between the PC and microcontroller
*/
void setup() {
    Serial.begin(115200);
    pinMode(enablePin, OUTPUT); // Set the enable pin as an output
    digitalWrite(enablePin, LOW); // Enable the driver
    
    // Set encoder pins as inputs with pull-ups
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);
    
    // Attach interrupts for encoder channels
    attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);

    // Set the maximum speed and acceleration
    stepper.setMaxSpeed(2000); // 2000mm/s
    stepper.setAcceleration(1000); // 400mm/s^2

    // Void returns nothing
}

/*
* Main function where the gantry will move
* Currently setup to check calibration
*/
void loop() {
    int distance = 500; // Distance is in millimeters (1 meter)
    move_rail_x(distance); // Move the rail by the specified distance

    // Optionally, print encoder position for debugging
    Serial.print("Encoder Position: ");
    Serial.print(encoderPosition*RC);
    Serial.println(" mm");
    
    delay(1000); // Wait for 1 second before the next move

    // Void returns nothing
}
```

# <div align ="center"> Mechanical Frame CAD Design Overview </div>
![370409415-1df8b744-70b0-4bfa-a11d-afa3a9b27c9c](https://github.com/user-attachments/assets/2b34529f-097a-49ef-b5af-636d91c5e30e)
### <div align = "Center" > Figure 4.0 (3D Blender Render) </div>

## Assembled Sample Frame
![image](https://github.com/user-attachments/assets/19168a9b-73d9-4032-93db-c142c46b60a5)
### <div align = "Center" > Figure 4.1 (2nd Design Iteration Of Frame) </div>

## Electronics mounted On Frame:
![image](https://github.com/user-attachments/assets/0f8856cc-a083-4535-b870-cc8844e09d20)
### <div align = "Center"> Figure 4.2 (Frame with Electronics) </div>

# Documentation and Implementation:
1. [Wiki](https://github.com/TETRA888/Profilometer/wiki)

# Tech Stack and Specs:
 ![Static Badge](https://img.shields.io/badge/Language-C-blue)
 ![Static Badge](https://img.shields.io/badge/Language-Python-red)
 ![Static Badge](https://img.shields.io/badge/Tech-RaspberryPi-hotpink)
 ![Static Badge](https://img.shields.io/badge/Tech-Arduino-darkblue)
 ![Static Badge](https://img.shields.io/badge/Tech-LiDAR-purple)
 ![Static Badge](https://img.shields.io/badge/Tech-64MP%20Camera-purple)
 ![Static Badge](https://img.shields.io/badge/Tech-%20Class%20II%20Precision%20Laser-purple)
 ![Static Badge](https://img.shields.io/badge/Precision-Submilimeter-green)
 ![Static Badge](https://img.shields.io/badge/Accuracy-Submilimeter-green)
 ![Static Badge](https://img.shields.io/badge/Repeatibility-Submilimeter-green)

# Parts:
1. [Exact quantities and parts needed for single axial system](https://docs.google.com/spreadsheets/d/1ZoPqY9_Fw6rnbfQ8UKPL65L5WncEJa40W8i2KiA_dJQ/edit?gid=0#gid=0)
2. [Parts list draft](https://docs.google.com/document/d/1qKMDZtSdquMjX08xfJKCa0uS36UHgNZ3eyHph81zQOM/edit)

# Profiler from 30 years ago:
<p align="center"> 
<img src="https://github.com/user-attachments/assets/5ffa2545-2cf1-40bd-9891-e65d8baee50d">
</p>

### <div align = "Center" > Figure 5.0 (The First Profiler) </div>
