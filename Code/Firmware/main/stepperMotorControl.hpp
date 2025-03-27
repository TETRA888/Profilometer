#ifndef STEPPER_MOTOR_CONTROL_HPP
#define STEPPER_MOTOR_CONTROL_HPP

#include <Arduino.h>
#include "endStopOutput.hpp"
#include <AccelStepper.h>

extern const int stepPin;
extern const int dirPin;
extern const int enablePin;
extern const int powerPin;

extern AccelStepper stepper;

void setupStepperMotors(int speed, int acceleration);
bool moveRailX(int distance);

#endif