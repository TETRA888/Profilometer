# Open Road Profiler (ORP)

The **Open Road Profiler (ORP)** is an advanced, open-source system engineered to map the degradation of theoretical road designs developed by Caltrans. This precision gantry platform leverages a robust integration of **computer vision**, **LiDAR sensing**, and **optical measurement** technologies, including a Garmin LiDAR-Lite v3HP, a 64MP high-resolution camera, and a Class II precision laser, to capture sub-millimeter road surface details crucial for high-fidelity data.

## Purpose

Purpose-built to support the **Heavy Vehicle Simulator (HVS)**, the ORP delivers end-to-end **systems engineering** for tracking pavement wear under simulated traffic conditions. Through repeated **V&V (Verification & Validation)** cycles via external encoder sensors, the ORP system collects accurate degradation metrics, creating highly detailed point clouds and digital maps of road surfaces. These insights are pivotal in optimizing roads for the state of California.

## Project Leadership

Led by **Asad Melibaev**, the project emphasizes a modular, scalable design, ensuring smooth integration with existing systems and adaptability to future sensing technologies. With support from a dedicated team of R&D engineers, PhD researchers, and machinists, the ORP’s goal is to enable precise, actionable data analysis to inform road composition improvements and advance Caltrans' pavement research efforts.

![1-s2 0-S1996681417300354-gr6](https://github.com/user-attachments/assets/80c31641-4dbb-49a7-ad4e-a4b5ba6d7d86)

## Table of Contents
1. [Project Leadership](##-Key-Contributors)
2. [Collaborating Institutions](#collaborating-institutions)
3. [System Design Overview](#High-Level-Multi-System-Integration-Overview)
5. [Key Features/Specifications](#Tech-Stack-and-Specs)
8. [Code Examples](#Sample-code-with-active-offsetting-for-submilimeter-accuracy-debugging-and-testing)

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
  
### Acknowledgments
I would like to express my sincere gratitude to my Electrical Engineering professors and faculty members at UC Davis for their invaluable support in designing the system and deepening my understanding of circuit design. Their expertise and guidance have been instrumental in the development of this project.
  
## Collaborating Institutions
![PIC_Logo_Version3-1](https://github.com/user-attachments/assets/17cbd89d-2607-47e3-9363-86e45fdb013c)
![cee_logo_125px](https://github.com/user-attachments/assets/006992ca-56f5-472b-9f67-138f40989d7f)
![ece_logo_125px](https://github.com/user-attachments/assets/dc39ba0e-d0da-407a-b563-ca034a3d2a44)

# High-Level Multi System Integration Overview
![Systems Diagram(1)](https://github.com/user-attachments/assets/35b1d3e9-78a1-4742-bf07-a832225d76c4)

# High-Level Electrical System Design Overview
![Electronic System Overview(1)](https://github.com/user-attachments/assets/d6533f4a-1731-4d4b-939f-d08a8defeab5)

# High-Level Software System Design Overview
![High Level Software](https://github.com/user-attachments/assets/9cfec3ed-bea4-4a3b-860d-f29a711aa0e1)

# Low-Level Embedded Software System Design Overview
![Software Design](https://github.com/user-attachments/assets/b4a4c98d-c5f1-4c48-93e9-cc25088d4ced)

# Mechanical Frame Design And Parts Overview
![image](https://github.com/user-attachments/assets/1d78618b-e48f-44f0-9139-ca29d3cbe0ff)

# Documentation and Implementation:
1. [Wiki](https://github.com/TETRA888/Profilometer/wiki)

# Tech Stack and Specs:
- ![Static Badge](https://img.shields.io/badge/Language-C-blue)
- ![Static Badge](https://img.shields.io/badge/Language-Python-red)
- ![Static Badge](https://img.shields.io/badge/Tech-LiDAR-purple)
- ![Static Badge](https://img.shields.io/badge/Tech-64MP%20Camera-purple)
- ![Static Badge](https://img.shields.io/badge/Tech-%20Class%20II%20Precision%20Laser-purple)
- ![Static Badge](https://img.shields.io/badge/Precision-Submilimeter-green)
- ![Static Badge](https://img.shields.io/badge/Accuracy-Submilimeter-green)
- ![Static Badge](https://img.shields.io/badge/Repeatibility-Submilimeter-green)

# Parts:
1. [Parts list Wiki](https://docs.google.com/document/d/1qKMDZtSdquMjX08xfJKCa0uS36UHgNZ3eyHph81zQOM/edit)
2. [Google Sheets containing exact quantities and parts needed for single axial system](https://docs.google.com/spreadsheets/d/1ZoPqY9_Fw6rnbfQ8UKPL65L5WncEJa40W8i2KiA_dJQ/edit?gid=0#gid=0)

# Blender Renders:

![370409415-1df8b744-70b0-4bfa-a11d-afa3a9b27c9c](https://github.com/user-attachments/assets/2b34529f-097a-49ef-b5af-636d91c5e30e)
## <div align = "Center" > Figure 1. (Side view of the 3D model)
</div>

# Low Level Electrical System Design Overview
### Iteration #1 Initial schematic for stepper motor control:

![370549337-e03756ac-cc0a-44d8-81d0-12ec9ca38810](https://github.com/user-attachments/assets/c86bd222-eb04-4c2a-aee0-ba2ea33dbb47)
## <div align = "Center" > Figure 2. (Basic Schematic of the controller)
</div>

# Sample code with active offsetting for submilimeter accuracy debugging and testing
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

# Iteration #1 of the frame assembly
![image](https://github.com/user-attachments/assets/d379a351-0e1b-4eab-8d46-dd3683de833d)
### Some current issues include torsional wobble along the X-Axis which will be planned to replaced by a 8080 aluminum extrusion

# Iteration #1 of the electronics
![image](https://github.com/user-attachments/assets/8821cd9f-d167-477e-ad44-f5d820c94e56)
### Submilimeter encoder calibration completed with the stepper motor

# Sub mill achieved
![image](https://github.com/user-attachments/assets/9b63d809-6dc8-4725-9c5b-83a01d76cedc)

# Utilizing Garmin LIDAR-Lite v3HP for point cloud mapping:
![image](https://github.com/user-attachments/assets/b87a08cc-a08b-48a4-9e66-ddc740305fd2)

# Utilizing 64MP Camera for photogrammetry mapping of the road:
![image](https://github.com/user-attachments/assets/690f08b7-1356-43be-958b-edece788f500)

# Next steps and milestones:
1. Complete encoder calibration for active offset correction
2. Calibrate LiDAR for micrometer precision.
3. Work on parsing location and RGBA data into single points


