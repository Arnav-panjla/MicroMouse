#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include "Adafruit_VL53L0X.h"


//LIDARS

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32

// set the pins to shutdown
// #define SHT_LOX1 7
#define SHT_LOX2 3
#define SHT_LOX3 4

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

volatile float fr_LIDARval = 0;
volatile float ri_LIDARval = 0;
volatile float le_LIDARval = 0;



//MPU and ENCODERS

Adafruit_MPU6050 mpu;
int EN1 = 0; // PWM control for motor M1
int PH1 = 1; // Direction control for motor M1
int EN2 = 2; // PWM control for motor M2
int PH2 = 10; // Direction control for motor M2

int encoder1Pin1 = 20; //Encoder Output 'A' must connected with intreput pin of arduino.
int encoder1Pin2 = 21; //Encoder Otput 'B' must connected with intreput pin of arduino.
int encoder2Pin1 = 7; //Encoder Output 'A' must connected with intreput pin of arduino.
int encoder2Pin2 = 6; //Encoder Otput 'B' must connected with intreput pin of arduino.

volatile int lastEncoded1 = 0; // Here updated value of encoder store.
volatile int lastEncoded2 = 0; // Here updated value of encoder store.
volatile long encoder1Value = 0; // Raw encoder value
volatile long encoder2Value = 0; // Raw encoder value
#define CM_TO_STEPS 75
#define GYRO_MUL 59

static float rotZ = 0;
static unsigned long lastTime = 0;
static unsigned long currentTime = 0;



