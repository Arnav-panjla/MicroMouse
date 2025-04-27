# Micromouse - Robotics Summer Project 2025-26

<div align="center">
  <img src="https://img.shields.io/badge/Status-In%20Development-yellow" alt="Status: In Development">
  <img src="https://img.shields.io/badge/Team-Robotics%20Club-blue" alt="Team: Robotics Club">
  <img src="https://img.shields.io/badge/Platform-STM32/Arduino-orange" alt="Platform: STM32/Arduino">
</div>

## 🤖 Project Overview

This repository houses the codebase for the **Micromouse Summer Project 2025-26**. It serves as a comprehensive collection of resources including code, CAD models, calculations, and component datasheets. Our aim is to create a well-documented reference that will enable future teams to build upon our work.

### 🎯 Design Goals

- ✅ Compact design (within 100×100mm)
- ✅ Efficient corner turning capability
- ✅ Fast maze-solving algorithm
- ✅ Differential drive with high-speed motors
- ✅ Custom-designed hall effect encoders
- ✅ Custom PCB implementation
- ✅ High-performance microcontroller

## 📋 Development Roadmap

### Base Model (60×100mm)
- Micro-geared motors with encoders
- IR LED sensor array
- L293D motor driver
- Arduino Nano microcontroller
- IMU for orientation tracking
- DFS algorithm implementation

### Advanced Features
- Size reduction (potentially with custom PCB)
- Optimized IR sensor placement ([diagonal LED configuration](https://www.youtube.com/watch?v=VAvPl1eCIEA))
- Enhanced motor driver
- STM32 microcontroller upgrade
- Algorithm simulation using MMS

## 🧠 Algorithm Development
Research focus on flood-fill algorithms and optimization techniques for maze navigation.

## ⏱️ Project Timeline

### Week 1: Introduction
- Review the competition rulebook
-  Study the [UCLA IEEE Micromouse playlist](https://youtube.com/playlist?list=PLAWsHzw_h0iiPIaGyXAr44G0XfHfyjOe7)
-  Brainstorm ideas and design concepts
-  Prepare Bill of Materials
-  Draft electronic system diagram

### Week 2: Hardware Assembly
-  Assemble mechanical components
-  Learn [MMS simulator](https://github.com/mackorone/mms) operation
-  Implement baseline navigation algorithm

### Week 3: Debugging
-  Hardware and software troubleshooting
-  Performance analysis and optimization

### Week 4: Algorithm Refinement
-  Improve navigation algorithms
-  Enhance hardware robustness
-  Plan optimizations based on [Veritasium analysis](https://www.youtube.com/watch?v=ZMQbHMgK2rw)
-  Research additional enhancement opportunities

### Weeks 5-7: Progressive Enhancements
- 🔄 Implement iterative improvements (tbd)

## 📚 Resources

### Tools and References (tbd)
- 🔵 [MMS Simulator](https://github.com/mackorone/mms)
- 🎥 [UCLA IEEE Micromouse Series](https://youtube.com/playlist?list=PLAWsHzw_h0iiPIaGyXAr44G0XfHfyjOe7)
- 🧮 [Veritasium Micromouse Analysis](https://www.youtube.com/watch?v=ZMQbHMgK2rw)

### Development Software
-  Fusion/Eagle (PCB design)
-  MATLAB (calculations if needed)
-  STM32 Cube IDE
-  Arduino IDE (prototype development)


## 🤝 Contributor Notes
- We follow the [standard Git workflow](https://www.geeksforgeeks.org/git-workflows-with-open-source-collaboration/) for collaboration
- Suggestions for improvement are welcome via Issues or Discussions

---

<div align="center">
  <i>Building the future of autonomous navigation, one maze at a time.</i>
</div>

