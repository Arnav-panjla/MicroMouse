#ifndef SENSORS_H
#define SENSORS_H

void initMPU();
void initLIDARS();
void setLIDARAddresses();
void read_sensors();
void updateRotation();

// LIDAR readings
extern volatile float fr_LIDARval;
extern volatile float ri_LIDARval;
extern volatile float le_LIDARval;

#endif
