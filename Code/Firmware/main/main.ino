// main.ino
#include "GantryControl.h"
#include "LiDARSystem.h"

void setup() {
    setupGantry(); // Code for gantry setup
    setupLidar(); // Code for LiDAR setup
    setupLighting(); // Code to setup light system
}

void loop() {
    MovementUnitTest(500.00); // Movement test to verify accurate gantry movement
    readLidar(); // Simple function to read active LiDAR values
}
