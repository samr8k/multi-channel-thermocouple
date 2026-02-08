#ifndef CHANNEL_MANAGER_H
#define CHANNEL_MANAGER_H

#include <Arduino.h>
#include "max31856.h"

/*
 * ChannelManager
 *
 * Responsibilities:
 * - Manage multiple MAX31856 thermocouple channels
 * - Enable / disable channels
 * - Read temperatures from all enabled channels
 * - Store latest readings in a structured form
 *
 * This class does NOT:
 * - Access SPI registers directly
 * - Print data
 * - Handle logging, Wi-Fi, or timing
 */

class ChannelManager {
public:
    /* Maximum supported channels */
    static const uint8_t MAX_CHANNELS = 8;

    /* Data structure for one channel */
    struct ChannelData {
        bool  enabled;     // Is this channel active?
        float hotTemp;     // Hot junction temperature (°C)
        float coldTemp;    // Cold junction temperature (°C)
        bool  fault;       // Fault detected?
    };

    /* Constructor */
    ChannelManager();

    /* Register a thermocouple channel */
    bool addChannel(MAX31856* sensor, bool enable = true);

    /* Enable or disable a channel */
    void enableChannel(uint8_t index, bool enable);

    /* Read all enabled channels */
    void readAll();

    /* Get data for one channel */
    ChannelData getChannel(uint8_t index) const;

    /* Number of registered channels */
    uint8_t channelCount() const;

private:
    MAX31856*  _channels[MAX_CHANNELS];
    ChannelData _data[MAX_CHANNELS];
    uint8_t     _count;
};

#endif
