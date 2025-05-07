#include "algo.h"

void setup() {
    Serial.begin(9600);
    initializeBot();
}

void loop() {
    // Simulate wall detection
    int frontWall = random(0, 2);  // 0 or 1 randomly
    simpleNavigate(frontWall);

    delay(500);  // Delay between decisions
}
