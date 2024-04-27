#ifndef MAGTAG_PERIPHERALS_H
#define MAGTAG_PERIPHERALS_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

typedef std::function<void()> ButtonCallback;

class MagTag_Peripherals {
public:
    MagTag_Peripherals();

    ~MagTag_Peripherals();

    void begin();

    void playTone(unsigned int frequency, unsigned long duration);

    void enableSpeaker() { 
        _isSpeakerEnabled = true;
        digitalWrite(SPEAKER_SHUTDOWN, HIGH); 
    }
    void disableSpeaker() { 
        _isSpeakerEnabled = false;
        digitalWrite(SPEAKER_SHUTDOWN, LOW); 
    }

    void handleButtonA() { if (_callbackBtnA != nullptr) _callbackBtnA(); }
    void handleButtonB() { if (_callbackBtnB != nullptr) _callbackBtnB(); }
    void handleButtonC() { if (_callbackBtnC != nullptr) _callbackBtnC(); }
    void handleButtonD() { if (_callbackBtnD != nullptr) _callbackBtnD(); }
    
    void setNeoPixelBrightness(double percent);
    void setCallbackBtnA(ButtonCallback cbBtnPtr) { _callbackBtnA = cbBtnPtr; }
    void setCallbackBtnB(ButtonCallback cbBtnPtr) { _callbackBtnB = cbBtnPtr; }
    void setCallbackBtnC(ButtonCallback cbBtnPtr) { _callbackBtnC = cbBtnPtr; }
    void setCallbackBtnD(ButtonCallback cbBtnPtr) { _callbackBtnD = cbBtnPtr; }

private:
    Adafruit_NeoPixel _strip = Adafruit_NeoPixel(NEOPIXEL_NUM, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
    const uint8_t _buttonPins[4] = {BUTTON_A, BUTTON_B, BUTTON_C, BUTTON_D};
    bool _isSpeakerEnabled = false;
    ButtonCallback _callbackBtnA = nullptr;
    ButtonCallback _callbackBtnB = nullptr;
    ButtonCallback _callbackBtnC = nullptr;
    ButtonCallback _callbackBtnD = nullptr;
};

#endif // MAGTAG_PERIPHERALS_H