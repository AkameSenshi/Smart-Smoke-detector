# Smart Smoke Detector

## Overview
The Smart Smoke Detector is a Wi-Fi-enabled, compact, and aesthetic smoke detection device built using ESP32, MQ-2 smoke sensor, and a TP4056 LiPo charging circuit. It is designed to provide reliable real-time smoke detection and alerting capabilities while maintaining a sleek and modern design. This device communicates with an MQTT broker to report data and sends out an alarm when smoke levels exceed a predefined threshold. The device is housed in a custom-designed 3D-printed enclosure created using Fusion 360.
## Documentation

[Documentation](https://linktodocumentation)


## Features
- Real-Time Smoke Detection: Utilizes the MQ-2 smoke sensor for precise detection.
- Wi-Fi Connectivity: Reports data to an MQTT broker for remote monitoring.
- Threshold-Based Alarming: Triggers a buzzer alarm when smoke levels cross a user-defined threshold.
- LED Indicators: Displays device status and heartbeat.
- Rechargeable Battery Support: Equipped with a TP4056 LiPo charging circuit for uninterrupted power supply.
- Custom Enclosure: Aesthetic and functional 3D-printed design available as STL files.
- Aesthetic Design: Compact, modern, and suitable for home or office environments.
## Technical Specifications

- Microcontroller: ESP32
- Sensor: MQ-2 (smoke and gas sensor)
- Power Circuit: TP4056 LiPo charging circuit
- Communication Protocol: MQTT
- Indicators:
  - LED: Status and heartbeat.
  - Buzzer: Alarm for threshold breach.
- Enclosure:
  - Designed in Fusion 360.
  - Includes STL files for 3D printing.


## How it works

1. The MQ-2 sensor continuously monitors smoke levels.
2. The ESP32 microcontroller processes sensor data and transmits it to an MQTT broker.
3. If the smoke levels exceed a predefined threshold:
- The buzzer sounds an alarm.
- Status updates are sent to the MQTT broker.
4. The LED provides visual feedback for system status and heartbeat.
## Future Plans
- ESP-NOW Protocol Integration: Enable device-to-device communication without relying on Wi-Fi or an external broker.
- Mobile App: Develop an app for real-time notifications and control.
- Extended Sensor Support: Add additional environmental sensors like temperature and humidity.
- Battery Optimization: Improve power efficiency for longer operational hours.
