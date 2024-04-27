#ifndef MAGTAG_DISPLAY_H
#define MAGTAG_DISPLAY_H

#include <Arduino.h>
#include <Adafruit_ThinkInk.h>

class MagTag_Display : public ThinkInk_290_Grayscale4_T5 {
public:
    MagTag_Display() : ThinkInk_290_Grayscale4_T5(EPD_DC, EPD_RESET, EPD_CS, -1, -1) {}
    ~MagTag_Display();

    void begin();

    void addText(int16_t x, int16_t y, const GFXfont* font, uint8_t size, uint16_t color);
private:

};


#endif // MAGTAG_DISPLAY_H