#ifndef UTILITY_FUNCTIONS_HPP
#define UTILITY_FUNCTIONS_HPP

#include <Arduino.h>
#include <AccelStepper.h>
#include "stepperMotorControl.hpp"
#include "endStopOutput.hpp"
#include "encoderOutput.hpp"
#include "statusIndicators.hpp"
#include "laserOutput.hpp"

extern const uint32_t positiveInfinity;
extern volatile long endEncoderPosition;
extern int endStop0;
extern int endStop1;

float homeRailX();
bool calibrationCheck();
void collectDataPoints(float startX, float endX, float stepSize);
void scanMoveless(float startX, float endX, float stepSize);
void moveScanless(float startX, float endX, float stepSize);

#endif