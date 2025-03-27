#ifndef STATUS_INDICATORS_HPP
#define STATUS_INDICATORS_HPP

#include <Arduino.h>

extern int lightPin1;

extern int lightPin2;

extern int lightPin3;

void lightIndicatorSetup();
void lightIndicatorActivation(int status, int activation);

#endif