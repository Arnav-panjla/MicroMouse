#include "motion.h"
#include "encoders.h"
#include "sensors.h"
#include "algorithm.h"

void setup() {
  Serial.begin(115200);
  initEncoders();
  initMotors();
  initMPU();
  initLIDARS();
  setLIDARAddresses();
}

void loop() {
//   turnRight(180, 150);
  delay(500);

  // Place algorithm call here in future
  // solveMaze();
}
