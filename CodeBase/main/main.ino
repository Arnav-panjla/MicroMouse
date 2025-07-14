#include "motion.h"
#include "encoders.h"
#include "sensors.h"
#include "algorithm.h"

void setup() {
  Serial.begin(115200);
  initEncoders();
  initMotors();
  initLIDARS();
  setLIDARAddresses();
  delay(10000);
  initMPU();
}

void loop() {
  read_sensors();
  uint8_t coord[2] = {0,0};
  uint8_t goal[2] = {2,5};
  float lidar_threshold = 80;
  dir cur_dir = dir::NORTH;
  Maze m = new_Maze();
  while (coord != goal) {
    read_sensors();
    if (fr_LIDARval < lidar_threshold) {
      addWall(m, coord[0], coord[1], cur_dir);
      Serial.println("Front Wall!!");
    }
    if (le_LIDARval < lidar_threshold) {
      Serial.println("Left Wall!!");
      if (cur_dir == dir::NORTH) {
        addWall(m, coord[0], coord[1], dir::WEST);
      } else if (cur_dir == dir::WEST) {
        addWall(m, coord[0], coord[1], dir::SOUTH);
      } else if (cur_dir == dir::SOUTH) {
        addWall(m, coord[0], coord[1], dir::EAST);
      } else if (cur_dir == dir::EAST) {
        addWall(m, coord[0], coord[1], dir::NORTH);
      } 
    }
    if (ri_LIDARval < lidar_threshold) {
      Serial.println("Right Wall!!");
      if (cur_dir == dir::NORTH) {
        addWall(m, coord[0], coord[1], dir::EAST);
      } else if (cur_dir == dir::EAST) {
        addWall(m, coord[0], coord[1], dir::SOUTH);
      } else if (cur_dir == dir::SOUTH) {
        addWall(m, coord[0], coord[1], dir::WEST);
      } else if (cur_dir == dir::WEST) {
        addWall(m, coord[0], coord[1], dir::NORTH);
      }
    }

    flood(m, goal);
    dir d = getDir(m, coord[0], coord[1]);
    if (d == dir::NORTH) {coord[0]+=1;}
    else if (d == dir::SOUTH) {coord[0]-=1;}
    else if (d == dir::WEST) {coord[1]-=1;}
    else if (d == dir::EAST) {coord[1]+=1;}


    if(d==cur_dir)
    {
      forward();
    }
    else if(d==dir::NORTH && cur_dir==dir::EAST)
    {
      left();
      forward();
    }
    else if(d==dir::NORTH && cur_dir==dir::WEST)
    {
      right();
      forward();
    }
    else if(d==dir::SOUTH && cur_dir==dir::EAST)
    {
      right();
      forward();
    }
    else if(d==dir::SOUTH && cur_dir==dir::WEST)
    {
      left();
      forward();
    }
    else if(d==dir::EAST && cur_dir==dir::NORTH)
    {
      right();
      forward();
    }
    else if(d==dir::EAST && cur_dir==dir::SOUTH)
    {
      left();
      forward();
    }
    else if(d==dir::WEST && cur_dir==dir::NORTH)
    {
      left();
      forward();
    }
    else if(d==dir::WEST && cur_dir==dir::SOUTH)
    {
      right();
      forward();
    }
    cur_dir = d;

    if(d==dir::NORTH) {Serial.println("NORTH");}
    else if (d==dir::EAST) {Serial.println("EAST");}
    else if (d==dir::SOUTH) {Serial.println("SOUTH");}
    else if (d==dir::WEST) {Serial.println("WEST");}
  }
  delay(500);
}
