#include "sensors.h"
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_VL53L0X.h"

#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32

#define SHT_LOX2 3
#define SHT_LOX3 4

Adafruit_MPU6050 mpu;
float mpu_diff = 0;

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure1, measure2, measure3;

volatile float fr_LIDARval = 0;
volatile float ri_LIDARval = 0;
volatile float le_LIDARval = 0;

volatile float rotZ = 0;
unsigned long lastTime = 0, currentTime = 0;

void initMPU() {
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  sensors_event_t a, g, temp;

  float x = 0;
  for (int i=0; i<100; i++) {
    mpu.getEvent(&a, &g, &temp);
    x+=g.gyro.z;
  }
  mpu_diff = x/100;
}

void initLIDARS() {
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
}

void setLIDARAddresses() {
  // all reset
  // digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  delay(10);
  // all unreset
  // digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  // digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, LOW);
  delay(10);

  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  //initing LOX2
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }
}

void read_sensors() {
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  lox3.rangingTest(&measure3, false);

  if (measure1.RangeStatus != 4) ri_LIDARval = abs(measure1.RangeMilliMeter - 50);
  if (measure2.RangeStatus != 4) le_LIDARval = abs(measure2.RangeMilliMeter - 30);
  if (measure3.RangeStatus != 4) fr_LIDARval = abs(measure3.RangeMilliMeter - 30);
}

void updateRotation() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0;
  if (deltaTime > 0.1) {deltaTime = 0;}
  float gyro_z = g.gyro.z - mpu_diff;
  lastTime = currentTime;

  rotZ += gyro_z * deltaTime * GYRO_MUL;
}
