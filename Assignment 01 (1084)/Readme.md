# 📘 Assignment 1 – Embedded IoT Systems  
**Name:** Noor Ul Huda  
**Reg No:** 23-NTU-CS-1084  
**Course:** Embedded IoT Systems  
**Instructor:** Sir Nasir Mehmood  
**Date:** 26-Oct-2025  

---

## 🧩 Overview  
This assignment contains **two ESP32-based projects** developed and tested on the **Wokwi Simulator**.  
Both projects demonstrate **hardware interfacing, sensor input handling, and OLED-based visual feedback.**

---

## 🔹 Task 1 – Device Control using ESP32 (LEDs, Buttons, Buzzer & OLED)

### 📝 Description  
ESP32 controls **three LEDs**, **two buttons**, and a **buzzer**, with visual messages displayed on the **OLED**.  
Buttons toggle the LEDs and buzzer states, and the OLED updates in real-time to reflect changes.

### 🔧 Components Used
- ESP32 DevKitC V4  
- OLED 128x64 (I2C)  
- LEDs × 3  
- Buzzer × 1  
- Push Buttons × 2  
- 420Ω Resistors × 3  
- Jumper wires  

### ⚙️ Pin Map

| Component | Pin Name | GPIO No. |
|------------|-----------|----------|
| LED 1 | D2 | GPIO 2 |
| LED 2 | D4 | GPIO 4 |
| LED 3 | D5 | GPIO 5 |
| Button 1 | D26 | GPIO 26 |
| Button 2 | D27 | GPIO 27 |
| Buzzer | D15 | GPIO 15 |
| OLED SDA | SDA | GPIO 21 |
| OLED SCL | SCL | GPIO 22 |

### 🌐 Wokwi Project Link  
🔗 [View Simulation on Wokwi](https://wokwi.com/projects/445712677554764801)

### 🖼️ Screenshots  
![Task 1 Output](./Task_1/task1_output.png)  
![Task 1 Wokwi](./Task_1/task1_wokwi.png)  
![Task 1 Hardware](./Task_1/task1_breadboard.jpg)

---

## 🔸 Task 2 – Button Press Duration Detection (Short / Long Press with OLED)

### 📝 Description  
This task detects **short and long button presses** using the ESP32.  
- A **short press** toggles the LED.  
- A **long press** activates the buzzer.  
- The **OLED** shows the corresponding feedback message.

### 🔧 Components Used
- ESP32 DevKitC V4  
- OLED 128x64 (I2C)  
- Push Button × 1  
- LED × 1  
- Buzzer × 1  
- Resistor × 1  

### ⚙️ Pin Map

| Component | Pin Name | GPIO No. |
|------------|-----------|----------|
| LED | D5 | GPIO 5 |
| Button | D25 | GPIO 25 |
| Buzzer | D18 | GPIO 18 |
| OLED SDA | SDA | GPIO 21 |
| OLED SCL | SCL | GPIO 22 |

### 🌐 Wokwi Project Link  
🔗 [View Simulation on Wokwi](https://wokwi.com/projects/445714036162391041)

### 🖼️ Screenshots  
![Task 2 Output](./Task_2/task2_output.png)  
![Task 2 Wokwi](./Task_2/task2_wokwi.png)  
![Task 2 Hardware](./Task_2/task2_breadboard.jpg)

---

## ✅ Summary  
This assignment demonstrates fundamental **IoT device control and interaction logic** using the **ESP32 platform**.  
- **Task 1:** Focused on multiple device control and OLED status feedback.  
- **Task 2:** Implemented **short and long press detection logic** with visual output.  

Both tasks were fully simulated and verified on **Wokwi**.

---
