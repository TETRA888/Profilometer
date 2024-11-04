// GantryControl.h
#ifndef GANTRY_CONTROL_H
#define GANTRY_CONTROL_H

#include <AccelStepper.h>
#include <math.h>

// Constants
extern const uint32_t INFINITY_INT; // Represents a large integer value
extern const double RC;              // Rotary calibration constant
extern const double CN;              // Conversion constant
extern const int stepPin;            // Pin for stepper motor step signal
extern const int dirPin;             // Pin for stepper motor direction signal
extern const int enablePin;          // Pin to enable the stepper driver
extern const int encoderPinA;        // Encoder pin A
extern const int encoderPinB;        // Encoder pin B
extern const int EndStop0;           // Pin for end stop sensor 0
extern const int EndStop1;           // Pin for end stop sensor 1
extern volatile long encoderPosition; // Current position of the encoder
extern volatile bool lastAState;     // Last state of encoder pin A
extern volatile int offsetFromExpected; // Offset from expected position

// Function declarations
void updateEncoder();
void correctLocation(int offsetFromExpected);
void verifiedAccuracy(int distance, int pulses);
bool move_rail_x(int distance);
void setupGantry();
bool MovementUnitTest(float distance);
bool CalibrateSystem();

#endif // GANTRY_CONTROL_H
