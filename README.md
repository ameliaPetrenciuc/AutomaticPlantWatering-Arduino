# Smart Plant Watering System - Arduino

## Description
This project is an automatic plant watering system using Arduino, designed to monitor soil moisture and temperature and control water flow via a PWM water pump. The entire system is managed through a mobile application via Bluetooth communication.

## Key Features
- **Temperature & Humidity Monitoring**: Uses a temperature and humidity sensor to track environmental conditions.
- **Automated Watering**: Controls a PWM water pump based on soil moisture levels.
- **Bluetooth Connectivity**: Allows remote monitoring and manual control through a mobile app.
- **Energy Efficient**: The system operates only when necessary, optimizing water and power usage.

## Components Used
- **Arduino Board** (Arduino Jade)
- **Soil Moisture Sensor**
- **Temperature & Humidity Sensor**
- **PWM Controlled Water Pump**
- **Bluetooth Module (HC-05)**
- **Relay Module**
- **Power Supply (Battery)**

## System Architecture
1. The temperature and humidity sensor continuously reads environmental conditions.
2. The soil moisture sensor detects the water level in the soil.
3. When the soil moisture is below a predefined threshold, the pump is activated using PWM control.
4. Users can override automatic control via a mobile app connected through Bluetooth.
5. Real-time data is displayed in the mobile application for monitoring.



