#include "utilityFunctions.hpp"

const uint32_t positiveInfinity = UINT32_MAX;
volatile long endEncoderPosition = 0;

AccelStepper stepper1(1, stepPin, dirPin);

/*
    Simple function that will home the block to the encoder
*/

volatile bool endStopTriggered = false;

void checkEndStopStatus2() {
  endStopTriggered = true;
}

float homeRailX() {
  // Prepare for first end stop detection
  endStopTriggered = false;
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
  attachInterrupt(digitalPinToInterrupt(3), checkEndStopStatus2, HIGH);

  // Move away from base
  stepper.setSpeed(-5000);
  while(!endStopTriggered){
    stepper.runSpeed();
  }
  stepper.stop();
  detachInterrupt(digitalPinToInterrupt(3));

  stepper.setCurrentPosition(0); // Set absolute position to 0
  encoderPosition = 0;

  delay(100); // delay for safety

  // Reverse and prepare to go opposite direction
  endStopTriggered = false;
  attachInterrupt(digitalPinToInterrupt(2), checkEndStopStatus2, HIGH);

  // Move towards base
  stepper.setSpeed(5000);
  while(!endStopTriggered){
    stepper.runSpeed();
  }
  stepper.stop();
  detachInterrupt(digitalPinToInterrupt(2));


  float endPosition = stepper.currentPosition(); // Calculate the current position
  float distanceInMM = (endPosition * (2 * PI * 12.5)) / 3200;

  // Debugging code
  /*
  Serial.print("Second endstop reached. Total distance: ");
  Serial.print(distanceInMM);
  Serial.println(" mm");
  */

  return distanceInMM;
}

/*
    Simple function that will check if the system is calibrated by homing it and then sending it 2500mm forwards and comparing that
    to the value that the encoder recorded.
*/

bool calibrationCheck(){
    setupEncoderInterrupts(); // setup
    encoderPosition = 0;
    //Serial.println(encoderPosition);
    float distanceTravelled = homeRailX();
    detachEncoderInterrupts(); // clean up
    //Serial.println(encoderPosition/6.819);
    // Creating a 2mm fault tolerence
    if(encoderPosition >= 2498 && encoderPosition <= 2502) return true;
}

/*
    Function that will move the rail by a small specified increment and record the data point and send it serially to the Raspberry Pi

    @param StartX is the start location of the scanning
    @param endX is the end location of the scanning
    @param stepSize is the increment of the distance that it will be travelling
*/

void collectDataPoints(float startX, float endX, float stepSize){
    for (float x = startX; x <= endX; x += stepSize){
        moveRailX(stepSize);
        readLaserValue();

        Serial.print("DATA:");
        Serial.print(x);
        Serial.print(",");
        Serial.print("0");
        Serial.print(distance);
        Serial.println();
    }
}

/*
  debugging functions, same as collectDataPoints, but without moving and scanning elements, respectively
*/

void scanMoveless(float startX, float endX, float stepSize){
  for (float x = startX; x <= endX; x += stepSize){
    readLaserValue();

    Serial.print("DATA:");
    Serial.print(x);
    Serial.println();
  }
}

void moveScanless(float startX, float endX, float stepSize){
  for (float x = startX; x <= endX; x += stepSize){
      moveRailX(stepSize);
      Serial.println("moving...");
    }
}

/*
    Simple function that tells the Raspberry Pi the status of the data collection
*/

void sendDataToRaspberryPi(){
    Serial.println("DATA_COLLECTION_COMPLETE");
}




