#include "stepperMotorControl.hpp"
#include "endStopOutput.hpp"
#include "encoderOutput.hpp"
#include "laserOutput.hpp"
#include "statusIndicators.hpp"
#include "utilityFunctions.hpp"

/*
    This is the main setup function which will setup the peripherals of all of the functions

    The current version of the profiler has the following hardware:
    - 2x Proximity sensors for end stops on both ends of the rail
    - 1x Rotary encoder for the rail to check for accurate movement
    - 1x High Torque NEMA 23 stepper motor for the axis
    - 1x Laser sensor for the profiler to measure the distance
    - 3x Indicator lights to indicate the status of the profiler

    NOTES:
    The rotary encoder will only be used during the calibration check of the profiler to ensure that the system is calibrated

    @author Asad Melibaev <amelibaev@ucdavis.edu>
    @version 2.0
    @since: 2025-21-09
*/

/*
  The setup function is where the setup functions of the peripherals will be called
*/
void setup(){
    Serial.begin(115200); // Begin serial communication at 115200 bits per second

    /*
      @param speed Setting speed to 2000 mm/s
      @param acceleration Setting acceleration to 1000mm/s^2
    */
    setupStepperMotors(2000, 1000);

    setupEncoder(); // Setup encoder input pins

    //setupLaser(); // Setup laser sensor       //FIXME WHEN YOU CONNECT A LASER, LIDAR OR ANY OTHER SENSOR

    homeRailX(); // Home the rail

    lightIndicatorSetup(); // setup indicator light inputs pins

    /*
      @param arg0 is the light that you want to turn on
             - 1 is the Green LED
             - 2 is the Yellow LED
             - 3 is the Red LED
      @param arg1 is what state you want the LED to be in
              - 1 is LED ON
              - 0 is LED OFF  
    */
    lightIndicatorActivation(1, 1); // Green light indicating that everything is functioning

    /*
      NOTES:
      The setup laser function only works for the specific KEYENCE LB1000 laser that I setup at the time
      If you are using a different laser sensor, you will need to modify the setupLaser function to accomodate for the different sensor
      You can also write a different function to make it work with your sensor
    */  
}

/*
  A simple function that will turn on only the yellow light to indicate that a function is in progress
*/
void functionInprogress(){
  lightIndicatorActivation(1, 0);
  lightIndicatorActivation(2, 1);
  lightIndicatorActivation(3, 0);
}


/*
  This is where we will be constantly monitoring the actions that the Raspberry Pi is requesting for us to perform
*/
void loop(){

  if (Serial.available() > 0){
    lightIndicatorActivation(1,1); // Turn on green light

    String command = Serial.readStringUntil('\n');

    if(command == "START"){
      functionInprogress();
      collectDataPoints(0, 2500, 0.1); // This is 25000 data points over the span of 2.5 meters
      Serial.println("DATA_COLLECTION_COMPLETE");
    }

    else if (command == "CALIBRATE"){
      functionInprogress();
      if(calibrationCheck()){
        Serial.println("CALIBRATION_SUCCESSFUL");
      }
      else{
        Serial.println("CALIBRATION_FAILED");
      }
    }

    else if (command == "HOME"){
      functionInprogress();
      homeRailX();
      Serial.println("HOME_COMPLETE");
    }

    /* 
    debugging commands
    */
    else if (command == "SCANMOVELESS"){
      functionInprogress();
      scanMoveless(0, 2500, 0.1);
      Serial.println("DATA_COLLECTION_COMPLETE");
    }

    else if (command == "MOVESCANLESS"){
      functionInprogress();
      moveScanless(0, 2500, 0.1);
      Serial.println("DATA_COLLECTION_COMPLETE");
    }
  }

  else{
    lightIndicatorActivation(3,1); // red light if not serial connection is established with Raspberry Pi
  }
}
