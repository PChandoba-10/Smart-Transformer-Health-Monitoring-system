# Smart Transformer Health Monitoring System using ESP32

An IoT-based embedded system for real-time transformer health monitoring and protection using the ESP32 microcontroller. The system continuously monitors transformer temperature, load current, and oil level. When abnormal conditions are detected, it automatically disconnects the load and sends remote alerts while logging data to the cloud.

---

##  Project Overview

Power transformers are critical components in electrical power systems. Continuous monitoring of their operating conditions helps prevent failures, reduces maintenance costs, and improves system reliability.

This project provides an automated monitoring solution that measures:

-  Transformer Temperature
-  Load Current
-  Transformer Oil Level

The system compares the measured values against predefined safety thresholds. If any parameter exceeds its safe operating limit, it:

- Disconnects the load using a relay
- Activates a buzzer
- Sends GSM and Telegram alerts
- Updates the Blynk dashboard
- Stores sensor data on ThingSpeak for historical analysis

---

## Features

- Real-time transformer health monitoring
- Temperature monitoring using LM35
- Load current monitoring using ACS712
- Oil level monitoring using HC-SR04 Ultrasonic Sensor
- Automatic fault detection
- Relay-based load protection
- GSM SMS notification
- Telegram alert system
- Blynk IoT dashboard
- ThingSpeak cloud data logging
- ESP32 Wi-Fi connectivity

---

## Hardware Components

| Component | Purpose |
|-----------|----------|
| ESP32 DevKit | Main Controller |
| LM35 | Temperature Sensor |
| ACS712 (20A) | Current Sensor |
| HC-SR04 | Oil Level Measurement |
| Relay Module | Load Protection |
| SIM800L | GSM SMS Alerts |
| Passive Buzzer | Fault Indication |
| Buck Converter | Stable Power Supply |
| Transformer | Test Load |

---

## Software & Tools

- PlatformIO
- Arduino Framework
- Embedded C/C++
- Blynk IoT
- ThingSpeak
- Telegram Bot

---

## System Working

1. ESP32 initializes all sensors and connects to Wi-Fi.
2. Temperature, current, and oil level are measured continuously.
3. Sensor values are compared with predefined threshold values.
4. If all parameters are within safe limits:
   - Load remains connected.
   - Data is uploaded to ThingSpeak.
   - Live values are displayed on Blynk.
5. If any parameter exceeds the threshold:
   - Relay disconnects the load.
   - Buzzer turns ON.
   - GSM sends an SMS alert.
   - Telegram notification is sent.
   - Fault information is displayed on Blynk.

---

## Monitoring Parameters

| Parameter | Sensor |
|-----------|--------|
| Temperature | LM35 |
| Current | ACS712 |
| Oil Level | HC-SR04 |

## Future Improvements

- TinyML-based fault prediction
- Predictive maintenance
- Mobile application
- OTA firmware updates
- SD card data logging
- MQTT communication
- AI-based transformer health analysis


##  Learning Outcomes

Through this project, I gained hands-on experience in:

- Embedded C/C++ Programming
- ESP32 Firmware Development
- Sensor Interfacing
- ADC Programming
- UART Communication
- GPIO Control
- Relay Control
- IoT Integration
- Cloud Data Logging
- Hardware Debugging
- System Integration


