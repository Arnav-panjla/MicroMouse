#include "encoders.h"
#include <Arduino.h>

int encoder1Pin1 = 20, encoder1Pin2 = 21;
int encoder2Pin1 = 7, encoder2Pin2 = 6;

volatile int lastEncoded1 = 0;
volatile int lastEncoded2 = 0;
volatile long encoder1Value = 0;
volatile long encoder2Value = 0;

void initEncoders() {
  pinMode(encoder1Pin1, INPUT_PULLUP);
  pinMode(encoder1Pin2, INPUT_PULLUP);
  pinMode(encoder2Pin1, INPUT_PULLUP);
  pinMode(encoder2Pin2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoder1Pin1), updateEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder1Pin2), updateEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder2Pin1), updateEncoder2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder2Pin2), updateEncoder2, CHANGE);
}

void updateEncoder1() {
  int MSB = digitalRead(encoder1Pin1);
  int LSB = digitalRead(encoder1Pin2);
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded1 << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoder1Value--;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoder1Value++;

  lastEncoded1 = encoded;
}

void updateEncoder2() {
  int MSB = digitalRead(encoder2Pin1);
  int LSB = digitalRead(encoder2Pin2);
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded2 << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoder2Value--;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoder2Value++;

  lastEncoded2 = encoded;
}
