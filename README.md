# 🌱 Smart Plant Monitoring System using ESP8266 & Blynk

This project is an IoT-based **Smart Plant Monitoring System** built using the ESP8266 NodeMCU, Blynk IoT platform, and sensors for monitoring temperature, humidity, soil moisture, and motion detection.

> 💡 Ideal for home gardening automation or learning how to integrate hardware with IoT platforms like Blynk.

---

## 🔧 Features

- 🌡️ **DHT11 Sensor** – Measures Temperature and Humidity
- 💧 **Soil Moisture Sensor** – Monitors soil wetness and displays it. 
- 🚨 **PIR Motion Sensor** – Detects movement and triggers Blynk alerts
- ⚙️ **Relay Module + Water Pump** – Allows plant watering via Blynk app
- 📱 **Blynk IoT App** – View real-time data and control the pump remotely

---

## 🧰 Hardware Used

| Component            | Quantity |
|----------------------|----------|
| ESP8266 NodeMCU      | 1        |
| DHT11 Sensor         | 1        |
| Soil Moisture Sensor | 1        |
| PIR Motion Sensor    | 1        |
| Relay Module         | 1        |
| Mini Water Pump      | 1        |
| 3.7V Li-ion Battery  | 1        |
| Jumper Wires         | Several  |
| Breadboard           | 1        |

---

## 🖥️ Software Used

- **Arduino IDE** (for writing and uploading code)
- **Blynk IoT App** (for dashboard and device control)
- **Libraries:**
  - `ESP8266WiFi.h`
  - `BlynkSimpleEsp8266.h`
  - `DHT.h`

---

## 🧠 How It Works

- Sensor readings are sent to Blynk every few seconds.
- If motion is detected, an alert is sent to Blynk and logged as an event.
- The water pump can be manually activated via the Blynk app using the button assigned to Virtual Pin `V12`.

---

## 📸 Demo

<img width="850" height="600" alt="Screenshot 2025-07-14 135819" src="https://github.com/user-attachments/assets/04717268-401a-4e5b-9d41-0a4829eacdc6" />

<img width="452" height="600" alt="Screenshot 2025-07-14 140933" src="https://github.com/user-attachments/assets/4a30d242-99bf-4702-91f7-8da37f90fc1b" />


---

