# Automatic Power Factor Correction (APFC) System

## Overview
This project implements an **Automatic Power Factor Correction (APFC)** system using an **Arduino Uno (ATmega328)** to improve the power factor in AC electrical systems with inductive loads such as submersible pumps and lighting loads. The system continuously monitors electrical parameters and automatically compensates for reactive power by switching capacitors as needed.

The objective of this project is to reduce energy losses, improve system efficiency, and minimize electricity costs, particularly for rural and small industrial applications.

---

## Features

✔ Real-time measurement of electrical parameters  
✔ Automatic capacitor switching through relays  
✔ Power factor improvement from **0.66 → 0.92**  
✔ Live monitoring using a **16×4 LCD display**  
✔ Low-cost and scalable implementation  
✔ Automatic response to changing load conditions  

---

## Hardware Components

- Arduino Uno (ATmega328)
- PZEM-004T Power Measurement Module
- Relay Module
- Capacitors for reactive power compensation
- 16×4 LCD Display
- Submersible Pump / Bulb (Load)
- AC Power Supply

---

## Working Principle

Inductive loads consume reactive power, causing the current waveform to lag behind the voltage waveform. This lagging current reduces the power factor and increases energy losses.

The **PZEM-004T** continuously measures parameters such as:

- Voltage
- Current
- Power
- Power Factor

The measured data is transmitted to the Arduino controller. When the power factor falls below a predefined threshold, the Arduino activates relay modules to connect suitable capacitors in parallel with the load.

These capacitors provide leading reactive power that compensates for the lagging reactive power of the inductive load, reducing the phase difference between current and voltage and improving the overall power factor.

The system displays all measured values and system status in real time on the LCD display.

---

## Results

| Parameter | Value |
|------------|--------|
| Initial Power Factor | 0.66 |
| Corrected Power Factor | 0.92 |
| Improvement | ~39% |

---

## Applications

- Rural electrical systems
- Agricultural water pumping systems
- Small industrial setups
- Energy efficiency projects
- Power quality improvement systems

---

## Future Improvements

- IoT-based remote monitoring
- Mobile application integration
- Automatic adaptive capacitor selection
- Data logging and analytics

---

## Project Goal

To provide an affordable and efficient solution for improving power quality and reducing energy losses in electrical systems.