void setup() {
  Serial.begin(115200);
  mpu.begin();
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  pinMode(EN1, OUTPUT);
  pinMode(PH1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(PH2, OUTPUT);

  pinMode(encoder1Pin1, INPUT_PULLUP);
  pinMode(encoder1Pin2, INPUT_PULLUP);
  pinMode(encoder2Pin1, INPUT_PULLUP);
  pinMode(encoder2Pin2, INPUT_PULLUP);

  digitalWrite(encoder1Pin1, HIGH); //turn pullup resistor on
  digitalWrite(encoder1Pin2, HIGH); //turn pullup resistor on
  digitalWrite(encoder2Pin1, HIGH); //turn pullup resistor on
  digitalWrite(encoder2Pin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen

  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(digitalPinToInterrupt(encoder1Pin1), updateEncoder1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(encoder1Pin2), updateEncoder1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(encoder2Pin1), updateEncoder2, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(encoder2Pin2), updateEncoder2, CHANGE); 

  // pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);

  Serial.println(F("Shutdown pins inited..."));

  // digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);


  Serial.println(F("Both in reset mode...(pins are low)"));
  
  
  Serial.println(F("Starting..."));
  setID();
}

// void loop() {
//   M1_Forward(200); // Motor M1 moves forward with adjustable PWM
//   M2_Forward(200); // Motor M2 moves forward with adjustable PWM
//   delay(5000);
//   M1_Backward(200); // Motor M1 moves backward with adjustable PWM
//   M2_Backward(200); // Motor M2 moves backward with adjustable PWM
//   delay(5000);
// }

void loop() {
  // M1_Forward(200);
  // M2_Forward(200);
  // for (int i = 0; i <= 100; i++){
  //   Serial.print("Forward  ");
  //   Serial.println(encoderValue);
  // }
  // delay(1000);

  // M1_Backward(0);
  // M2_Backward(0);
  // for (int i = 0; i <= 100; i++){
  //   Serial.print("Reverse  ");
  //   Serial.println(encoderValue);
  // }
  // delay(1000);

  // moveForward(30*CM_TO_STEPS, 100);
  // delay(5000);
  // turnRight(90, 150);
  // delay(5000);
  // turnLeft(90, 250);
  // delay(2000);
  // moveForward(16*CM_TO_STEPS, 100);
  // delay(2000);
  // moveForward(30*CM_TO_STEPS, 150);
  // delay(1000);
  turnRight(180, 150);
  delay(500);
} 

void M1_Forward(int Speed1) // Forward fast decay mode for M1 motor, larger Speed1 value results in faster motor rotation
{
  analogWrite(EN1, Speed1);
  digitalWrite(PH1, HIGH);
}
void M1_Backward(int Speed1) // Forward fast decay mode for M1 motor, larger Speed1 value results in faster motor rotation
{
  analogWrite(EN1, Speed1);
  digitalWrite(PH1, LOW);
}
void M2_Forward(int Speed1) // Forward fast decay mode for M1 motor, larger Speed1 value results in faster motor rotation
{
  analogWrite(EN2, Speed1);
  digitalWrite(PH2, LOW);
}
void M2_Backward(int Speed1) // Forward fast decay mode for M1 motor, larger Speed1 value results in faster motor rotation
{
  analogWrite(EN2, Speed1);
  digitalWrite(PH2, HIGH);
}

void moveForward(int steps, int speed)
{
  move(encoder1Value+steps, encoder2Value+steps, speed);
  // M1_Forward(speed);
  // M2_Forward(speed);

  // encoder1Value = 0;
  // encoder2Value = 0;
  // while(encoder1Value>-steps)
  // {
  //   Serial.println(encoder1Value);
  //   Serial.println(encoder2Value);
  //   delay(10);
  // }
  // M1_Forward(0);
  // M2_Forward(0);
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

void moveBackward(int steps, int speed)
{
  moveForward(-steps, speed);
  // int speed1 = speed;
  // int speed2 = speed;
  // encoder1Value = 0;
  // encoder2Value = 0;
  // while(encoder1Value<steps)
  // {
  //   M1_Backward(speed1);
  //   M2_Backward(speed2);
  //   delay(10);
  // }

  // M1_Forward(0);
  // M2_Forward(0);
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
    

    delay(1);
  }
  M1_Forward(0);
  M2_Forward(0);
}

void turnRight(float degrees, float speed){
  float target_rot = rotZ - degrees;
  turn(target_rot, speed);
  // M1_Forward(speed);
  // M2_Backward(speed);
  // Serial.println("Turning right");
  // while(target_rot < rotZ)
  // {
  //   updateRotation();
  //   delay(10);
  // }

  // M1_Forward(0);
  // M2_Forward(0);
}

void turnLeft(float degrees, int speed){
  float target_rot = rotZ + degrees;
  turn(target_rot, speed);
  // M2_Forward(speed);
  // M1_Backward(speed);

  // while(target_rot > rotZ)
  // {
  //   updateRotation();
  //   delay(10);
  // }

  // M1_Forward(0);
  // M2_Forward(0);
}

void setID() {
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
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!

  if(measure1.RangeStatus != 4) {     // if not out of range
    ri_LIDARval = abs(measure1.RangeMilliMeter-40);
  }

  if(measure2.RangeStatus != 4) {
    le_LIDARval = abs(measure2.RangeMilliMeter-;
  }

  if(measure3.RangeStatus != 4) {
    fr_LIDARval = measure3.RangeMilliMeter;
  }
}

void updateRotation(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  currentTime = millis();
  float deltaTime = (currentTime - lastTime) / 1000.0; // Convert to seconds
  float gyro_z = 0;
  for(int i=0; i<2000; i++)
  {
    gyro_z += g.gyro.z;
  }
  gyro_z /= 2000;
  lastTime = currentTime;
  rotZ += gyro_z*deltaTime*GYRO_MUL;
}

void updateEncoder1(){
  int MSB = digitalRead(encoder1Pin1); //MSB = most significant bit
  int LSB = digitalRead(encoder1Pin2); //LSB = least significant bit
  
  int encoded1 = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded1 << 2) | encoded1; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoder1Value --;

  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoder1Value ++;

  lastEncoded1 = encoded1; //store this value for next time
}

void updateEncoder2(){
  int MSB2 = digitalRead(encoder2Pin1); //MSB = most significant bit
  int LSB2 = digitalRead(encoder2Pin2); //LSB = least significant bit

  int encoded2 = (MSB2 << 1) |LSB2; //converting the 2 pin value to single number
  int sum2  = (lastEncoded2 << 2) | encoded2; //adding it to the previous encoded value

  if(sum2 == 0b1101 || sum2 == 0b0100 || sum2 == 0b0010 || sum2 == 0b1011) encoder2Value --;

  if(sum2 == 0b1110 || sum2 == 0b0111 || sum2 == 0b0001 || sum2 == 0b1000) encoder2Value ++;
  
  lastEncoded2 = encoded2; //store this value for next time
}