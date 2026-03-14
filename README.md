# Smart Traffic Monitoring & Violation Detection System

## Overview
The **Smart Traffic Monitoring & Violation Detection System** is an Arduino-based project designed to monitor vehicle movement at a traffic signal. The system detects **red light violations**, calculates **vehicle speed using IR sensors**, and warns drivers if they exceed the **speed limit during yellow signals**.

The system also includes **day/night detection using an LDR sensor**, an **LCD display for real-time information**, and an **IR remote control to manually change traffic lights**.

This project demonstrates how embedded systems can be used for **basic intelligent traffic management and safety monitoring**.

---

## Features
- Traffic light control (Red, Green, Yellow)
- Red light violation detection
- Vehicle speed measurement using IR sensors
- Overspeed warning during yellow signal
- Day/Night detection using LDR
- LCD display for real-time traffic status
- Buzzer alert for violations
- IR remote-based manual traffic light control
- Vehicle/object counting

---

## Hardware Components
- Arduino Uno / Arduino Nano
- 16x2 LCD Display with I2C module
- 2 IR Sensors (Vehicle detection)
- IR Remote Receiver Module
- Buzzer
- Red LED
- Green LED
- LDR (Light Dependent Resistor)
- Resistors
- Breadboard and jumper wires

---

## System Working

### 1. Traffic Signal Control
Traffic lights are controlled using an **IR remote**.

- Button 1 → Red Light
- Button 2 → Green Light
- Button 3 → Yellow Light

The system updates the LEDs and LCD display based on the selected traffic signal.

---

### 2. Red Light Violation Detection
If a vehicle passes either IR sensor while the signal is **RED**, the system detects it as a **traffic violation**.

The system then:
- Activates the **buzzer**
- Displays **TRAFFIC VIOLATION** on the LCD

---

### 3. Vehicle Speed Measurement
Two IR sensors are placed at a fixed distance.

When a vehicle passes:

1. IR1 detects the vehicle → timer starts
2. IR2 detects the vehicle → timer stops

Speed is calculated using:

```
Speed = Distance / Time
```

The result is converted to **km/h** and displayed on the LCD.

---

### 4. Overspeed Warning
During **Yellow Light**, vehicles must move slowly.

If the detected speed exceeds:

```
Speed Limit = 10 km/h
```

The system:

- Displays **SLOW DOWN**
- Shows **LIMIT 10 km/h**
- Activates buzzer warning

---

### 5. Day/Night Detection
An **LDR sensor** detects ambient light conditions.

If light intensity falls below a threshold:

- System switches to **Night Mode**
- LCD displays **NIGHT**

Otherwise it displays **DAY**.

---

## LCD Display Information

Normal Display:

```
RED DAY
SPD: 5.2 km/h
```

Overspeed Warning:

```
SLOW DOWN !
LIMIT 10km/h
```

Violation Screen:

```
TRAFFIC
VIOLATION !
```

---

## Pin Configuration

| Component | Arduino Pin |
|----------|-------------|
| IR Sensor 1 | D2 |
| IR Sensor 2 | D3 |
| Buzzer | D5 |
| IR Receiver | D6 |
| Red LED | D9 |
| Green LED | D10 |
| LDR Sensor | A0 |
| LCD (I2C) | SDA/SCL |

---

## Libraries Used

- `Wire.h`
- `LiquidCrystal_I2C.h`
- `IRremote.hpp`

Install libraries from the **Arduino Library Manager** before compiling.

---

## How to Run

1. Connect all hardware components according to the circuit.
2. Install required Arduino libraries.
3. Upload the Arduino code to the board.
4. Power the system.
5. Use the IR remote to change traffic light states.
6. Observe vehicle detection, speed measurement, and violation alerts on the LCD.

---

## Applications
- Smart traffic monitoring systems
- Traffic rule violation detection
- Speed monitoring systems
- Smart city infrastructure
- Embedded systems learning project

---

## Future Improvements
- Automatic traffic signal timing
- Camera-based license plate detection
- Cloud-based violation logging
- IoT dashboard for traffic monitoring
- Machine learning for traffic flow prediction

---

## Author
**D. Srinivas Rao**

Electronics Engineering Student  
Arduino Embedded Systems Project
