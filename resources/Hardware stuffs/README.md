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
  - Hall effect encoders (custom-designed)
  - IMU for orientation tracking
- **Power**: 3.7V LiPo battery
- **Control**: Arduino Nano (base model) / STM32 (advanced model)
- **PCB**: Custom-designed for compact integration

## 🛠️ CAD File Usage Guide

### File Formats

- Main assembly files are in `.f3d` format (Fusion 360)
- Export files available in `.step` and `.stl` formats
- PCB designs in `.brd` and `.sch` formats (Eagle)

### Adding New CAD Files

When adding new design files, please follow these guidelines:

1. Create a new subdirectory if your design represents a major component
2. Use descriptive filenames with version numbers (e.g., `chassis_v2.f3d`)
3. Include a brief README in each directory describing the components
4. For 3D printable files, include recommended print settings

## 🔌 Electronics Design

### Base Configuration

- **Microcontroller**: Arduino Nano
- **Motor Driver**: L293D
- **Sensor Interface**: Direct GPIO connection
- **Communication**: Serial for debugging

### Advanced Configuration

- **Microcontroller**: STM32F4
- **Motor Driver**: DRV8833 dual H-bridge
- **Sensor Processing**: Dedicated signal conditioning
- **Communication**: USB and Bluetooth modules

## 📋 Bill of Materials

[Link to detailed BOM spreadsheet]

## 📐 Assembly Instructions

1. Print all chassis components using recommended settings
2. Assemble the base chassis following the guide in `/assembly_guides`
3. Mount motors and attach wheels
4. Install sensor array according to the alignment guide
5. Mount control PCB and connect all components
6. Install battery and secure with mounting bracket

---

<div align="center">
  <i>For software documentation, please see the <a href="SOFTWARE_README.md">Software README</a></i>
</div>