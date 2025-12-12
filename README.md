# 🤖 Bluetooth-Controlled Mobile Manipulator

A robust, wirelessly controlled robotics system that combines a 4-wheel drive mobile chassis with a 4-degree-of-freedom robotic arm. This project utilizes a dual-microcontroller architecture to ensure efficient power management and signal stability.

## 👥 Project Team
**Designed and Developed by:**
* **Pravalika Kota**
* **Jampu Brahma Teja**
* **Lokesh Jaya rao**

---

## 📖 Overview
This project bridges the gap between mobility and manipulation. Users can remotely drive the robot and operate the robotic arm using a smartphone app via Bluetooth. The system is split into two independent processing units:
1.  **Mobile Base (Master):** Controlled by an **Arduino Uno with an L293D Motor Shield**. It handles navigation and Bluetooth communication.
2.  **Robotic Arm (Slave):** Controlled by an **Arduino Nano with a V5 Servo Shield**. It handles the precise PWM signals required for the arm's servo motors.

---

## 🛠️ Hardware Requirements

### Microcontrollers & Shields
* 1x Arduino Uno R3
* 1x L293D Motor Drive Shield (v1)
* 1x Arduino Nano
* 1x Nano V5 I/O Expansion Shield (Sensor Shield)

### Actuators
* 4x DC Gear Motors (BO Motors) + Wheels
* 3x MG996R Metal Gear High-Torque Servos (Base, Shoulder, Elbow)
* 1x SG90 Micro Servo (Gripper)

### Power & Communication
* 1x HC-05 or HC-06 Bluetooth Module
* 1x 12V Li-Ion or Li-Po Battery Pack
* 1x LM2596 Buck Converter (Step-down module 12V → 5V)
* Jumper Wires (Male-Male, Male-Female, Female-Female)

---

## 🔌 Wiring & Connections (Step-by-Step)

### Step 1: Mobile Base (Master Unit)
**Components:** Arduino Uno + L293D Shield + HC-05 Bluetooth + DC Motors.

1.  **Mount the Shield:** Plug the L293D Motor Shield directly on top of the Arduino Uno.
2.  **Connect Motors:**
    * Front Left Motor wires → Terminal **M1**
    * Front Right Motor wires → Terminal **M2**
    * Back Left Motor wires → Terminal **M3**
    * Back Right Motor wires → Terminal **M4**
3.  **Connect Bluetooth (Using Analog Pins):**
    * Since the shield uses digital pins, we use Analog pins as Digital I/O.
    * **HC-05 VCC** → Shield 5V
    * **HC-05 GND** → Shield GND
    * **HC-05 TX** → Arduino **A0**
    * **HC-05 RX** → Arduino **A1**
4.  **Connect Communication Link:**
    * Arduino **A2** → Goes to Arduino Nano Pin **D2** (See Step 2).
    * Arduino **GND** → Goes to Arduino Nano **GND** (Common Ground is critical).

### Step 2: Robotic Arm (Slave Unit)
**Components:** Arduino Nano + V5 Shield + Servos.

1.  **Mount the Nano:** Plug the Arduino Nano into the V5 Expansion Shield.
2.  **Connect Servos:** Plug servos into the 3-pin headers (Signal - Voltage - Ground) on the shield.
    * **Base Servo:** Pin **D3**
    * **Shoulder Servo:** Pin **D5**
    * **Elbow Servo:** Pin **D6**
    * **Gripper Servo:** Pin **D9**
3.  **Connect Communication Link:**
    * Nano **D2** (RX) → Connected from Uno **A2**.

### Step 3: Power Distribution (CRITICAL)
**Improper power wiring will cause the Arduino to reset continuously.**

1.  **Source:** Connect the 12V Battery to a switch.
2.  **To L293D Shield:**
    * Connect 12V (+) to the **EXT_PWR** block on the shield.
    * Connect Battery (-) to the **GND** block.
    * **Important:** Remove the "PWR" jumper on the shield to prevent feeding 12V into the Arduino's 5V line.
3.  **To Servo Shield:**
    * Connect 12V Battery to the **Input** of the LM2596 Buck Converter.
    * Adjust Buck Converter output to **5V - 6V**.
    * Connect the Buck Converter **Output (+/-)** to the **External Power Terminal** on the Nano V5 Shield.
    * **Do not** rely on USB power for the servos.

---

## 💻 Software Setup

### Prerequisites
1.  Download & Install **Arduino IDE**.
2.  Install the **AFMotor Library**:
    * Open Arduino IDE → Sketch → Include Library → Manage Libraries.
    * Search for `AFMotor`.
    * Install **"Adafruit Motor Shield library"** (v1.0.0 is standard).

### Uploading Code
1.  **Upload Master Code:**
    * Connect Arduino Uno via USB.
    * Select Board: "Arduino Uno".
    * **Disconnect the HC-05 Bluetooth Module (VCC wire) while uploading.**
    * Upload `Master_Code.ino`.
    * Reconnect Bluetooth.
2.  **Upload Slave Code:**
    * Connect Arduino Nano via USB.
    * Select Board: "Arduino Nano" (Select "Old Bootloader" if upload fails).
    * Upload `Slave_Code.ino`.

---

## 📱 App Configuration & Control

Use the **"Arduino Bluetooth Controller"** app (available on Play Store) or any Bluetooth Terminal.
**Set the mode to: Controller Mode / Gamepad Mode.**

### Control Mapping

| Action | Button Setting (Data to Send) |
| :--- | :--- |
| **Move Forward** | `F` |
| **Move Backward** | `B` |
| **Turn Left** | `L` |
| **Turn Right** | `R` |
| **Stop** | `S` (Configure button "On Release" to send S) |
| **Base Left** | `q` |
| **Base Right** | `a` |
| **Shoulder Up** | `w` |
| **Shoulder Down** | `s` |
| **Elbow Up** | `e` |
| **Elbow Down** | `d` |
| **Gripper Open** | `o` |
| **Gripper Close** | `c` |

---

## ⚠️ Troubleshooting Guide

| Issue | Possible Cause | Solution |
| :--- | :--- | :--- |
| **"Motor Shield Not Found" Error** | Missing Library | Install `AFMotor` library in Arduino IDE. |
| **Robot resets when Arm moves** | Brownout / Low Power | Ensure Servos are powered by the Buck Converter, not the Arduino. |
| **Bluetooth fails to connect** | Wrong PIN or wiring | PIN is usually `1234`. Check if TX/RX are crossed (TX->A0, RX->A1). |
| **Arm doesn't respond** | Broken Serial Link | Check connection between Uno **A2** and Nano **D2**. Ensure Common Ground. |
| **Motors spin wrong way** | Polarity reversed | Swap the two wires of the specific motor at the screw terminal. |

---
