# Wiring Guide – Multi-Channel MAX31856 System (ESP32)

This document describes the **hardware wiring** for a **multi-channel thermocouple measurement system** using **MAX31856 modules** with an **ESP32** microcontroller.

The wiring is designed for:
- Correct SPI operation on ESP32
- Multi-channel scalability
- Low-noise operation in welding environments

---

## 1. System Architecture

Each thermocouple channel uses **one MAX31856 IC**.  
All MAX31856 modules share the same **SPI bus**, while each module has a **dedicated Chip Select (CS)** line.
```bash
Thermocouple → MAX31856 → SPI → ESP32
Thermocouple → MAX31856 → SPI → ESP32
Thermocouple → MAX31856 → SPI → ESP32
```

Each channel performs **independent cold-junction compensation** inside the MAX31856.

---

## 2. ESP32 SPI Pins (Recommended)

ESP32 has multiple SPI buses.  
This project uses **VSPI** (default and most stable).

| SPI Signal | ESP32 Pin (VSPI) |
|----------|------------------|
| SCK      | GPIO 18 |
| MOSI    | GPIO 23 |
| MISO    | GPIO 19 |

These pins are configurable in software, but using VSPI defaults avoids conflicts.

---

## 3. Shared SPI Connections

All MAX31856 modules connect to the same SPI lines.

| ESP32 Pin | MAX31856 Pin | Description |
|---------|-------------|------------|
| GPIO 18 | SCK | SPI Clock |
| GPIO 23 | SDI | SPI Data (ESP32 → MAX31856) |
| GPIO 19 | SDO | SPI Data (MAX31856 → ESP32) |
| GND     | GND | Common Ground |
| 3.3V    | VCC | Power Supply |

⚠️ **Important**
- ESP32 is **3.3V logic only**
- MAX31856 **must be powered at 3.3V**
- Do **NOT** use 5V logic on SPI lines

---

## 4. Chip Select (CS) – One Per Channel

Each MAX31856 requires a **unique CS pin** on the ESP32.

Example mapping:

| Channel | MAX31856 | ESP32 CS Pin |
|------|----------|-------------|
| TC1 | MAX31856 #1 | GPIO 5 |
| TC2 | MAX31856 #2 | GPIO 17 |
| TC3 | MAX31856 #3 | GPIO 16 |
| TC4 | MAX31856 #4 | GPIO 4 |
| TC5 | MAX31856 #5 | GPIO 15 |

Rules:
- CS is **active LOW**
- Only one CS must be LOW at a time
- Never leave CS floating

---

## 5. Thermocouple Probe Wiring

### Recommended Thermocouple
- **K-type** (best for welding-related temperatures)

### Typical K-type Color Code
| Wire | Polarity |
|----|---------|
| Yellow | T+ |
| Red    | T− |

### Connection to MAX31856
| Thermocouple Wire | MAX31856 Terminal |
|------------------|------------------|
| T+ (Yellow) | T+ |
| T− (Red)    | T− |

⚠️ Reversed polarity will result in incorrect temperature readings.

---

## 6. Power Supply Notes (Critical)

- Power MAX31856 modules from **ESP32 3.3V rail** or a **dedicated low-noise 3.3V regulator**
- Ensure:
  - Common ground between ESP32 and all MAX31856 boards
  - No high-current loads (motors, relays, welders) share the measurement supply

For welding environments, **power isolation** improves stability.

---

## 7. Noise & EMI Best Practices (Welding-Specific)

Welding setups are electrically noisy. Follow these guidelines:

- Keep SPI wires **short**
- Twist thermocouple leads
- Route thermocouple cables **away from welding leads**
- Avoid running SPI lines parallel to high-current cables
- Use star grounding where possible
- Do not create ground loops between PSU, ESP32, and MAX31856 modules

Because the signal path is digital, noise sensitivity is **significantly lower** than analog thermocouple amplifiers.

---

## 8. Scaling the System

To add a new thermocouple channel:

1. Add one MAX31856 module
2. Connect it to the shared SPI bus
3. Assign a new CS pin
4. Register the CS pin in firmware

No analog redesign or recalibration is required.

---

## 9. Common Wiring Mistakes to Avoid

❌ Powering MAX31856 at 5V  
❌ Mixing 5V logic with ESP32 SPI  
❌ Leaving CS pins floating  
❌ Long unshielded SPI wiring  
❌ Missing common ground  

---

## 10. Summary

- ESP32 uses **3.3V SPI**
- One MAX31856 per thermocouple
- Shared SPI bus, unique CS per channel
- Built-in cold-junction compensation
- Suitable for multi-channel welding temperature measurement

This wiring approach ensures **stable, reproducible, and research-grade data acquisition**.

---
