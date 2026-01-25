# WiFi-Enabled Sign Language Translation Glove

A smart wearable glove that translates hand gestures into text and speech using an ESP32 microcontroller. This project modifies the original Arduino-based design to use WiFi for a direct, low-latency connection to a mobile app, eliminating the need for a separate Bluetooth module.

##  Features
- **Microcontroller:** ESP32 (Integrated WiFi & Bluetooth).
- **Sensors:** - 5x Flex Sensors (for finger bending).
  - 1x MPU6050 (Accelerometer/Gyroscope for hand tilt and movement).
- **Connectivity:** WiFi (TCP/IP) - Connects directly to the mobile app.
- **Output:** Text and Speech output via the connected Smartphone App.
- **Power:** Battery powered for portability.

##  Hardware Requirements
1. **ESP32 Development Board** (e.g., ESP32 DOIT DevKit V1).
2. **MPU6050** Accelerometer/Gyroscope Module.
3. **5x Flex Sensors** (2.2 inch or 4.5 inch).
4. **5x 10kΩ Resistors** (for voltage dividers).
5. **Glove** (to mount the sensors).
6. **Battery** (Power bank or LiPo battery via 5V/USB).
7. **Jumper Wires & Breadboard/PCB**.

##  Circuit Connections
**Critical Note:** When using WiFi on the ESP32, you **cannot** use ADC2 pins. You must use **ADC1** pins for the analog sensors.

| Component       | ESP32 Pin | Description |
|-----------------|-----------|-------------|
| **MPU6050 VCC** | 3.3V      | Power       |
| **MPU6050 GND** | GND       | Ground      |
| **MPU6050 SDA** | GPIO 21   | I2C Data    |
| **MPU6050 SCL** | GPIO 22   | I2C Clock   |
| **Flex 1 (Thumb)**| GPIO 36 (VP)| Analog In |
| **Flex 2 (Index)**| GPIO 39 (VN)| Analog In |
| **Flex 3 (Middle)**| GPIO 34   | Analog In |
| **Flex 4 (Ring)** | GPIO 35   | Analog In |
| **Flex 5 (Pinky)**| GPIO 32   | Analog In |

*Note: Connect one leg of the Flex Sensor to 3.3V. Connect the other leg to the ESP32 Pin AND to GND via a 10kΩ resistor (Voltage Divider).*

##  Software Setup
1. **Install Arduino IDE**.
2. **Install ESP32 Board Manager**:
   - Go to `File` > `Preferences`.
   - Add `https://dl.espressif.com/dl/package_esp32_index.json` to "Additional Board Manager URLs".
   - Go to `Tools` > `Board` > `Board Manager` and search for "esp32" by Espressif Systems. Install it.
3. **Install Libraries**:
   - Go to `Sketch` > `Include Library` > `Manage Libraries`.
   - Install **Adafruit MPU6050** and **Adafruit Unified Sensor**.

##  Configuration & Calibration

1. Upload the code and open the **Serial Monitor** (115200 baud).
2. Bend your fingers and note the "Min" (straight) and "Max" (bent) values for each finger.
3. Update the logical thresholds in the `loop()` function (e.g., `if (thumb > 2000)...`) to match your specific readings.
4. Update the **WiFi Credentials** (`ssid` and `password`) in the code to match your network (or your phone's hotspot).

##  App Integration
The ESP32 acts as a **WiFi Server**. 
1. The ESP32 will print its **IP Address** to the Serial Monitor upon starting.
2. Your Android/iOS app should act as a **TCP Client** and connect to this IP Address on **Port 80**.
3. The glove sends string data which the app interprets and speaks.
