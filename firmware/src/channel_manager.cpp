#include "channel_manager.h"

/* Constructor */
ChannelManager::ChannelManager()
{
    _count = 0;

    for (uint8_t i = 0; i < MAX_CHANNELS; i++) {
        _channels[i] = nullptr;
        _data[i].enabled  = false;
        _data[i].hotTemp  = 0.0f;
        _data[i].coldTemp = 0.0f;
        _data[i].fault    = false;
    }
}

/* Register a new thermocouple channel */
bool ChannelManager::addChannel(MAX31856* sensor, bool enable)
{
    if (_count >= MAX_CHANNELS || sensor == nullptr) {
        return false;
    }

    _channels[_count]      = sensor;
    _data[_count].enabled = enable;
    _data[_count].hotTemp = 0.0f;
    _data[_count].coldTemp = 0.0f;
    _data[_count].fault   = false;

    _count++;
    return true;
}

/* Enable or disable a channel */
void ChannelManager::enableChannel(uint8_t index, bool enable)
{
    if (index >= _count) return;
    _data[index].enabled = enable;
}

/* Read all enabled channels */
void ChannelManager::readAll()
{
    for (uint8_t i = 0; i < _count; i++) {

        if (!_data[i].enabled || _channels[i] == nullptr)
            continue;

        _data[i].hotTemp  = _channels[i]->readHotJunction();
        _data[i].coldTemp = _channels[i]->readColdJunction();
        _data[i].fault    = _channels[i]->hasFault();
    }
}

/* Get channel data */
ChannelManager::ChannelData ChannelManager::getChannel(uint8_t index) const
{
    if (index >= _count) {
        ChannelData empty;
        empty.enabled  = false;
        empty.hotTemp  = 0.0f;
        empty.coldTemp = 0.0f;
        empty.fault    = true;
        return empty;
    }

    return _data[index];
}

/* Return number of registered channels */
uint8_t ChannelManager::channelCount() const
{
    return _count;
}
