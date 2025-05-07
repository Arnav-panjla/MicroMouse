#include "algo.h"

void setup() {
    Serial.begin(9600);
    initializeBot();
}

void loop() {
    int frontWall = random(0, 2);  // Replace with sensor read
    simpleNavigate(frontWall);
    delay(500);
}
