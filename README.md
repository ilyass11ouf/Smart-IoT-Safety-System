# 🔥 Smart IoT Safety System: ESP32 & ESP8266 Gas & Water Leak Detector with MQTT

**By Ilyass Oufaris**

This project monitors gas and water leaks in real-time using ESP32 and ESP8266 boards with DHT11, MQ2, and water sensors. It communicates via MQTT and triggers alarms when leaks are detected. Perfect for learning IoT and MQTT communication.

---

## 📌 System Overview

- **ESP8266 — Kitchen Node**: DHT11 + MQ2, sends data via MQTT  
- **ESP32 — Main Hub**: DHT11 + MQ2 + Water Sensor + Buzzer, receives MQTT data  
- **Communication**: MQTT using Mosquitto broker (`kitchen_node/data` topic)  

---

## 🛠 Hardware

- ESP8266 NodeMCU  
- ESP32 Dev Module  
- DHT11 x2  
- MQ2 Gas Sensor x2  
- Water Sensor  
- Passive Buzzer  
- Breadboard & jumper wires  

---

## 💻 Software

- Arduino IDE  
- Libraries: PubSubClient, DHT sensor library, Adafruit Unified Sensor  
- Mosquitto MQTT Broker (Windows)  

---

## ⚡ Quick Setup

1. Install Arduino IDE  
2. Add ESP32 & ESP8266 boards in Preferences → Additional Boards Manager URLs:  
```

[https://arduino.esp8266.com/stable/package_esp8266com_index.json](https://arduino.esp8266.com/stable/package_esp8266com_index.json),
[https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)

```
3. Install the boards via Boards Manager  
4. Install required libraries via Library Manager  

---

## 🔌 Wiring

**ESP8266 (Kitchen Node)**: DHT11 → D2, MQ2 → A0, VCC → 3.3V, GND → GND  
**ESP32 (Main Hub)**: DHT11 → GPIO 4, MQ2 → GPIO 34, Water → GPIO 35, Buzzer → GPIO 18  

---

## 🚀 Mosquitto Setup

1. Install Mosquitto for Windows  
2. Allow firewall access  
3. Configure `mosquitto.conf`:  
```

listener 1883
allow_anonymous true

```
4. Run CMD →  
```

D:
cd Mosquitto
mosquitto.exe -c mosquitto.conf -v

```

---

## 🖥 Testing

- Upload `ESP8266_KitchenNode.ino` to ESP8266, baud 9600  
- Upload `ESP32_MainHub.ino` to ESP32, baud 115200  
- Open Serial Monitors to see sensor data  
- Buzzer triggers on gas/water leak detection  

---

## ⚠ Common Issues

- MQTT rc=-2 → Mosquitto not running or wrong IP  
- DHT returns NaN → check wiring or sensor  
- MQ2 max = 1023 on ESP8266 → normal 10-bit ADC  

---

## 🔐 Security

Do not upload real Wi-Fi credentials. Use placeholders.  

---

## 📌 License

MIT License – Free to use and modify  

---

## 🌍 Author

**Ilyass Oufaris** – IoT and embedded systems learning project
```


