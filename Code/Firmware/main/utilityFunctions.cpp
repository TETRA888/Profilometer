#include "utilityFunctions.hpp"

const uint32_t positiveInfinity = UINT32_MAX;
volatile long endEncoderPosition = 0;

AccelStepper stepper1(1, stepPin, dirPin);

/*
    Simple function that will home the block to the encoder
*/

bool homeRailX(){
    stepper1.moveTo(positiveInfinity);
    attachInterrupt(digitalPinToInterrupt(endStop0), checkEndStopStatus, HIGH);

    while(endStop0 != HIGH){
        checkEndStopStatus();
        stepper1.run();
    }

    stepper1.stop();

    return true;
}

/*
    Simple function that will check if the system is calibrated by homing it and then sending it 2500mm forwards and comparing that
    to the value that the encoder recorded.
*/

bool calibrationCheck(){
    homeRailX();

    setupEncoderInterrupts();
    encoderPosition = 0;

    bool reached = moveRailX(-2500);

    if(reached && (endStop1 == HIGH)){
        bool returned = moveRailX(2500);
        endEncoderPosition = encoderPosition;
    }
    else{
        lightIndicatorActivation(1,1);
        return false;
    }

    if(endEncoderPosition == 2500){
        endEncoderPosition = 0;
        return true;
    }
    else{
        lightIndicatorActivation(1,1);
        return false;
    }
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
        Serial.print("distance");
        Serial.println();
    }
}

/*
    Simple function that tells the Raspberry Pi the status of the data collection
*/

void sendDataToRaspberryPi(){
    Serial.println("DATA_COLLECTION_COMPLETE");
}