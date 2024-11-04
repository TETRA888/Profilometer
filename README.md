#  <div align="center"> Open Road Profiler (ORP) </div>

The **Open Road Profiler (ORP)** is an advanced, open-source system engineered to map the degradation of theoretical road designs developed by Caltrans. This precision gantry platform leverages a robust integration of **computer vision**, **LiDAR sensing**, and **optical measurement** technologies, including a Garmin LiDAR-Lite v3HP, a 64MP high-resolution camera, and a Class II precision laser, to capture sub-millimeter road surface details crucial for high-fidelity data.

## Purpose

Purpose-built to work with the **Heavy Vehicle Simulator (HVS) system **, the ORP delivers end-to-end **systems engineering** for tracking pavement wear under simulated traffic conditions. Through repeated **V&V (Verification & Validation)** cycles via external encoder sensors, the ORP system collects accurate degradation metrics, creating highly detailed point clouds and digital maps of road surfaces. These insights are pivotal in optimizing roads for the state of California. The end goal of this project is to enable all road research labs in the world with the ability to accurately assess how their road design degrades and performs overtime.

## Project Leadership

Led by **Asad Melibaev**, the project emphasizes a modular, scalable design, ensuring smooth integration with existing HVS systems and adaptability to future sensing technologies. With support from a dedicated team of R&D engineers, PhD researchers, and machinists, the ORP’s goal is to enable precise, actionable data analysis to inform road composition improvements and advance Caltrans' pavement research efforts.

<p align="center">
  <img src="https://github.com/user-attachments/assets/80c31641-4dbb-49a7-ad4e-a4b5ba6d7d86" alt="1-s2 0-S1996681417300354-gr6">
</p>
<div align="center"> Figure 1.0 (Heavy Vehicle Simulator) </div>

## Key Contributors

### Core Team
- **Asad Melibaev**  
  *(Systems Lead)*  
  [GitHub Profile](https://github.com/TETRA888)

### Help, Advice and Guidance from
- **Andrew Cobb**  
  *(Sr. Machinst)*  

- **Kin Yen**  
  *(Sr. Development Engineer)*  

- **Stephanus Louw**  
  *(Lead Geotechnical Engineer)*

- **Rauf Zokhrabov**  
  *(Documentation Assistant)*
  *(University of Illinois Urbana-Champaign)*
  
### <div align = "center"> Acknowledgments </div>
I would like to express my sincere gratitude to my Electrical Engineering professors and faculty members at UC Davis for their invaluable support in designing the system and deepening my understanding of circuit design. Their expertise and guidance have been instrumental in the development of this project.
  
## <div align = "center"> Collaborating Institutions </div>
![PIC_Logo_Version3-1](https://github.com/user-attachments/assets/17cbd89d-2607-47e3-9363-86e45fdb013c)
![cee_logo_125px](https://github.com/user-attachments/assets/006992ca-56f5-472b-9f67-138f40989d7f)
![ece_logo_125px](https://github.com/user-attachments/assets/dc39ba0e-d0da-407a-b563-ca034a3d2a44)

# <div align="center"> High-Level Multi System Integration Overview </div>
![image](https://github.com/user-attachments/assets/8839c64d-6e4a-4f62-a997-80743c14610c)
### <div align="center"> Figure 2.0 (The connection of different subsystems to collect data on stress tested roads) </div>

# <div align ="center"> High-Level Electrical System Design Overview </div>
![Electronic System Overview](https://github.com/user-attachments/assets/a1dfd340-66dc-46f6-a01b-4a3a1e8daf18)
### <div align="center"> Figure 3.0 (Abstract overview of the electronic connections) </div>

# <div align ="center"> Electronic Schematic Overview </div>
![image](https://github.com/user-attachments/assets/e47172af-e0ef-41ed-a5eb-c84660c2853c)
### <div align="center"> Figure 4.0 (Schematic of the single axial gantry control) </div>

# <div align ="center"> Assembled Data Acquisition Electronics Overview </div>
![image](https://github.com/user-attachments/assets/d127bfc2-c86a-42aa-ab2a-80563844572e)
### <div align="center"> Figure 5.0 (The nervous system of the gantry) </div>

# <div align ="center"> High-Level Software System Design Overview </div>
![High Level Software](https://github.com/user-attachments/assets/9c1f1827-0924-40f6-bd45-1ba07a533b19)
### <div align="center"> Figure 6.0 (Data flow) </div>

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

# <div align ="center"> High-Level Firmware System Design Overview </div>
![Software Design](https://github.com/user-attachments/assets/5eb6d624-5567-4f5e-95c3-a54661827108)
### <div align="center"> Figure 7.0 (Data collection) </div>

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
### <div align = "Center" > Figure 8.0 (3D Blender Render) </div>

## Assembled Sample Frame
![image](https://github.com/user-attachments/assets/19168a9b-73d9-4032-93db-c142c46b60a5)
### <div align = "Center" > Figure 9.0 (2nd Design Iteration Of Frame) </div>

# Documentation and Implementation:
1. [Wiki](https://github.com/TETRA888/Profilometer/wiki)

# Tech Stack and Specs:
 ![Static Badge](https://img.shields.io/badge/Language-C-blue)
 ![Static Badge](https://img.shields.io/badge/Language-Python-red)
 ![Static Badge](https://img.shields.io/badge/Tech-LiDAR-purple)
 ![Static Badge](https://img.shields.io/badge/Tech-64MP%20Camera-purple)
 ![Static Badge](https://img.shields.io/badge/Tech-%20Class%20II%20Precision%20Laser-purple)
 ![Static Badge](https://img.shields.io/badge/Precision-Submilimeter-green)
 ![Static Badge](https://img.shields.io/badge/Accuracy-Submilimeter-green)
 ![Static Badge](https://img.shields.io/badge/Repeatibility-Submilimeter-green)

# Parts:
1. [Exact quantities and parts needed for single axial system](https://docs.google.com/spreadsheets/d/1ZoPqY9_Fw6rnbfQ8UKPL65L5WncEJa40W8i2KiA_dJQ/edit?gid=0#gid=0)
2. [Parts list draft](https://docs.google.com/document/d/1qKMDZtSdquMjX08xfJKCa0uS36UHgNZ3eyHph81zQOM/edit)

# Profiler from 30 years ago
<p align="center"> 
<img src="https://github.com/user-attachments/assets/5ffa2545-2cf1-40bd-9891-e65d8baee50d">
</p>

