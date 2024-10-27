# <div align = "Center" > Open Source 3D Profilometer By Asad Melibaev
</div>

# In collaboration with:
![PIC_Logo_Version3-1](https://github.com/user-attachments/assets/17cbd89d-2607-47e3-9363-86e45fdb013c)
![cee_logo_125px](https://github.com/user-attachments/assets/006992ca-56f5-472b-9f67-138f40989d7f)

# Help and guidance from:
Andrew Cobb, Kin Yen, Stephanus Louw

# Specs:
- ![Static Badge](https://img.shields.io/badge/Language-C-blue)
- ![Static Badge](https://img.shields.io/badge/Tech-LiDAR-red)
- ![Static Badge](https://img.shields.io/badge/Precision-Submilimeter-green)
- ![Static Badge](https://img.shields.io/badge/Accuracy-Submilimeter-green)
- ![Static Badge](https://img.shields.io/badge/Repeatibility-Submilimeter-green)

# Parts:
1. [Parts list Wiki](https://docs.google.com/document/d/1qKMDZtSdquMjX08xfJKCa0uS36UHgNZ3eyHph81zQOM/edit)
2. [Google Sheets containing exact quantities and parts needed](https://docs.google.com/spreadsheets/d/1ZoPqY9_Fw6rnbfQ8UKPL65L5WncEJa40W8i2KiA_dJQ/edit?gid=0#gid=0)

# Renders:

![370409415-1df8b744-70b0-4bfa-a11d-afa3a9b27c9c](https://github.com/user-attachments/assets/2b34529f-097a-49ef-b5af-636d91c5e30e)
## <div align = "Center" > Figure 1. (Side view of the 3D model)
</div>

# Iteration #1 Schematic:

![370549337-e03756ac-cc0a-44d8-81d0-12ec9ca38810](https://github.com/user-attachments/assets/c86bd222-eb04-4c2a-aee0-ba2ea33dbb47)
## <div align = "Center" > Figure 2. (Basic Schematic of the controller)
</div>

# Iteration #1 Code:

```cpp
#include <AccelStepper.h>
#include <math.h>
#define PI 3.14159265358979323846

// Define a stepper and the pins it will use
const int stepPin = 13;    // STEP pin connected to pin 13
const int dirPin = 12;     // DIR pin connected to pin 12
const int enablePin = 9;  // EN pin connected to pin 9 (optional)

// Create the stepper object with 2 pins (using driver mode)
AccelStepper stepper(1, stepPin, dirPin);

void move_rail_x(int distance){
  int pulses = (distance / (2*PI*0.028))*400;
  stepper.moveTo(pulses);
  stepper.run();
}

void setup() {
  pinMode(enablePin, OUTPUT); // Set the enable pin as an output
  digitalWrite(enablePin, LOW); // Enable the driver
  
  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(2000); // 2000mm/s
  stepper.setAcceleration(400); // 400mm/s^2

  // Motor setup and formulas
  /*
  θ = (360/((steps per rev)) * #pulses
  θ is the angle that the shaft has rotated
  Current setup is as follows:
  400 steps per revolution
  A full 360 degree rotation would require 400 pulses
  */

  // Pulley setup and formulas
  /*
  1 rotation = 400 pulses
  distance = (2πr) * number of rotations
  */
}

void loop() {
  int distance = 1; // distance is in meters
  move_rail_x(distance);
}
```

# Iteration #1 Calibrated Code for Submilimeter accuracy
```cpp
#include <AccelStepper.h>
#include <math.h>
#define PI 3.14159265358979323846

// Define pins for the stepper motor
const int stepPin = 13;    // STEP pin connected to pin 13
const int dirPin = 12;     // DIR pin connected to pin 12
const int enablePin = 9;   // EN pin connected to pin 9 (optional)

// Define pins for the encoder
const int encoderPinA = 21; // Encoder Channel A
const int encoderPinB = 20; // Encoder Channel B

// Create the stepper object with driver mode
AccelStepper stepper(1, stepPin, dirPin);

// Variables for encoder position
volatile long encoderPosition = 0; // Current position
volatile bool lastAState = LOW;     // Last state of encoder pin A

// Interrupt service routine to handle encoder changes
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
}

void move_rail_x(int distance) {
    int pulses = (distance / (2 * PI * 28)) * 3200; // Calculate pulses for the given distance
    stepper.moveTo(pulses); // Set target position
    while (stepper.distanceToGo() != 0 && ((encoderPosition*0.1466275659824047) == distance)) { // Move until the target position is reached and verified by encoder
        stepper.run(); // Run the stepper motor
    }
}

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
}

// 6820 pulses
// real travelled distance = 1000/6820 = 0.1466 mm per pulse

void loop() {
    int distance = 500; // Distance is in millimeters (1 meter)
    move_rail_x(distance); // Move the rail by the specified distance

    // Optionally, print encoder position for debugging
    Serial.print("Encoder Position: ");
    Serial.print(encoderPosition*0.1466275659824047);
    Serial.println(" mm");
    
    delay(1000); // Wait for 1 second before the next move
}
```

# Spec sheet for frame
![image](https://github.com/user-attachments/assets/1d78618b-e48f-44f0-9139-ca29d3cbe0ff)

# Sub mill achieved:
![image](https://github.com/user-attachments/assets/ea26056d-1939-45df-84d4-babdae8b881d)



