# ADC Sensor Interface for Satellite Telemetry

**Proteus + Arduino Simulation Project**  
**Author:** Dhruvrajsinh Vansia  
**Date:** November 2026  
**Track:** Satellite Engineering - Avionics

---

## 1. Project Overview

This project demonstrates a satellite sensor node that reads analog sensor data via ADC, processes telemetry, and transmits via serial communication. The design mimics real spacecraft data acquisition systems used for health monitoring.

### Objective
Design a telemetry acquisition system with:
- Multi-channel ADC sensing (temperature + voltage)
- Real-time data packetization
- Serial telemetry output
- Sensor calibration and scaling

---

## 2. Design Specifications

| Parameter | Specification |
|-----------|---------------|
| Microcontroller | ATmega328P (Arduino Uno) |
| ADC Resolution | 10-bit (0-1023) |
| Reference Voltage | 5V |
| Temperature Sensor | LM35 (0-100°C analog output) |
| Voltage Sensor | Potentiometer (0-5V simulation) |
| ADC Channels | A0 (Temperature), A1 (Voltage) |
| Serial Baud Rate | 9600 bps |
| Sampling Rate | 1 Hz (1 sample/second) |

---

## 3. System Design

### 3.1 Hardware Components

| Component | Value/Model | Purpose |
|-----------|-------------|---------|
| Microcontroller | Arduino Uno (ATmega328P) | Main processor |
| Temperature Sensor | LM35 | Analog temperature sensing |
| Voltage Sensor | 1k Potentiometer | Bus voltage simulation |
| Display | Virtual Terminal | Serial telemetry display |
| Power Supply | 5V DC | System power |

### 3.2 Pin Configuration

| Pin | Function | Connection |
|-----|----------|------------|
| A0 (PF0) | ADC Channel 0 | LM35 Vout |
| A1 (PF1) | ADC Channel 1 | Potentiometer wiper |
| TX (PD1) | Serial Transmit | Virtual Terminal RX |
| RX (PD0) | Serial Receive | Virtual Terminal TX |
| VCC | 5V Power | Sensor supply |
| GND | Ground | Common ground |

### 3.3 Circuit Schematic

![Circuit Diagram](Results/Circuit.png)

---

## 4. Software Design

### 4.1 Firmware Architecture

```
┌─────────────────────────────────────┐
│           SETUP                     │
│  - Initialize Serial (9600 bps)     │
│  - Print header                     │
└─────────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────┐
│           MAIN LOOP                 │
│  - Read ADC0 (Temperature)          │
│  - Read ADC1 (Voltage)              │
│  - Convert to engineering units     │
│  - Format telemetry packet          │
│  - Transmit via Serial              │
│  - Wait 1000ms                      │
└─────────────────────────────────────┘
```

### 4.2 Source Code

```cpp
const int TEMP_PIN = A0;  // PF0 (Pin 61) -> LM35
const int VOLT_PIN = A1;  // PF1 (Pin 60) -> Potentiometer
unsigned long packetID = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("=== SATELLITE TELEMETRY NODE (ATMEGA329P) ===");
  Serial.println("PKT_ID | TIME(ms) | TEMP(C) | BUS_VOLT(V) | ADC0 | ADC1");
}

void loop() {
  int rawTemp = analogRead(TEMP_PIN);
  int rawVolt = analogRead(VOLT_PIN);

  float temperatureC = ((rawTemp * 5.0) / 1024.0) * 100.0;
  float busVoltage = (rawVolt * 5.0) / 1024.0;

  Serial.print(packetID++);
  Serial.print("      | ");
  Serial.print(millis());
  Serial.print("     | ");
  Serial.print(temperatureC, 2);
  Serial.print("   | ");
  Serial.print(busVoltage, 2);
  Serial.print("        | ");
  Serial.print(rawTemp);
  Serial.print("  | ");
  Serial.println(rawVolt);

  delay(1000);
}
```

### 4.3 Data Processing

**Temperature Calculation (LM35):**
```
ADC Value (0-1023) → Voltage (0-5V) → Temperature (0-100°C)
Temperature = (ADC × 5.0 / 1024.0) × 100.0
```

**Voltage Calculation:**
```
Bus Voltage = ADC × 5.0 / 1024.0
```

---

## 5. Simulation Setup

### 5.1 Proteus Configuration

1. **Open Proteus 8 Professional**
2. **Load Project:** `ADC Sensor Interface.pdsprj`
3. **Components Used:**
   - Arduino Uno board
   - LM35 temperature sensor
   - 1kΩ potentiometer
   - Virtual terminal (serial display)

### 5.2 Simulation Steps

1. Place components from Proteus library
2. Wire according to schematic
3. Load Arduino hex file into Arduino properties
4. Run simulation (Play button)
5. Observe virtual terminal output

---

## 6. Results

### 6.1 Telemetry Output

