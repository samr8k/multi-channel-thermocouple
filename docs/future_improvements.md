# Future Improvements

The current implementation focuses on **measurement correctness, stability, and reproducibility**.  
Additional features are intentionally deferred to avoid introducing unnecessary complexity during system validation.

The following enhancements are planned as **optional future extensions**.

---

## 1. Wi-Fi Data Streaming

The ESP32 provides built-in Wi-Fi capabilities that can be leveraged for wireless data transmission.

Planned improvements:
- HTTP/REST-based data streaming to a host PC or server
- MQTT-based telemetry for real-time dashboards
- Remote monitoring during high-temperature experiments

Benefits:
- Improved operator safety (remote logging during experiments)
- Reduced dependency on physical USB connections
- Support for long-duration unattended measurements

Wi-Fi is excluded from the current implementation to keep the data path deterministic during validation.

---

## 2. Dedicated External Power Supply

The system is currently powered via USB from the host PC, which is sufficient for development and testing.

Potential future enhancement:
- Dedicated low-noise 3.3 V linear regulator
- Separate measurement power domain for improved EMI resilience
- Improved stability in electrically noisy environments

An external power supply will be considered only if required by operating conditions or system scaling.

---

## 3. On-Device Data Logging

Future versions may support standalone operation without a host PC.

Possible additions:
- SD card–based CSV logging
- Timestamped data storage
- Configurable logging intervals

This would enable fully autonomous experiments in remote or constrained environments.

---

## 4. Advanced Fault Monitoring

The MAX31856 provides fault flags that can be expanded in future firmware revisions.

Enhancements may include:
- Continuous fault status logging
- Automatic detection of probe disconnection
- Fault tagging in recorded datasets

This would improve robustness during long experiments.

---

## 5. Time Synchronization and Metadata

Future improvements may introduce:
- Real-time clock (RTC) integration
- Absolute timestamping (date and time)
- Experiment metadata tagging (operator, sample ID, notes)

These additions would improve traceability and post-processing.

---

## 6. Visualization and Analysis Tools

Potential software-side improvements:
- Real-time plotting on the host PC
- Automated cooling/heating curve analysis
- Export to scientific data analysis environments (MATLAB, Python, R)

These tools would enhance data interpretation without modifying the core measurement hardware.

---

## Summary

All future improvements are intentionally deferred to maintain a clear focus on building a **correct and reliable multi-channel thermocouple measurement system**.

Each enhancement will be evaluated based on:
- Impact on measurement integrity
- Added system complexity
- Actual experimental requirements

This staged development approach ensures long-term maintainability and research validity.
