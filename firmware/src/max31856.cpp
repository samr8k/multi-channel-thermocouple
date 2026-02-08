#include "max31856.h"

/* MAX31856 register addresses (from datasheet) */
#define REG_CR0     0x00
#define REG_CR1     0x01
#define REG_SR      0x0F
#define REG_CJTH    0x0A
#define REG_CJTL    0x0B
#define REG_LTCBH   0x0C

/* Constructor */
MAX31856::MAX31856(uint8_t csPin, SPIClass &spi)
{
    _cs  = csPin;
    _spi = &spi;
}

/* Initialize the MAX31856 */
bool MAX31856::begin(TCType type)
{
    pinMode(_cs, OUTPUT);
    deselect();

    /*
     * CR0:
     *  - Auto conversion mode
     *  - Fault detection enabled
     */
    write8(REG_CR0, 0x80);

    /*
     * CR1:
     *  - Set thermocouple type
     */
    write8(REG_CR1, type & 0x07);

    clearFault();
    return true;
}

/* Read hot junction (thermocouple) temperature */
float MAX31856::readHotJunction()
{
    uint32_t raw = read24(REG_LTCBH);

    /* Sign extend 19-bit value */
    if (raw & 0x80000) {
        raw |= 0xFFF00000;
    }

    raw >>= 5;   // remove unused bits

    /* 1 LSB = 1/128 °C */
    return raw * 0.0078125f;
}

/* Read cold junction temperature */
float MAX31856::readColdJunction()
{
    uint16_t raw = (read8(REG_CJTH) << 8) | read8(REG_CJTL);

    /* 1 LSB = 1/64 °C */
    return (int16_t)raw * 0.015625f;
}

/* Check if any fault is present */
bool MAX31856::hasFault()
{
    uint8_t status = read8(REG_SR);
    return (status & 0xBF) != 0;   // any fault bit set
}

/* Clear fault flags */
void MAX31856::clearFault()
{
    write8(REG_CR0, 0x80);
}

/* -------- Low-level SPI helpers -------- */

uint8_t MAX31856::read8(uint8_t reg)
{
    select();
    _spi->transfer(reg & 0x7F);
    uint8_t val = _spi->transfer(0x00);
    deselect();
    return val;
}

uint32_t MAX31856::read24(uint8_t reg)
{
    select();
    _spi->transfer(reg & 0x7F);

    uint32_t v = 0;
    v |= _spi->transfer(0x00); v <<= 8;
    v |= _spi->transfer(0x00); v <<= 8;
    v |= _spi->transfer(0x00);

    deselect();
    return v;
}

void MAX31856::write8(uint8_t reg, uint8_t val)
{
    select();
    _spi->transfer(reg | 0x80);
    _spi->transfer(val);
    deselect();
}
