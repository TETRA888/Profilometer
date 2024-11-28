#ifndef LASER_OUTPUT_HPP
#define LASER_OUTPUT_HPP

#include <Arduino.h>

extern volatile double sensorValue;
extern volatile double voltage;
extern volatile double distance;

void setupLaser();
void readLaserValue();

#endif