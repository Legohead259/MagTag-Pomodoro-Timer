#ifndef MAGTAG_DISPLAY_H
#define MAGTAG_DISPLAY_H

#include <Arduino.h>
#include <Adafruit_ThinkInk.h>

#define DISPLAY_WIDTH_PX 296
#define DISPLAY_HEIGHT_PX 128
#define CENTER_DISPLAY_X_OFFSET_PX -13
#define CENTER_DISPLAY_X_PX DISPLAY_WIDTH_PX/2 + CENTER_DISPLAY_X_OFFSET_PX
#define CENTER_DISPLAY_Y_PX DISPLAY_HEIGHT_PX/2

class MagTag_Display : public ThinkInk_290_Grayscale4_T5 {
public:
    MagTag_Display() : ThinkInk_290_Grayscale4_T5(EPD_DC, EPD_RESET, EPD_CS, -1, -1) {}
    ~MagTag_Display();

    void begin();

    void addText(int16_t x, int16_t y, const GFXfont* font, uint8_t size, uint16_t color);
private:

};


#endif // MAGTAG_DISPLAY_H