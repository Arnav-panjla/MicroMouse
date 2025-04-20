# Micromouse - Robotics Summer project 2025-26
This repository is intended to manage the codebase for the **Micromouse summer project 2025-26** (part of robotics club). Ideally, it can be extended to include other related resources as well (CAD model, calculation(Matlab), Datasheet of the electronic components etc.) Over time, it will serve as both a proof of work and a **well-documented reference** to help others continue the project beyond its initial requirements.

Main goal, is to build a bot which has the following properties
- small size, within 90 x 90
- effecient corner turning
- fast algorithm
- differential drive with high speed motors
- implement a self designed encoder,(basically hall effect)
- custom pcb
- a fast microcontroller
  

## Adjenda
- Complete a base model (within 90x120)
  - microgeared motor, with encoders
  - ir leds
  - motor driver, L293D
  - micorcontroller (Arduino Nano)
  - IMU
  - implement DFS
- reduce size, if possible without custom PCB
- look for optimal placement of IR sensors [diagonal led](https://www.youtube.com/watch?v=VAvPl1eCIEA&list=PLAWsHzw_h0iiPIaGyXAr44G0XfHfyjOe7&index=7)
- use a better motor driver
- Replace arduino nano with stm32
- use mms for algorthm simulation

## algorithm
Need to do some research, 
for now see, floodfill

## resources
- simulator [mms](https://github.com/mackorone/mms)
- yt playlist on micormouse [UCLA IEEE](https://youtube.com/playlist?list=PLAWsHzw_h0iiPIaGyXAr44G0XfHfyjOe7&si=PbVkcmYhvSuIREAw)
- (Veritasium)[https://www.youtube.com/watch?v=ZMQbHMgK2rw]
- Some useful softwares
  - fusion(eagle)
  - Matlab(if needed)
  - Cube IDE
  - Arduino IDE, (only for base model)

## 🤝 Contributor Notes
- will be following standard git workflow [here](https://www.geeksforgeeks.org/git-workflows-with-open-source-collaboration/)
- Feel free to suggest improvements via Issues or Discussions
