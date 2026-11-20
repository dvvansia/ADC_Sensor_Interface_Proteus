# ADC Sensor Interface - Proteus Simulation

Satellite telemetry acquisition system using ATmega328P ADC for multi-sensor data acquisition.

## Project Overview

This project simulates a spacecraft sensor node that reads analog sensors via ADC, processes telemetry data, and transmits via serial communication. Designed in Proteus 8 Professional with Arduino firmware.

## Specifications

| Parameter | Value |
|-----------|-------|
| Microcontroller | ATmega328P (Arduino Uno) |
| ADC Resolution | 10-bit (0-1023) |
| Temperature Sensor | LM35 (0-100°C) |
| Voltage Sensor | Potentiometer (0-5V) |
| ADC Channels | 2 (A0, A1) |
| Serial Baud | 9600 bps |
| Sampling Rate | 1 Hz |

## Features

- Multi-channel ADC telemetry acquisition
- Real-time sensor data processing
- Serial telemetry output (CCSDS-style packets)
- Proteus circuit simulation
- Arduino firmware included

## Files

- `Report/ADC_Sensor_Interface_Report.md` - Full technical report
- `Simulation/ADC Sensor Interface.pdsprj` - Proteus project file
- `Firmware/ADC_Sensor_Interface.ino` - Arduino source code
- `Results/` - Simulation screenshots

## Quick Start

### Simulation

1. Open Proteus 8 Professional
2. Load `Simulation/ADC Sensor Interface.pdsprj`
3. Click Play (Run Simulation)
4. Observe telemetry on virtual terminal

### Firmware

1. Open `Firmware/ADC_Sensor_Interface/ADC_Sensor_Interface.ino` in Arduino IDE
2. Select Board: Arduino Uno
3. Compile (Verify)
4. Export compiled binary for Proteus

## Telemetry Output Format

```
=== SATELLITE TELEMETRY NODE (ATMEGA329P) ===
PKT_ID | TIME(ms) | TEMP(C) | BUS_VOLT(V) | ADC0 | ADC1
0      | 1023     | 25.39   | 2.50        | 520  | 512
```

## Applications

- CubeSat housekeeping telemetry
- Satellite thermal monitoring
- Power system voltage sensing
- Embedded sensor node prototyping
- ADC interfacing education

## Author

**Dhruvrajsinh Vansia**  
MSc Space Sciences and Technologies  
University of Bremen, Germany  

**Experience:** Project Trainee, Physical Research Laboratory (ISRO)

## Related Projects

- [Buck Converter LTSpice](https://github.com/dvvansia/buck_convertor_LTSpice) - Satellite power regulation

---

*Project Date: November 2026*  
*Tools: Proteus 8 Professional, Arduino IDE*
