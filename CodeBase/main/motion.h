#ifndef MOTION_H
#define MOTION_H

#include "algorithm.h"

#define CM_TO_STEPS 75
void initMotors();
void M1_Forward(int Speed1);
void M1_Backward(int Speed1);
void M2_Forward(int Speed1);
void M2_Backward(int Speed1);
void move(int encoder1Target, int encoder2Target, float speed);
void turn(float target_rot, float speed);

void moveForward(int steps, int speed);
void moveBackward(int steps, int speed);
void turnRight(float degrees, float speed);
void turnLeft(float degrees, int speed);

void followPath(dir* path, int pathLength);

#endif
