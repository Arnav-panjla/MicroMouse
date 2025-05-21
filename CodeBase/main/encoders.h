#ifndef ENCODERS_H
#define ENCODERS_H

void initEncoders();
void updateEncoder1();
void updateEncoder2();

extern volatile long encoder1Value;
extern volatile long encoder2Value;

#endif
