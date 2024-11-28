#include "laserOutput.hpp"

volatile double sensorValue = 0;
volatile double voltage = 0;
volatile double distance = 0;

/*
    Setting up the pins for the laser
*/

void setupLaser(){
    pinMode(A0, INPUT);
}

/*
    Actively reading the input values of the laser
*/

void readLaserValue(){
    sensorValue = analogRead(A0);
    voltage = sensorValue*(5.0 / 1023.0);
    distance = voltage*20; // 20mm/V is the conversion factor
}