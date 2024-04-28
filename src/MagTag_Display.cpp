#include "MagTag_Display.h"

MagTag_Display::~MagTag_Display() {
}

void MagTag_Display::begin() {
    this->ThinkInk_290_Grayscale4_T5::begin(THINKINK_GRAYSCALE4);
    pinMode(EPD_BUSY, INPUT);
}

void MagTag_Display::addText(int16_t x, int16_t y, const GFXfont* font, uint8_t size, uint16_t color) {
    setCursor(x, y);
    setFont(font);
    setTextSize(size);
    setTextColor(color);
}