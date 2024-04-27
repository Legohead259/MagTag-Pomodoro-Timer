#include "SevenSegmentWidget.h"

SevenSegmentDigit::SevenSegmentDigit(uint16_t posX, uint16_t posY, uint8_t digit, uint16_t color, float anchorX, float anchorY) {
    _construct(posX, posY, digit, color, anchorX, anchorY);
}

SevenSegmentDigit::SevenSegmentDigit(uint16_t posX, uint16_t posY, uint8_t digit, SegmentType* segmentOptions, uint16_t color, float anchorX, float anchorY) {
    _segmentOptions = *segmentOptions;
    _construct(posX, posY, digit, color, anchorX, anchorY);
}

SevenSegmentDigit::~SevenSegmentDigit() {}

void SevenSegmentDigit::_construct(uint16_t posX, uint16_t posY, uint8_t digit, uint16_t color, float anchorX, float anchorY) {
    _posX = posX;
    _posY = posY;
    _digit = digit;
    _color = color;
    _anchorX = anchorX;
    _anchorY = anchorY;
}

// RENDER DIGITS:
// use this funtion to print digits
// valid range range: 0-999
// void SevenSegmentDigit::render_digits(uint16_t pos_x, uint16_t pos_y, uint16_t digits, uint16_t color) {
//     uint16_t spacing_x = DIGIT_SPACING_DEFAULT;

//     uint8_t digit_array[] = {digits / 100 % 10, digits / 10 % 10, digits % 10};
//     if (digits > 99) {
//         render_digit(pos_x, pos_y, digit_array[0], color);
//     }
//     if (digits > 9) {
//         render_digit(pos_x + spacing_x, pos_y, digit_array[1], color);
//     }
//     render_digit(pos_x + (spacing_x * 2), pos_y, digit_array[2], color);
// }

// RENDER DIGIT
// don't use this unless you only need a single digit
// use render_digits() func above instead

#ifdef ARDUINO_MAGTAG29_ESP32S2
void SevenSegmentDigit::render(ThinkInk_290_Grayscale4_T5* display) {       
    uint16_t w = _segmentOptions.width;
    uint16_t h = _segmentOptions.height;
    uint16_t r = _segmentOptions.radius;
    uint16_t p = _segmentOptions.padding;

    // loop through 7 segments
    for (uint8_t i = 0; i < 7; i++) {
        bool seg_on = DIGIT_TRUTH_TABLE[_digit][i];
        // if seg_on is true draw segment
        if (seg_on) {
        switch (i) {
            case 0:
                display->fillRoundRect(r+2*p+_posX, 0+_posY, w, h, r, _color); // SEG a
                break;
            case 1:
                display->fillRoundRect(w+r+p+_posX, r+p+_posY, h, w, r, _color); // SEG b
                break;
            case 2:
                display->fillRoundRect(w+r+p+_posX, w+r+2*p+_posY, h, w, r, _color); // SEG c
                break;
            case 3:
                display->fillRoundRect(r+2*p+_posX, 2*w+3*p+_posY, w, h, r, _color); // SEG d
                break;
            case 4:
                display->fillRoundRect(0+_posX, w+r+2*p+_posY, h, w, r, _color); // SEG e
                break;
            case 5:
                display->fillRoundRect(0+_posX, r+p+_posY, h, w, r, _color); // SEG f
                break;
            case 6:
                display->fillRoundRect(r+p+_posX, w+2*p+_posY, w, h, r, _color); // SEG g
                break;
        }
        seg_on = false;
        }
    }
}
#endif // #ARDUINO_MAGTAG29_ESP32S2


SevenSegmentWidget::SevenSegmentWidget(uint16_t posX, uint16_t posY, uint16_t digit, uint8_t placesOverride, uint16_t color, float anchorX, float anchorY) {
    _construct(posX, posY, digit, placesOverride, color, anchorX, anchorY);
}

SevenSegmentWidget::~SevenSegmentWidget() {}

void SevenSegmentWidget::_construct(uint16_t posX, uint16_t posY, uint16_t digit, uint8_t placesOverride, uint16_t color, float anchorX, float anchorY) {
    _posX = posX;
    _posY = posY;
    _placesOverride = placesOverride;
    _color = color;
    _anchorX = anchorX;
    _anchorY = anchorY;

    setDigit(digit);
}

void SevenSegmentWidget::formDigitArray() {
    uint16_t _digitTemp = _digit;
    uint8_t _counter = MAX_DIGITS;

    // Break into digits
    // Calculate the total number of digits in the number
    while (_digitTemp > 0) {
        _digitTemp /= 10;
        ++_order;
    }

    if (_digit == 0) { // Apply fix for if digit is 0
        _order++;
    }

    if (_order < _placesOverride) { // Check for adding additional places
        _order = +_placesOverride;
    }

    _digitTemp = _digit;
    // Extract digits from the number and store them in the array
    for (int i=_order-1; i>=0; --i) {
        _digits[i] = SevenSegmentDigit(_posX+i*DIGIT_SPACING_DEFAULT, _posY, _digitTemp % 10, _color);
        _digitTemp /= 10;
    }
}

#ifdef ARDUINO_MAGTAG29_ESP32S2
void SevenSegmentWidget::render(ThinkInk_290_Grayscale4_T5* display) {
    for (uint8_t i=0; i<_order; i++) {
        _digits[i].render(display);
    }
}
#endif // #ARDUINO_MAGTAG29_ESP32S2