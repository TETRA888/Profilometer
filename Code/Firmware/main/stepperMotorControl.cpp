#include "stepperMotorControl.hpp"

/*Pins for the DM542 stepper motor driver*/
const int stepPin = 13; // Pulse Output Pin
const int dirPin = 12; // Direction Output Pin
const int enablePin = 11; // Driver Enable Output Pin
const int powerPin = 10; // Driver Power Pin Set To Active Constant 5V

/*
    Creating a motor instance
    @param interface is set to 1 which indicates it is in drivemode

    @param stepPin is the pin which will recieve the pulses

    @param dirPin is the direction pin
*/

/*
    For more information on the AccelStepper library, please visit the following link:
    https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#a8a419121702399d8ac66df4cc47481f4
*/

AccelStepper stepper(1, stepPin, dirPin);

/*
   Initializing the pins that we will be using
*/

void setupStepperMotors(int speed, int acceleration){
    pinMode(enablePin, OUTPUT);
    pinMode(powerPin, OUTPUT);
    digitalWrite(enablePin, LOW); // Setting  the enable pin to GND to enable the driver
    digitalWrite(powerPin, HIGH); // Setting the power pin to 5V

    stepper.setMaxSpeed(speed);
    stepper.setAcceleration(acceleration);
}

/*
    Moves rail to a specified distance
    @param distance is the distance it will move
*/

bool moveRailX(int distance){
    int pulses = (distance / (2*PI*12.5)) * 3200; // Approximate linear travel distance with 3200 steps per revolution and 12.5mm radius shaft

    stepper.move(pulses);
    while (stepper.distanceToGo() != 0){
        stepper.run();
    }

    return true; // returns true if it moved specified distance
}

