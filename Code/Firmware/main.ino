// main.ino
#include "GantryControl.h"

void setup() {
    setupGantry();
}

void loop() {
    MovementUnitTest(500.00);
}
