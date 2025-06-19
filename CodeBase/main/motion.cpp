#include "motion.h"
#include <Arduino.h>
#include "encoders.h"
#include "sensors.h"

int EN1 = 0, PH1 = 1, EN2 = 2, PH2 = 10;

void initMotors() {
  pinMode(EN1, OUTPUT);
  pinMode(PH1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(PH2, OUTPUT);
}

void M1_Forward(int Speed1) {
  analogWrite(EN1, Speed1);
  digitalWrite(PH1, HIGH);
}
void M1_Backward(int Speed1) {
  analogWrite(EN1, Speed1);
  digitalWrite(PH1, LOW);
}
void M2_Forward(int Speed1) {
  analogWrite(EN2, Speed1);
  digitalWrite(PH2, LOW);
}
void M2_Backward(int Speed1) {
  analogWrite(EN2, Speed1);
  digitalWrite(PH2, HIGH);
}

void turn(float target_rot, float speed){
  float diff = abs(target_rot-rotZ)/(GYRO_MUL);
  while(1)
  {
    diff = abs(target_rot-rotZ)/(GYRO_MUL);
    if(diff>1) diff=1;
    Serial.println(diff);
    float x = 1-(1-diff)*(1-diff);
    updateRotation();
    if(diff<0.02)
    {
      M1_Forward(0);
      M2_Forward(0);
      for(int i=0; i<20; i++)
      {
        delay(1);
        updateRotation();
        diff = abs(target_rot-rotZ)/(GYRO_MUL);
      }
      if(diff<0.02) break;
    }
    else if(target_rot < rotZ)
    {
      M1_Forward(x*speed);
      M2_Backward(x*speed);
    }
    else if(target_rot > rotZ)
    {
      M1_Backward(x*speed);
      M2_Forward(x*speed);
    }
  }
  M1_Forward(0);
  M2_Forward(0);
}

void turnRight(float degrees, float speed){
  float target_rot = rotZ - degrees;
  turn(target_rot, speed);
}

void turnLeft(float degrees, int speed){
  float target_rot = rotZ + degrees;
  turn(target_rot, speed);
}

void move(int encoder1Target, int encoder2Target, float speed)
{
  float diff1 = 100;
  float diff2 = 100;
  while(diff1*speed>5 || diff2*speed>5)
  {
    diff1 = abs(encoder1Target-encoder1Value)/(3*speed);
    diff2 = abs(encoder2Target-encoder2Value)/(3*speed);
    Serial.println(diff1);
    Serial.println(diff2);
    if(diff1>1) diff1=1;
    if(diff2>1) diff2=1;
    
    float x1 = 1-(1-diff1)*(1-diff1);
    float x2 = 1-(1-diff2)*(1-diff2);
    if(diff2*3*speed<5)
      M2_Forward(0);
    else if(encoder2Target>encoder2Value)
      M2_Forward(x2*speed);
    else if(encoder2Target<encoder2Value)
      M2_Backward(x2*speed);
    
    if(diff1*3*speed<5)
      M1_Forward(0);
    else if(encoder1Target>encoder1Value)
      M1_Forward(x1*speed);
    else if(encoder1Target<encoder1Value)
      M1_Backward(x1*speed);
  }
}

void moveForward(int steps, int speed)
{
  move(encoder1Value+steps, encoder2Value+steps, speed);
}

void moveBackward(int steps, int speed)
{
  moveForward(-steps, speed);
}