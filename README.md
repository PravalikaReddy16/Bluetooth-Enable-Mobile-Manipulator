# 🤖 Mobile Manipulator Robot (Arduino Bluetooth Control)

This project details the construction and deployment of a mobile manipulator robot. The system features a 4-wheel drive mobile platform controlled by an **Arduino Uno** and a 4-DOF robotic arm controlled by an **Arduino Nano**. The entire system is operated wirelessly via Bluetooth using a smartphone app.

## 📋 Hardware Requirements

### Electronics
* **Master Controller:** Arduino Uno R3
* **Slave Controller:** Arduino Nano
* **Communication:** HC-05 or HC-06 Bluetooth Module
* **Motor Driver:** L298N H-Bridge Driver
* **Actuators:**
    * 4x DC Gear Motors (for wheels)
    * 3x MG996R High Torque Servos (Base, Shoulder, Elbow)
    * 1x SG90 Micro Servo (Gripper)
* **Power:**
    * 12V Li-Po Battery (3S) or Li-Ion Pack
    * LM2596 Buck Converter (Step-down module 12V to 5V/3A)

### Mechanical
* 4-Wheel Robot Chassis Kit
* 3D Printed Robotic Arm Parts (Base, Links, Claw)
* Jumper Wires & Breadboard

## 🔌 Wiring Guide

### 1. Power Distribution (CRITICAL)
Do not power servos directly from the Arduino 5V pin.
* **Battery (12V):** Connects to L298N 12V input and LM2596 Input.
* **LM2596 Output (5V):** Connects to **Arduino Uno 5V**, **Arduino Nano 5V**, and **All Servo VCC pins**.
* **Ground (GND):** All components (Battery, Drivers, Arduinos) must share a common ground wire.

![Wiring Diagram for Mobile Manipulator](path/to/wiring_diagram.png)

### 2. Master Connections (Arduino Uno)
| Component | Pin Name | Arduino Uno Pin |
| :--- | :--- | :--- |
| **HC-05 BT** | TX | D10 |
| | RX | D11 |
| **Nano Comms** | TX | D2 (Goes to Nano D2) |
| **L298N Driver** | IN1 | D5 |
| | IN2 | D6 |
| | IN3 | D7 |
| | IN4 | D8 |

### 3. Slave Connections (Arduino Nano)
| Component | Pin Name | Arduino Nano Pin |
| :--- | :--- | :--- |
| **Uno Comms** | RX | D2 (Connects from Uno D3*) |
| **Servo Base** | Signal | D3 |
| **Servo Shoulder** | Signal | D5 |
| **Servo Elbow** | Signal | D6 |
| **Servo Gripper** | Signal | D9 |

*[Note: In the code provided, we only use one-way communication from Uno (TX) to Nano (RX) to save pins.]*

## 📱 App Configuration
Use "Arduino Bluetooth Controller" app in "Controller/Button Mode".

**Key Mapping:**
* **Movement:**
    * `F`: Forward
    * `B`: Backward
    * `L`: Left
    * `R`: Right
    * `S`: Stop (Release button)
* **Arm Control:**
    * `q` / `a`: Base Left / Right
    * `w` / `s`: Shoulder Up / Down
    * `e` / `d`: Elbow Up / Down
    * `o` / `c`: Gripper Open / Close

## ⚠️ Troubleshooting & Common Errors

**1. Brownout / Arduino Resetting**
* **Symptom:** The Arduino restarts when the arm moves or the robot stops suddenly.
* **Cause:** Servos are drawing too much current, causing a voltage drop.
* **Fix:** Ensure you are using a high-amp external power source (Buck converter) for the servos. **Never** power MG996R servos from the Arduino USB or 5V pin.



[Image of LM2596 buck converter wiring]


**2. Bluetooth Not Connecting**
* **Symptom:** Phone cannot find HC-05 or fails to pair.
* **Fix:** Default PIN is usually `1234` or `0000`. Ensure the RX/TX wires on the Uno are not crossed (TX of module goes to Pin 10, RX of module goes to Pin 11).

**3. Jittery Servos**
* **Symptom:** Servos shake uncontrollably.
* **Fix:** This is often electrical noise. Add a 470uF capacitor across the Servo power rails (Positive and Ground) to smooth out the power supply.

**4. Wheels Spinning in Reverse**
* **Symptom:** Robot goes backward when you press Forward.
* **Fix:** Swap the two wires connected to the motor output on the L298N driver for the specific wheel that is reversed.
