## Multi-Channel Thermocouple Measurement System (MAX31856)

This project implements a scalable, multi-channel thermocouple data acquisition system using the MAX31856 thermocouple-to-digital converter. Each channel performs independent cold-junction compensation and communicates digitally over SPI, enabling reliable absolute temperature measurement across a wide range of high-temperature and thermal monitoring applications, including welding, heat treatment, and experimental research.

## Why this project exists

Temperature measurement in welding and high-temperature experiments is deceptively hard.
Early prototypes using analog thermocouple amplifiers may appear to work, but often fail under:

- multi-channel conditions

- different environments

- long-term stability

- research scrutiny

This project is a clean redesign that solves those problems properly.

## Key Features

- Multi-channel thermocouple support (one MAX31856 per channel)

- Built-in cold junction compensation (CJC)

- Absolute temperature measurement

- SPI-based scalable architecture

- Per-channel fault detection (open TC, short to GND/VCC)

- Designed for welding & high-temperature experiments

- Clean, modular firmware architecture

## System Overview

Each thermocouple probe is connected to its own MAX31856 IC.
All MAX31856 devices share the SPI bus and are selected using independent Chip Select (CS) lines.
```bash
K-Type Probe → MAX31856 → SPI → MCU
K-Type Probe → MAX31856 → SPI → MCU
K-Type Probe → MAX31856 → SPI → MCU
```


This ensures:

- independent cold-junction measurement per channel

- no analog signal routing issues

- no ADC reference or grounding ambiguity

## Problems with the Previous Setup (Why this Redesign Was Needed)

Before this system, an analog thermocouple amplifier–based setup was used.
Through extensive testing, the following fundamental issues were identified:

**1. No Cold-Junction Compensation**

- Analog amplifiers only measure temperature difference

- Cold junction temperature was assumed, not measured

- Any change in environment broke calibration

- Absolute temperature became environment-dependent

**2. Multi-Channel Cold Junction Mismatch**

- Each amplifier board experienced different local heating

- External PSU + MCU caused PCB thermal gradients

Result:
```bash
T_cold_TC1 ≠ T_cold_TC3 ≠ T_cold_TC4
```

- Channel-to-channel comparison became physically invalid

**3. Static Offset Calibration Was Not Transferable**

- Offsets worked only for one environment

- Changing room temperature, airflow, or power load broke results

- Re-calibration was required for every condition

- Not acceptable for research or reproducibility

**4. Analog Noise & ADC Dependency**

- Shared ADC reference

- Ground offsets

- EMI sensitivity (especially problematic near welding setups)

- Stable trends possible, but absolute temperature was unreliable

## Why MAX31856 Solves These Issues

The MAX31856 is designed specifically to address the above problems:

| Problem                     | MAX31856 Solution                  |
|----------------------------|------------------------------------|
| Cold junction unknown       | ✅ Internal cold-junction sensor   |
| Multi-channel mismatch     | ✅ Per-channel CJC                 |
| Environment dependence     | ✅ Automatic compensation          |
| Analog drift               | ✅ Digital SPI output              |
| Research validity          | ✅ Industry-grade approach         |

## Why This Is Suitable for Welding Applications

- Supports K-type thermocouples (wide temperature range)

- Handles HAZ and near-weld measurements

- Stable under different ambient and power conditions

- Data remains valid across environments

⚠️ Note: Direct molten pool or arc temperatures require specialized probes and techniques.

## Example Applications

- Welding and heat-affected zone (HAZ) monitoring  
- Furnace and kiln temperature measurement  
- Thermal profiling of power electronics  
- Materials and metallurgical research  
- Industrial and laboratory temperature logging  


