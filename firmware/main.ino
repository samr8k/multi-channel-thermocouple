#include <Arduino.h>
#include <SPI.h>

#include "max31856.h"
#include "channel_manager.h"

/* ========== USER CONFIG ========== */
#define TC1_CS  5
#define TC2_CS  17
#define TC3_CS  16

#define SAMPLE_INTERVAL_MS 1000
/* ================================= */

MAX31856 tc1(TC1_CS);
MAX31856 tc2(TC2_CS);
MAX31856 tc3(TC3_CS);

ChannelManager manager;
unsigned long lastSampleTime = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);

    SPI.begin();

    tc1.begin(MAX31856::TYPE_K);
    tc2.begin(MAX31856::TYPE_K);
    tc3.begin(MAX31856::TYPE_K);

    manager.addChannel(&tc1, true);
    manager.addChannel(&tc2, true);
    manager.addChannel(&tc3, true);

    /* CSV header */
    Serial.println("time_ms,TC0_C,TC1_C,TC2_C");
}

void loop() {
    unsigned long now = millis();

    if (now - lastSampleTime >= SAMPLE_INTERVAL_MS) {
        lastSampleTime = now;

        manager.readAll();

        Serial.print(now);

        for (uint8_t i = 0; i < manager.channelCount(); i++) {
            auto ch = manager.getChannel(i);

            Serial.print(",");
            Serial.print(ch.hotTemp, 2);   // REAL temperature
        }

        Serial.println();
    }
}
