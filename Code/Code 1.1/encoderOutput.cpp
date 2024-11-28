#include "encoderOutput.hpp"

const int enablePin = 9;
const int encoderPinA = 21;
const int encoderPinB = 20;
volatile double encoderPosition = 0;
volatile bool lastAState = LOW;

/*
    Updates the state of the encoder by comparing the current values of A and B
    If the current state is different from the current one it means that a change in position has occured and we need to 
    check both of the channel states. If channel A starts leading, this means that the current channel state of B will match A after A has changed 
    and we will define this as a clockwise rotation. 
    However, if channel B starts leading, this means that the current channel state of A will not match B, and therefore the rotation is reversed, and
    we will define this as a counter clockwise rotation.
*/

void updateEncoder(){
    bool currentAState = digitalRead(encoderPinA);
    bool currentBState = digitalRead(encoderPinB);

    if(currentAState != lastAState){
        if(currentBState == currentAState){
            encoderPosition++;
        }
        else{
            encoderPosition--;
        }
    }

    lastAState = currentAState;
}

/*
    Simply prepares the pins for encoder posititioning
*/

void setupEncoder(){
    pinMode(encoderPinA, INPUT_PULLUP); // Setting up the pin with an internal pull up resistor to stabilize the input for channel A
    pinMode(encoderPinB, INPUT_PULLUP); // Setting up the pin with an internal pull up resistor to stablize the input for channel B
}

void setupEncoderInterrupts(){
    attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE); // Calls updateEncoder if a change in channel A's input has been detected
    attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE); // Calls updateEncoder if a change in channel B's input has been detected
}