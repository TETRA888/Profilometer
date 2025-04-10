#include "statusIndicators.hpp"

// Green LED
int lightPin1 = 33;

// Yellow LED
int lightPin2 = 32;

// Red LED
int lightPin3 = 52;

/*
    Setting up the pins for the status lights
*/

void lightIndicatorSetup(){
    pinMode(lightPin1, OUTPUT);
    pinMode(lightPin2, OUTPUT);
    pinMode(lightPin3, OUTPUT);

    digitalWrite(lightPin1, LOW);
    digitalWrite(lightPin2, LOW);
    digitalWrite(lightPin3, LOW);
}

/*
    This is a function that will trigger the requested LED light on the microcontroller

    @param status is the light that you want to turn on
            - 1 is the Green LED
            - 2 is the Yellow LED
            - 3 is the Red LED
    
    @param activation is what state you want the LED to be in
            - 1 is LED ON
            - 0 is LED OFF
*/

void lightIndicatorActivation(int status, int activation){
    digitalWrite(lightPin1, LOW);
    digitalWrite(lightPin2, LOW);
    digitalWrite(lightPin3, LOW);
    
    switch(status){
        case 1:
            if(activation == 1){
                digitalWrite(lightPin1, HIGH);
                break;
            }
            else{
                digitalWrite(lightPin1, LOW);
                break;
            }
        case 2:
            if(activation == 1){
                digitalWrite(lightPin2, HIGH);
                break;
            }
            else{
                digitalWrite(lightPin2, LOW);
                break;
            }
        case 3:
            if(activation == 1){
                digitalWrite(lightPin3, HIGH);
                break;
            }
            else{
                digitalWrite(lightPin3, LOW);
            }
    }
}