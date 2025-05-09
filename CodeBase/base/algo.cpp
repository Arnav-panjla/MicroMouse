#include <Arduino.h>
#include "algo.h"

// Define global state
Position currentPos = {0, 0, NORTH};

// Motor pin constants (match main.ino)
const int DIR_LEFT  = 2;
const int DIR_RIGHT = 3;
const int PWM_LEFT  = 5;
const int PWM_RIGHT = 6;
const int BASE_SPEED = 200;

void initializeBot() {
    Serial.println("Bot initialized.");

    // Motor pin setup
    pinMode(DIR_LEFT, OUTPUT);
    pinMode(DIR_RIGHT, OUTPUT);
    pinMode(PWM_LEFT, OUTPUT);
    pinMode(PWM_RIGHT, OUTPUT);
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
    Serial.println("Moving forward");

    digitalWrite(DIR_LEFT, HIGH);
    digitalWrite(DIR_RIGHT, HIGH);
    analogWrite(PWM_LEFT, BASE_SPEED);
    analogWrite(PWM_RIGHT, BASE_SPEED);

    delay(300); // move duration

    analogWrite(PWM_LEFT, 0);
    analogWrite(PWM_RIGHT, 0);

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
    Serial.println("Turning right");

    digitalWrite(DIR_LEFT, HIGH);
    digitalWrite(DIR_RIGHT, LOW);
    analogWrite(PWM_LEFT, BASE_SPEED);
    analogWrite(PWM_RIGHT, BASE_SPEED);

    delay(300); // turn duration

    analogWrite(PWM_LEFT, 0);
    analogWrite(PWM_RIGHT, 0);

    currentPos.dir = (Direction)((currentPos.dir + 1) % 4);

    Serial.print("Now facing ");
    switch (currentPos.dir) {
        case NORTH: Serial.println("NORTH"); break;
        case EAST:  Serial.println("EAST"); break;
        case SOUTH: Serial.println("SOUTH"); break;
        case WEST:  Serial.println("WEST"); break;
    }
}
