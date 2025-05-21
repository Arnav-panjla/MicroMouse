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

