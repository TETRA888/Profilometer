// main.ino
#include "GantryControl.h"
#include "LiDARSystem.h"

void setup() {
    Serial.begin(115200);
    setupGantry(); // Code for gantry setup
    setupLidar();  // Code for LiDAR setup
}

void loop() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        
        // Check for the "START" command from the Python script
        if (command == "START") {
            collectDataPoints(0, 250, 0.1); // Start collecting data move 2.5cm at 0.1 increment steps, so thats like 25 data points
            sendDataToRaspberryPi();
        }
    }
}

void collectDataPoints(float startX, float endX, float stepSize) {
    for (float x = startX; x <= endX; x += stepSize) {
        move_rail_x(x);
        delay(1); // Stabilize the gantry
        readLidar();

        // Send data in the structured format
        Serial.print("DATA:");
        Serial.print(x);        // X value
        Serial.print(",");
        Serial.print(0);        // Y value (always 0)
        Serial.print(",");
        Serial.print(distanceCM); // Z value from LiDAR
        Serial.println();
    }
}

void sendDataToRaspberryPi() {
    Serial.println("Data collection complete!");
}

