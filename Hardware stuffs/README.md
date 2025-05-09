# Micromouse Hardware Documentation

<div align="center">
  <img src="https://img.shields.io/badge/Status-In%20Development-yellow" alt="Status: In Development">
  <img src="https://img.shields.io/badge/Team-Robotics%20Club-blue" alt="Team: Robotics Club">
  <img src="https://img.shields.io/badge/Dimensions-60×100mm-green" alt="Dimensions: 60×100mm">
</div>

## 📁 Repository Organization

This section of the repository contains all hardware-related files and documentation for the Micromouse project.

## 🔧 Hardware Specifications

- **Dimensions**: 60×100mm (base model)
- **Drive System**: Differential drive with dual micro-geared motors
- **Sensors**:
  - IR LED sensor array (front and sides)
  - IMU for orientation tracking
- **Power**: 3.7V LiPo battery
- **Control**: Arduino Nano (base model) / STM32 (advanced model)

### Adding New CAD Files

When adding new design files, please follow these guidelines:

1. Create a new subdirectory if your design represents a major component
2. Use descriptive filenames with version numbers (e.g., `chassis_v2.ipt`)
3. Include a brief README in each directory describing the components
4. For 3D printable files, include recommended print settings

## 🔌 Electronics Design
TODO

### Base Configuration
- **Microcontroller**: Arduino Nano
- **Motor Driver**: L293D
- **Sensor Interface**: Direct GPIO connection

### Advanced Configuration
TODO

## 📋 Bill of Materials

[Link to detailed BOM spreadsheet]

---

<div align="center">
  <i>For software documentation, please see the <a href="../CodeBase/README.md">Software README</a></i>
</div>