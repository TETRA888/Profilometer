/*
* Submilimeter X-Axis gantry control code by Asad Melibaev
* This code will be broken down into a multi-file program once debugging and further testing is completed
*/

#include <AccelStepper.h> // Stepper motor library with fine controls
#include <math.h>
#define PI 3.14159265358979323846
#define RC 0.1466275659824047 // Rotary calibration constant calculated by A.M
#define CN 1.33351439541 // Conversion constant calculated by A.M

/*
* Constants
*/
const uint32_t INFINITY_INT = UINT32_MAX; // 4294967295

/*
* Connect corresponding pins to the DM542 stepper motor driver 
*/
const int stepPin = 13;    // STEP pin connected to pin 13
const int dirPin = 12;     // DIR pin connected to pin 12
const int enablePin = 9;   // EN pin connected to pin 9 (optional)

/*
Connect corresponding encoder pins to the microcontroller
*/
const int encoderPinA = 21; // Encoder Channel A
const int encoderPinB = 20; // Encoder Channel B

/*
* Connect corresponding induction sensor pins to the microcontroller
*/
const int EndStop0 = 2;       // Pin connected to the sensor's output (use a digital pin)
const int EndStop1 = 3;       // Pin connected to the sensor's output (use a digital pin)
/*
* Create the stepper object with driver mode enabled by setting the first param to 1
*/
AccelStepper stepper(1, stepPin, dirPin);

/*
* Encoder variables will be constantly changing therefore are set to volatile
* This ensures the compiler does not optimize or store stuff in cache
*/
volatile long encoderPosition = 0; // Current position
volatile bool lastAState = LOW;     // Last state of encoder pin A
volatile int offsetFromExpected = 0;

/*
* Update encoder vars as soon as position changes
*/
void updateEncoder() {
    bool currentAState = digitalRead(encoderPinA);
    bool currentBState = digitalRead(encoderPinB);

    if (currentAState != lastAState) { // Only update on change of state
        if (currentBState == currentAState) {
            encoderPosition++; // Clockwise
        } else {
            encoderPosition--; // Counterclockwise
        }
    }

    lastAState = currentAState; // Update last state

    // Void returns nothin 
}

/*
* Adjusts stepper motor location to correct an offset caused during movement
* @param offsetFromExpected is the amount of steps that the position is offset by
*/
void correctLocation(int offsetFromExpected){
    stepper.moveTo(offsetFromExpected); // Set target position
    while (stepper.distanceToGo() != 0) { // Move until the target position is reached and verified by encoder
        stepper.run(); // Run the stepper motor
    }

    // Void returns nothing
}

/*
* This function verifies that the accuracy is within the submilimeter tolerence and if its not it adjusts the offsetFromExpected value
@ param distance: is the distance in mm
@ param pulses: is the amount of pulses that have been sent to the stepper motor
*/
void verifiedAccuracy(int distance, int pulses){
  double TOLERANCE = 0.1; // in mm

  if (fabs(encoderPosition * RC - distance) > TOLERANCE){
    offsetFromExpected = pulses*CN - encoderPosition;
  }

  // Void Returns nothing
}

/*
* This function moves the rail by the specified distance in mm
@param distance: Is the distance that it will move in mm
*/
bool move_rail_x(int distance) {
    int pulses = (distance / (2 * PI * 28)) * 3200; // Calculate pulses for the given distance // 0.1466 mm per pulse to be exact
    stepper.moveTo(pulses); // Set target position
    while (stepper.distanceToGo() != 0) { // Move until the target position is reached and verified by encoder
        stepper.run(); // Run the stepper motor
        return true; // To verify the moving is complete
    }

    /*
    verifiedAccuracy(distance, pulses);

    if (offsetFromExpected != 0){
      correctLocation(offsetFromExpected);
      offsetFromExpected = 0;
    }
    */

    // Void returns nothing
}

/*
* Initialize required pins, interrupts, and serial communication between the PC and microcontroller
*/
void setup() {
    Serial.begin(115200);

    /*
    * End stop sensor pins
    */
    pinMode(EndStop0, INPUT);
    pinMode(EndStop1, INPUT);


    /*
    * DM542 Driver pins
    */
    pinMode(enablePin, OUTPUT); // Set the enable pin as an output
    digitalWrite(enablePin, LOW); // Enable the driver
    
    // Set encoder pins as inputs with pull-ups
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);
    
    // Attach interrupts for encoder channels
    attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);

    // Set the maximum speed and acceleration
    stepper.setMaxSpeed(2000); // 2000mm/s
    stepper.setAcceleration(1000); // 400mm/s^2

    // Void returns nothing
}

/*
* This is the first unit test which will test the movement of the X-axis on the gantry system
*/
bool MovementUnitTest(float distance){
    if(CalibrateSystem()){
    move_rail_x(distance);
    Serial.print("Encoder Position: ");
    Serial.print(encoderPosition*RC);
    Serial.println(" mm");
    Serial.println("");
    Serial.print("Intended Position: ");
    Serial.print(distance);
    Serial.println(" mm");
    if((round(encoderPosition*RC* 100.0) / 100.0) == distance)
      Serial.println("Unit test 1 passed")
    }
    else{
      Serial.println("Unit test 1 failed")
    }
}

/*
* The function runs the profilometer forward and then sends it back to verify that the profilometer is fully functioning and calibrated
*/
bool CalibrateSystem(){
  int InitialEndStopState = digitalRead(EndStop0);
  int RailDistance = 2500; // length of the fully gantry stroke in mm
  bool wait = true;
  if (InitialEndStopState == HIGH){
    while(wait){
      wait = !(move_rail_x(RailDistance));
    }
    int LastEndStopState = digitalRead(EndStop1);
    if(LastEndStopState == HIGH){
      move_rail_x(-1*RailDistance);
      return true; // Return true to indicate that the system is functioning
    }
    else{
      Serial.println("Positioning verification has failed!!!. Please verify that there is nothing blocking the gantry and that the mechanical system is functioning");
      return false;
    }
  }
  else {
    Serial.println("Please Move the block to the start position!!!"); // FIXME with an automated solution
    return false;
  }
}

void loop() {
  MovementUnitTest(500.00)
}