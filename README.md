# 🩸 Non-Invasive Continuous Glucose Monitor Prototype

<div align="center">

*An affordable and accessible optical-based continuous glucose monitoring solution using Arduino for non-invasive blood glucose measurement.*

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat&logo=Arduino&logoColor=white)](https://www.arduino.cc/)
[![Status: Prototype](https://img.shields.io/badge/Status-Prototype-orange)](https://github.com/username/Non-Invasive-CGM-Prototype)

</div>

## 📋 Table of Contents

- [🌟 Overview](#-overview)
- [✨ Features](#-features)
- [🔬 Scientific Principles](#-scientific-principles)
- [🛠️ Components Required](#-components-required)
- [⚙️ How It Works](#️-how-it-works)
- [📊 Calibration Process](#-calibration-process)
- [🚀 Future Improvements](#-future-improvements)
- [📝 Usage](#-usage)

## 🌟 Overview

This project presents an Arduino-based non-invasive continuous glucose monitor (CGM) prototype designed for measuring blood glucose levels without needles or invasive procedures. It utilizes near-infrared (NIR) spectroscopy combined with temperature correction to provide reasonably accurate glucose estimations. The system aims to provide an affordable and accessible alternative to traditional invasive glucose monitoring methods.

## ✨ Features

- **Non-Invasive Measurement**: Uses optical sensing rather than needles or blood samples
- **Real-time Monitoring**: Continuous measurement of glucose levels
- **Temperature Compensation**: Accounts for variations in skin temperature to improve accuracy
- **Calibration System**: Allows for personalized calibration to improve measurement accuracy
- **Rolling Average Filtering**: Reduces noise and stabilizes readings
- **Compact Design**: Built with readily available, low-cost components
- **Serial Output**: Provides detailed output for monitoring and data logging
- **Range Constraining**: Ensures readings fall within physiologically relevant values

## 🔬 Scientific Principles

The prototype works on the principle of Near-Infrared (NIR) Spectroscopy:

1. **Optical Absorption**: Different glucose concentrations in blood absorb NIR light differently
2. **Beer-Lambert Law**: The amount of light absorbed is proportional to the concentration of glucose
3. **Temperature Compensation**: Skin temperature affects measurements and is compensated for using a temperature coefficient
4. **Linear Interpolation**: Translates optical readings to glucose concentration using calibration points

## 🛠️ Components Required

- Arduino board (UNO or similar)
- IR LED (940nm wavelength)
- Photodiode or phototransistor
- DS18B20 temperature sensor (waterproof version)
- 4.7kΩ resistor (for temperature sensor)
- Appropriate resistors for LED circuit
- Breadboard and jumper wires
- 3D printed or custom housing for sensor placement

## ⚙️ How It Works

1. **Optical Measurement**: The IR LED emits light that passes through tissue, and the photodiode measures the amount of light absorbed/reflected
2. **Temperature Monitoring**: The DS18B20 sensor measures skin temperature at the measurement site
3. **Signal Processing**:
   - Multiple readings are taken and averaged to reduce noise
   - Temperature compensation is applied to account for variations in skin temperature
4. **Glucose Calculation**: 
   - Linear interpolation between calibration points converts optical readings to glucose values
   - Range constraints ensure physiologically relevant outputs

## 📊 Calibration Process

The device requires calibration with reference glucose values:

1. Collect optical readings at different known glucose levels (preferably using a traditional glucometer)
2. Define the relationship between optical readings and glucose values
3. Set the coefficients in the code (`optical_low_calibrated`, `optical_high_calibrated`, etc.)
4. Adjust temperature coefficient (`temp_coeff_mgdl_per_C`) based on observed temperature dependencies

## 🚀 Future Improvements

- Implement machine learning algorithms for better calibration and accuracy
- Add wireless connectivity (Bluetooth/WiFi) for data transmission to smartphone apps
- Improve form factor and ergonomics for better user experience
- Incorporate multiple wavelength measurements for improved specificity
- Develop companion app for data logging and trend analysis
- Add alerting mechanisms for hypo/hyperglycemic conditions

## 📝 Usage

1. **Setup**:
   - Connect the components according to the circuit diagram
   - Upload the provided Arduino code
   - Ensure the sensor is positioned correctly on the measurement site

2. **Calibration**:
   - Take multiple readings with a reference glucose meter
   - Adjust the calibration constants in the code
   - Re-upload the code with your personal calibration values

3. **Monitoring**:
   - The device will output readings to the Serial Monitor
   - Format: `Avg Optical: [value], Raw Optical: [value], Temperature: [value] C, Est. Glucose: [value] mg/dL`
   - Monitor trends rather than absolute values for best results

## 👥 Team Members

**Team 17 | SBME 2026**

*Developed as part of the Medical Equipment Design Course*

- Mostafa Mousa
- Amaar Yasser
- Ahmed Adeil
- Zeyad Wael
- Hussein Mohamed

---

**Disclaimer**: This device is a prototype for educational and research purposes only. It should not be used for medical diagnosis or treatment decisions. Always consult healthcare professionals for managing diabetes or other glucose-related conditions.
