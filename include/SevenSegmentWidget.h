#ifndef SEVEN_SEGMENT_WIDGET_H
#define SEVEN_SEGMENT_WIDGET_H

#ifdef ARDUINO_MAGTAG29_ESP32S2
#include <Adafruit_ThinkInk.h>
#endif

#include <algorithm>

#define SEGMENT_W_DEFAULT 24
#define SEGMENT_H_DEFAULT 6
#define SEGMENT_R_DEFAULT SEGMENT_H_DEFAULT/2
#define SEGMENT_P_DEFAULT SEGMENT_R_DEFAULT/2 
#define DIGIT_SPACING_DEFAULT 40 // TODO: Make dependent on SEGMENT_W
#define MAX_DIGITS 5

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

enum SegmentOrientation {
    HORIZONTAL,
    VERTICAL
};

typedef struct {
    uint16_t width = SEGMENT_W_DEFAULT;
    uint16_t height = SEGMENT_H_DEFAULT;
    uint16_t radius = SEGMENT_R_DEFAULT;
    uint16_t padding = SEGMENT_P_DEFAULT;
    SegmentOrientation orientation = HORIZONTAL;
} SegmentType;

static const uint8_t DIGIT_TRUTH_TABLE[10][7] = {
    // A, B, C, D, E, F, G
    {1, 1, 1, 1, 1, 1, 0},  // 0
    {0, 1, 1, 0, 0, 0, 0},  // 1
    {1, 1, 0, 1, 1, 0, 1},  // 2
    {1, 1, 1, 1, 0, 0, 1},  // 3
    {0, 1, 1, 0, 0, 1, 1},  // 4
    {1, 0, 1, 1, 0, 1, 1},  // 5
    {1, 0, 1, 1, 1, 1, 1},  // 6
    {1, 1, 1, 0, 0, 0, 0},  // 7
    {1, 1, 1, 1, 1, 1, 1},  // 8
    {1, 1, 1, 0, 0, 1, 1}   // 9
};

class SevenSegmentDigit {
public:
    SevenSegmentDigit() {}
    SevenSegmentDigit(uint16_t posX, uint16_t posY, uint8_t digit, uint16_t color=EPD_BLACK, float anchorX=0.0, float anchorY=0.0);
    SevenSegmentDigit(uint16_t posX, uint16_t posY, uint8_t digit, SegmentType* segmentOptions, uint16_t color=EPD_BLACK, float anchorX=0.0, float anchorY=0.0);
    ~SevenSegmentDigit();

    #ifdef ARDUINO_MAGTAG29_ESP32S2
    void render(ThinkInk_290_Grayscale4_T5* display);
    #endif // ARDUINO_MAGTAG29_ESP32S2

private:
    uint16_t _posX;
    uint16_t _posY;
    uint8_t _digit;
    uint16_t _color;
    uint16_t _width;
    uint16_t _height;
    float _anchorX;
    float _anchorY;
    SegmentType _segmentOptions = SegmentType();

    void _construct(uint16_t posX, uint16_t posY, uint8_t digit, uint16_t color=EPD_BLACK, float anchorX=0.0, float anchorY=0.0);
};

class SevenSegmentWidget {
public:
    SevenSegmentWidget(uint16_t posX, uint16_t posY, uint16_t digit, uint16_t color=EPD_BLACK, float anchorX=0.0, float anchorY=0.0);
    ~SevenSegmentWidget();

    #ifdef ARDUINO_MAGTAG29_ESP32S2
    void render(ThinkInk_290_Grayscale4_T5* display);
    #endif // ARDUINO_MAGTAG29_ESP32S2

    void setDigit(uint16_t digit) { _digit = digit; formDigitArray(); }

private:
    uint16_t _posX;
    uint16_t _posY;
    uint16_t _digit;
    uint16_t _color;
    float _anchorX;
    float _anchorY;
    uint8_t _order = 0;
    SevenSegmentDigit _digits[MAX_DIGITS];

    void formDigitArray();
    void _construct(uint16_t posX, uint16_t posY, uint16_t digit, uint16_t color=EPD_BLACK, float anchorX=0.0, float anchorY=0.0);
};

#endif // SEVEN_SEGMENT_WIDGET_H