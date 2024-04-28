#include "MagTag_Peripherals.h"

MagTag_Peripherals::MagTag_Peripherals() {
}

void MagTag_Peripherals::begin() {
    // NeoPixel Startup
    pinMode(NEOPIXEL_POWER, OUTPUT);
    _strip.begin();
    disableNeoPixel();

    // Battery monitor
    pinMode(BATT_MONITOR, INPUT);

    // Speaker
    pinMode(SPEAKER_SHUTDOWN, OUTPUT);
    disableSpeaker();

    // Light sensor
    pinMode(LIGHT_SENSOR, INPUT);

    // Buttons
    for (uint8_t i=0; i<4; i++) {
        pinMode(_buttonPins[i], INPUT_PULLUP);
    }
}

MagTag_Peripherals::~MagTag_Peripherals() {
}

void MagTag_Peripherals::playTone(unsigned int frequency, unsigned long duration) {
    if (!_isSpeakerEnabled) return;
    tone(A0, frequency, duration);
}

void MagTag_Peripherals::setNeoPixelBrightness(double percent) {
    _strip.setBrightness((uint8_t) percent*255);
    _strip.show();
}

void MagTag_Peripherals::setNeoPixelFill(uint32_t color) {
    _strip.fill(color);
    _strip.show();
}