#ifndef MAX31856_H
#define MAX31856_H

#include <Arduino.h>
#include <SPI.h>

/*
 * MAX31856 Thermocouple Interface (SPI)
 *
 * Responsibilities:
 * - Configure thermocouple type
 * - Read hot junction temperature
 * - Read cold junction temperature
 * - Report basic fault status
 *
 * One object = one MAX31856 device (one thermocouple channel)
 */

class MAX31856 {
public:
    /* Supported thermocouple types */
    enum TCType {
        TYPE_B = 0,
        TYPE_E = 1,
        TYPE_J = 2,
        TYPE_K = 3,
        TYPE_N = 4,
        TYPE_R = 5,
        TYPE_S = 6,
        TYPE_T = 7
    };

    /* Constructor */
    MAX31856(uint8_t csPin, SPIClass &spi = SPI);

    /* Initialize device */
    bool begin(TCType type);

    /* Temperature readings */
    float readHotJunction();     // °C
    float readColdJunction();    // °C

    /* Fault handling */
    bool hasFault();
    void clearFault();

private:
    uint8_t   _cs;
    SPIClass* _spi;

    /* Low-level SPI helpers */
    uint8_t  read8(uint8_t reg);
    uint32_t read24(uint8_t reg);
    void     write8(uint8_t reg, uint8_t val);

    inline void select()   { digitalWrite(_cs, LOW); }
    inline void deselect() { digitalWrite(_cs, HIGH); }
};

#endif
