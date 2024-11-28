#include "endStopOutput.hpp"

const int endStop0 = 2; // Input pin for the endstop that is closest to the encoder
const int endStop1 = 3; // Input pin for the endstop that is closest to the motor

/*
    Simply setting up the input pins for the endstops
*/

void setupEndStops(){
    pinMode(endStop0, INPUT); // Setting it up with a pull down resistor to reduce noise and avoid false positives
    pinMode(endStop1, INPUT); // Setting it up with a pull down resistor to reduce noise and avoid false positives
}

/*
    Updating the current state of the endstops
*/

void checkEndStopStatus(){
    digitalRead(endStop0);
    digitalRead(endStop1);
}

