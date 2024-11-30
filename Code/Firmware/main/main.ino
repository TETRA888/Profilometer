#include "stepperMotorControl.hpp"
#include "endStopOutput.hpp"
#include "encoderOutput.hpp"
#include "laserOutput.hpp"
#include "statusIndicators.hpp"
#include "utilityFunctions.hpp"

/*
    This is the main setup function which will setup the peripherals of all of the functions
*/

void setup(){
    Serial.begin(115200); // Begin serial communication

    /*
      @param speed Setting speed to 2000 mm/s
      @param acceleration Setting acceleration to 1000mm/s^2
    */
    setupStepperMotors(2000, 1000);
    setupEncoder();
    setupEndStops();
    setupLaser();
    lightIndicatorSetup(); // Indicator lights for live status updates
    calibrationCheck(); // Do a calibration run when turned on
    lightIndicatorActivation(3, 1); // Green light indicating that everything is functioning
}

/*
  This is where we will be constantly monitoring the actions that the Raspberry Pi is requesting for us to perform
*/

void loop(){
  if (Serial.available() > 0){
    lightIndicatorActivation(2,0); // Turn off Yellow light indicator
    String command = Serial.readStringUntil('\n');
    if(command == "START"){
      collectDataPoints(0, 2500, 0.1); // This is 25000 data points over the span of 2.5 meters
      sendDataToRaspberryPi(); // Send an status update to Raspberry Pi
    }
    else if (command == "CALIBRATE"){
      calibrationCheck();
    }
    else if (command == "HOME"){
      homeRailX();
    }
  }
  else{
    lightIndicatorActivation(2,1); // Yellow light if no serial connection
  }
}
