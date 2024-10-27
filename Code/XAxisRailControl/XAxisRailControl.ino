/*
Submilimeter X-Axis gantry control code by Asad Melibaev
*/

#include <AccelStepper.h>
#include <math.h>
#define PI 3.14159265358979323846 // Simply the value of PI
#define RC 0.1466275659824047 // Rotary calibration constant calculated by A.M

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
volatile int offsetFromExpected = 0;

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

void correctLocation(int offsetFromExpected){
    stepper.moveTo(offsetFromExpected); // Set target position
    while (stepper.distanceToGo() != 0) { // Move until the target position is reached and verified by encoder
        stepper.run(); // Run the stepper motor
    }
}

void verifiedAccuracy(int distance, int pulses){
  double TOLERANCE = 0.1; // in mm

  if (fabs(encoderPosition * RC - distance) > TOLERANCE){
    offsetFromExpected = pulses*1.33351439541 - encoderPosition;
  }
}

void move_rail_x(int distance) {
    int pulses = (distance / (2 * PI * 28)) * 3200; // Calculate pulses for the given distance
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
    Serial.print(encoderPosition*RC);
    Serial.println(" mm");
    
    delay(1000); // Wait for 1 second before the next move
}