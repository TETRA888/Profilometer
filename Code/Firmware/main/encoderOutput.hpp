#ifndef ENCODER_OUTPUT_HPP
#define ENCODER_OUTPUT_HPP

#include <Arduino.h>

extern const int encoderPinA;
extern const int encoderPinB;
extern volatile double encoderPosition;
extern volatile bool lastAState;

void updateEncoder();
void setupEncoder();
void setupEncoderInterrupts();

#endif