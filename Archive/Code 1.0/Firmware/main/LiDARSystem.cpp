#include "LiDARSystem.h"
#include <Arduino.h>
const int triggerPin = 51;     // Trigger pin on Arduino, you connect the monitor pin to the trigger pin via a 1k resistor
const int monitorPin = 53;      // Mode control pin connected to yellow wire

unsigned long pulseDuration;
float distanceCM;

void setupLidar() {
  pinMode(triggerPin, OUTPUT);  // Set trigger pin as output
  pinMode(monitorPin, INPUT);   // Set monitor pin as input

  delay(1000);                  // Wait for the sensor to stabilize
}

void readLidar() {
  // Send a trigger pulse to start a new measurement
  digitalWrite(triggerPin, HIGH);
  delay(10);                    // 10 ms trigger pulse duration
  digitalWrite(triggerPin, LOW);
  
  // Measure the PWM pulse duration from the mode control pin
  pulseDuration = pulseIn(monitorPin, HIGH, 100000);  // Timeout after 100 ms

  // Convert pulse duration to distance in cm (10 µs per cm)
  if (pulseDuration > 0) {
    distanceCM = pulseDuration;  // Convert to mm

    // Debugging code for the LiDAR
    /*
    Serial.print("Distance: ");
    Serial.print(distanceCM);
    Serial.println(" mm");
    */
  } else {
    /*
    * More debugging code
    */
    Serial.println("No valid PWM signal detected. Check wiring and setup.");
  }
}