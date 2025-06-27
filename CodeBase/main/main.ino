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
  read_sensors();
  dir path[8] = {dir::NORTH, dir::EAST, dir::NORTH, dir::EAST, dir::SOUTH, dir::SOUTH, dir::WEST, dir::WEST};
  followPath(path, 8);
  delay(500);
}
