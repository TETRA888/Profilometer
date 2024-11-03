// GantryControl.cpp
#include "GantryControl.h"
#include <math.h>

const uint32_t INFINITY_INT = UINT32_MAX; // 4294967295
const double RC = 0.1466275659824047;     // Rotary calibration constant
const double CN = 1.33351439541; // Rotary Conversion constant
const int stepPin = 13;
const int dirPin = 12;
const int enablePin = 9;
const int encoderPinA = 21;
const int encoderPinB = 20;
const int EndStop0 = 2;
const int EndStop1 = 3;

volatile long encoderPosition = 0; 
volatile bool lastAState = LOW;     
volatile int offsetFromExpected = 0;

AccelStepper stepper(1, stepPin, dirPin);

void updateEncoder() {
    bool currentAState = digitalRead(encoderPinA);
    bool currentBState = digitalRead(encoderPinB);

    if (currentAState != lastAState) {
        if (currentBState == currentAState) {
            encoderPosition++;
        } else {
            encoderPosition--;
        }
    }

    lastAState = currentAState; 
}

void correctLocation(int offsetFromExpected) {
    stepper.moveTo(offsetFromExpected);
    while (stepper.distanceToGo() != 0) {
        stepper.run();
    }
}

void verifiedAccuracy(int distance, int pulses) {
    double TOLERANCE = 0.1; // in mm

    if (fabs(encoderPosition * RC - distance) > TOLERANCE) {
        offsetFromExpected = pulses * CN - encoderPosition;
    }
}

bool move_rail_x(int distance) {
    int pulses = (distance / (2 * PI * 28)) * 3200; 
    stepper.moveTo(pulses);
    while (stepper.distanceToGo() != 0) {
        stepper.run();
    }
    return true; 
}

void setupGantry() {
    Serial.begin(115200);
    pinMode(EndStop0, INPUT);
    pinMode(EndStop1, INPUT);
    pinMode(enablePin, OUTPUT);
    digitalWrite(enablePin, LOW);
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);
    
    attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);

    stepper.setMaxSpeed(2000);
    stepper.setAcceleration(1000);
}

bool MovementUnitTest(float distance) {
    if (CalibrateSystem()) {
        move_rail_x(distance);
        Serial.print("Encoder Position: ");
        Serial.print(encoderPosition * RC);
        Serial.println(" mm");
        Serial.print("Intended Position: ");
        Serial.print(distance);
        Serial.println(" mm");
        if ((round(encoderPosition * RC * 100.0) / 100.0) == distance)
            Serial.println("Unit test 1 passed");
        return true;
    } else {
        Serial.println("Unit test 1 failed");
        return false;
    }
}

bool CalibrateSystem() {
    int InitialEndStopState = digitalRead(EndStop0);
    int RailDistance = 2500; 
    bool wait = true;
    if (InitialEndStopState == HIGH) {
        while (wait) {
            wait = !(move_rail_x(RailDistance));
        }
        int LastEndStopState = digitalRead(EndStop1);
        if (LastEndStopState == HIGH) {
            move_rail_x(-1 * RailDistance);
            return true;
        } else {
            Serial.println("Positioning verification has failed!!!");
            return false;
        }
    } else {
        Serial.println("Please Move the block to the start position!!!");
        return false;
    }
}
