#include "statusIndicators.hpp"

int lightPin1 = 28;
int gndPin1 = 29;

int lightPin2 = 34;
int gndPin2 = 36;

int lightPin3 = 35;
int gndPin3 = 37;

/*
    Setting up the pins for the status lights
*/

void lightIndicatorSetup(){
    pinMode(lightPin1, OUTPUT);
    pinMode(lightPin2, OUTPUT);
    pinMode(lightPin3, OUTPUT);

    pinMode(gndPin1, OUTPUT);
    pinMode(gndPin2, OUTPUT);
    pinMode(gndPin2, OUTPUT);

    digtialWrite(lightPin1, LOW);
    digtialWrite(lightPin2, LOW);
    digtialWrite(lightPin3, LOW);

    digtialWrite(gndPin1, LOW);
    digtialWrite(gndPin2, LOW);
    digtialWrite(gndPin3, LOW);
}

/*
    This is a function that will trigger the requested LED light on the microcontroller

    @param status is the light that you want to turn on
            - 1 is the Red LED
            - 2 is the Yellow LED
            - 3 is the Green LED
    
    @param activation is what state you want the LED to be in
            - 1 is LED ON
            - 0 is LED OFF
*/

void lightIndicatorActivation(int status, int activation){
    switch(status){
        case 1:
            if(activation == 1){
                digitalWrite(lightPin1, HIGH);
            }
            else{
                digitalWrite(lightPin1, LOW);
            }
        case 2:
            if(activation == 1){
                digitalWrite(lightPin2, HIGH);
            }
            else{
                digitalWrite(lightPin2, LOW);
            }
        case 3:
            if(activation == 1){
                digitalWrite(lightPin3, HIGH);
            }
            else{
                digitalWrite(lightPin3, LOW);
            }
            
        default: // Do nothing
    }
}