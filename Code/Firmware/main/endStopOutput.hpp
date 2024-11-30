#ifndef ENDSTOP_OUTPUT_HPP
#define ENDSTOP_OUTPUT_HPP

#include <Arduino.h>

extern const int endStop0;
extern const int endStop1;

void setupEndStops();
void checkEndStopStatus();

#endif
