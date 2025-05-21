#ifndef MOTION_H
#define MOTION_H

void initMotors();
void M1_Forward(int Speed1);
void M1_Backward(int Speed1);
void M2_Forward(int Speed1);
void M2_Backward(int Speed1);
void moveForward(int steps, int speed);
void moveBackward(int steps, int speed);
void move(int encoder1Target, int encoder2Target, float speed);
void turn(float target_rot, float speed);
void turnRight(float degrees, float speed);
void turnLeft(float degrees, int speed);

#endif
