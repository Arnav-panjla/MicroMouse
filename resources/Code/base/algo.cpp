#include "algo.h"

// Define global state
Position currentPos = {0, 0, NORTH};

void initializeBot() {
    Serial.println("Bot initialized.");
}

void simpleNavigate(int frontWall) {
    if (frontWall) {
        Serial.println("Wall ahead! Turning right.");
        turnRight();
    } else {
        moveForward();
    }
}

void moveForward() {
    Serial.println("Moving forward.");
    switch (currentPos.dir) {
        case NORTH: currentPos.y++; break;
        case EAST:  currentPos.x++; break;
        case SOUTH: currentPos.y--; break;
        case WEST:  currentPos.x--; break;
    }

    Serial.print("Now at: (");
    Serial.print(currentPos.x);
    Serial.print(", ");
    Serial.print(currentPos.y);
    Serial.println(")");
}

void turnRight() {
    currentPos.dir = (Direction)((currentPos.dir + 1) % 4);

    Serial.print("Turned right. Now facing ");
    switch (currentPos.dir) {
        case NORTH: Serial.println("NORTH"); break;
        case EAST:  Serial.println("EAST"); break;
        case SOUTH: Serial.println("SOUTH"); break;
        case WEST:  Serial.println("WEST"); break;
    }
}
