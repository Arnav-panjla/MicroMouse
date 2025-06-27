#ifndef SENSORS_H
#define SENSORS_H

#define GYRO_MUL 65.5
void initMPU();
void initLIDARS();
void setLIDARAddresses();
void read_sensors();
void updateRotation();

// LIDAR readings
extern volatile float fr_LIDARval;
extern volatile float ri_LIDARval;
extern volatile float le_LIDARval;
extern volatile float rotZ;

#endif
