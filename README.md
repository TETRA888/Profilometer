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

// Define the pins
#define STEP_PIN 13
#define DIR_PIN 12
#define ENABLE_PIN 11

// Create an instance of AccelStepper
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  // Set the enable pin as output
  pinMode(ENABLE_PIN, OUTPUT);
  
  // Enable the driver (LOW to enable for some drivers, change if needed)
  digitalWrite(ENABLE_PIN, LOW);

  // Set max speed and acceleration
  stepper.setMaxSpeed(1000);    // Adjust as needed
  stepper.setAcceleration(500); // Adjust as needed
  
  // Set the initial target position
  stepper.moveTo(1000); // Number of steps to move
}

void loop() {
  // Run the motor to the target position
  if (stepper.distanceToGo() == 0) {
    // Change direction when target is reached
    stepper.moveTo(-stepper.currentPosition());
  }

  stepper.run(); // Non-blocking function to run the motor
}
```
# Spec sheet for frame
![image](https://github.com/user-attachments/assets/b00d398e-fe64-4068-9114-2de268df600d)

