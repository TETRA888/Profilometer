# <div align = "Center" > Test Track Profilometer
</div>

# Specs:
- ![Static Badge](https://img.shields.io/badge/Language-C-blue)
- ![Static Badge](https://img.shields.io/badge/Tech-LiDAR-red)
- ![Static Badge](https://img.shields.io/badge/Precision-Submilimeter-green)
- ![Static Badge](https://img.shields.io/badge/Accuracy-Submilimeter-green)
- ![Static Badge](https://img.shields.io/badge/Repeatibility-Submilimeter-green)

# Parts:
1. [Parts list Wiki](https://docs.google.com/document/d/1qKMDZtSdquMjX08xfJKCa0uS36UHgNZ3eyHph81zQOM/edit)
2. [Google Sheets containing exact quantities and parts needed](https://docs.google.com/spreadsheets/d/1ZoPqY9_Fw6rnbfQ8UKPL65L5WncEJa40W8i2KiA_dJQ/edit?gid=0#gid=0)

# Gallery:

![370409415-1df8b744-70b0-4bfa-a11d-afa3a9b27c9c](https://github.com/user-attachments/assets/2b34529f-097a-49ef-b5af-636d91c5e30e)
## <div align = "Center" > Figure 1. (Side view of the 3D model)
</div>

# Schematic:

![370549337-e03756ac-cc0a-44d8-81d0-12ec9ca38810](https://github.com/user-attachments/assets/c86bd222-eb04-4c2a-aee0-ba2ea33dbb47)
## <div align = "Center" > Figure 2. (Basic Schematic of the controller)
</div>

# Code:

```cpp
#include <AccelStepper.h>

// Define a stepper and the pins it will use
const int stepPin = 13;    // STEP pin connected to pin 13
const int dirPin = 12;     // DIR pin connected to pin 12
const int enablePin = 9;  // EN pin connected to pin 9 (optional)

// Create the stepper object with 2 pins (using driver mode)
AccelStepper stepper(1, stepPin, dirPin);

void setup() {
  // Set the enable pin as an output
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // Enable the driver
  
  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(2000);       // Increase if necessary
  stepper.setAcceleration(500);     // Increase if necessary
  stepper.moveTo(500);              // Move to position 500
// Motor setup and formulas
/*
θ = (360/((steps per rev)*(microsteps))) * #pulses
θ is the angle that the shaft has rotated
Current setup is as follows:
400 steps per revolution
2 microsteps
A full 360 degree rotation would require 800 pulses
*/
// Pulley setup and formulas
/*
1 rotation = 800 pulses
distance = (2πr) * number of rotations
*/
}

void loop() {
  // If at the end of travel, reverse direction
  if (stepper.distanceToGo() == 0)
    stepper.moveTo(-stepper.currentPosition());

  stepper.run(); // Run the stepper
}
```
# Spec sheet for frame
![image](https://github.com/user-attachments/assets/1d78618b-e48f-44f0-9139-ca29d3cbe0ff)