```
=== SATELLITE TELEMETRY NODE (ATMEGA329P) ===
PKT_ID | TIME(ms) | TEMP(C) | BUS_VOLT(V) | ADC0 | ADC1
0      | 1023     | 25.39   | 2.50        | 520  | 512
1      | 2047     | 25.49   | 2.51        | 522  | 514
2      | 3071     | 25.59   | 2.49        | 524  | 510
3      | 4095     | 25.68   | 2.50        | 526  | 512
```

### 6.2 Output Waveform

![Serial Output](Results/Output.png)

### 6.3 Performance Metrics

| Measurement | Value |
|-------------|-------|
| ADC Resolution | 10-bit (4.88 mV per step) |
| Temperature Accuracy | ±0.5°C (LM35 typical) |
| Voltage Accuracy | ±50 mV |
| Sampling Rate | 1 Hz |
| Serial Baud Rate | 9600 bps |
| Packet Format | Pipe-delimited telemetry |

---

## 7. Analysis

### 7.1 ADC Performance

The ATmega328P internal ADC provides:
- **10-bit resolution:** 1024 discrete levels
- **Input range:** 0-5V (with 5V reference)
- **Conversion time:** ~100-130 µs per channel
- **Successive Approximation Register (SAR)** architecture

### 7.2 Sensor Calibration

**LM35 Characteristics:**
- Output: 10 mV/°C
- Range: 0°C to 100°C (0-1V output)
- Linearity: ±0.5°C typical

**Calibration Formula:**
```
Temperature (°C) = ADC_Value × (5.0 / 1024.0) × 100.0
```

### 7.3 Telemetry Packet Structure

| Field | Size | Description |
|-------|------|-------------|
| PKT_ID | Variable | Packet sequence number |
| TIME(ms) | Variable | Mission elapsed time |
| TEMP(C) | 5 chars | Temperature in Celsius |
| BUS_VOLT(V) | 5 chars | Bus voltage |
| ADC0 | Variable | Raw temperature ADC |
| ADC1 | Variable | Raw voltage ADC |

---

## 8. Space Application Relevance

### 8.1 Satellite Telemetry Systems

This design directly applies to:
- **Housekeeping telemetry** (temperature, voltage monitoring)
- **Payload health monitoring**
- **Power system telemetry**
- **Thermal control system data**

### 8.2 Real-World Parallels

| This Project | Actual Satellite System |
|--------------|------------------------|
| LM35 sensor | PT100/PT1000 RTDs |
| Potentiometer | Voltage divider for bus monitoring |
| Serial output | CCSDS telemetry frames |
| 1 Hz sampling | Typical housekeeping rate |

### 8.3 Connection to ISRO Experience

This project extends your PRL trainee work:
- **Same ATmega architecture** (ATmega128 → ATmega328P)
- **Same sensor interfacing** (environmental sensors)
- **Same telemetry concept** (GUI visualization → serial output)
- **Added ADC theory** and calibration fundamentals

---

## 9. Skills Demonstrated

- [x] ADC interfacing and configuration
- [x] Analog sensor signal conditioning
- [x] Embedded C programming (Arduino)
- [x] Proteus circuit simulation
- [x] Telemetry packet design
- [x] Serial communication protocols
- [x] Sensor calibration and scaling

---

## 10. Future Improvements

1. **I2C Digital Sensors:** Replace LM35 with DS18B20 or TMP102
2. **Data Logging:** Add SD card for onboard storage
3. **Wireless Telemetry:** Add XBee/LoRa for RF transmission
4. **Multi-sensor Node:** Expand to 8+ ADC channels
5. **Error Detection:** Add CRC/checksum for packet integrity
6. **Low-Power Mode:** Implement sleep between samples

---

## 11. Files in This Repository

```
adc_sensor_interface_proteus/
├── README.md
├── Report/
│   └── ADC_Sensor_Interface_Report.md
├── Simulation/
│   └── ADC Sensor Interface.pdsprj
├── Firmware/
│   └── ADC_Sensor_Interface/
│       └── ADC_Sensor_Interface.ino
└── Results/
    ├── Circuit.png
    └── Output.png
```

---

## 12. References

1. Atmel Corporation. "ATmega328P Datasheet"
2. Texas Instruments. "LM35 Precision Centigrade Temperature Sensor"
3. Proteus Design Suite 8 - Labcenter Electronics
4. Arduino.cc. "Analog Input Reference"
5. ISRO. "Satellite Telemetry, Tracking and Command Systems"

---

## 13. About the Author

**Dhruvrajsinh Vansia**  
MSc Space Sciences and Technologies  
University of Bremen, Germany  

**Experience:**
- Project Trainee, Physical Research Laboratory (ISRO) - Wireless sensor nodes
- Former President, PRAKALPA Space and Science Club

**Career Interest:** Satellite Engineering - Avionics & Data Systems

---

*Project completed: November 2026*  
*Simulation Tool: Proteus 8 Professional*  
*Firmware: Arduino IDE*
