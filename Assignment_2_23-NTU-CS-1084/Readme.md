# ESP32 IoT Assignment - Web Server & Blynk Cloud Integration

##  Overview
This repository contains my **IoT assignment based on ESP32**, covering two main concepts:
1. ESP32 Web Server for temperature and humidity monitoring  
2. ESP32 interfacing with **Blynk Cloud** for real-time data visualization  

The project demonstrates practical implementation of **Wi-Fi based IoT systems** using ESP32 and DHT sensors.

---

##  Hardware Components Used
- ESP32 Development Board  
- DHT11 / DHT22 Temperature & Humidity Sensor  
- OLED Display  
- Push Button  
- Jumper Wires  
- Breadboard  

---

##  Software & Tools
- Arduino IDE  
- ESP32 Board Package  
- Blynk IoT Platform  
- Required Libraries:
  - WiFi.h  
  - WebServer.h  
  - DHT Sensor Library  
  - Adafruit OLED Libraries  
  - Blynk Library  

---

## Project Structure
 webserver.cpp # ESP32 Web Server based temperature & humidity monitoring
 blynk.cpp # ESP32 Blynk Cloud integration code
 README.md # Project documentation


---

##  Part 1: ESP32 Web Server (webserver.cpp)

###  Description
In this part, ESP32 works as a **web server** that displays temperature and humidity values on a web browser using HTTP.

### Features
- ESP32 connects to Wi-Fi and gets an IP address  
- Web server runs on port 80  
- Sensor data is displayed on a dynamically generated HTML webpage  
- Button is used to trigger sensor reading  
- OLED displays updated values  
- Meta refresh updates webpage automatically  

---

##  Part 2: Blynk Cloud Interfacing (blynk.cpp)

###  Description
This part shows how ESP32 sends temperature and humidity data to **Blynk Cloud** and displays it on the dashboard using virtual pins.

###  Features
- Blynk Template and Datastream creation  
- Secure cloud connection using Auth Token  
- Real-time sensor data display  
- Virtual pins for cloud communication  
- Non-blocking execution using `BlynkTimer`  

---

##  Configuration Steps
1. Install required libraries in Arduino IDE  
2. Select correct ESP32 board and COM port  
3. Update Wi-Fi credentials in code  
4. Add Blynk Template ID, Template Name, and Auth Token  
5. Upload code to ESP32  

---

##  Common Issues & Solutions
- **ESP32 not connecting to Wi-Fi:** Check SSID and password  
- **Wrong sensor values:** Verify DHT sensor type in code  
- **Blynk device offline:** Check Auth Token and template mapping  
- **Web page not loading:** Confirm IP address and port  

---

##  Conclusion
This assignment helped me understand **ESP32 web servers**, **cloud-based IoT communication**, and **real-time sensor monitoring**.  
Both local web monitoring and cloud-based visualization were successfully implemented.

---

## Author
**Name:** _Noor ul huda_  
**Course:** Embedded & IoT Systems  
**Instructor:** _Nasir Mehmood_  
**Institute:** _NTU_

---