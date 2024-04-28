#include "PomodoroTimer.h"

PomodoroTimer timer = PomodoroTimer();

PomodoroTimer::PomodoroTimer() 
: counterDisplay(CENTER_DISPLAY_X_PX-36, CENTER_DISPLAY_Y_PX-29, 00, 2) {
    displayMutex = new std::mutex();
}

PomodoroTimer::~PomodoroTimer() {

}

void PomodoroTimer::init() {
    this->MagTag::begin();

    // peripherals.setCallbackBtnA(startTimer);
    // peripherals.setCallbackBtnB(acknowledgeAlarm);
    // peripherals.setCallbackBtnC(pauseTimer);
    // peripherals.setCallbackBtnD(cancelTimer);
    
    peripherals.enableNeoPixel();
    delay(5);
    peripherals.setNeoPixelFill(LED_OFF);
    delay(5);
    peripherals.disableNeoPixel();

    update();
}

void PomodoroTimer::update() {
    switch (state) {
        case INITIALIZATION:
            _timeRemaining = WORK_TIME_MINS;
            state = WORK_PAUSE;
            break;
        case WORK_PAUSE:
        case SHORT_BREAK_PAUSE:
        case LONG_BREAK_PAUSE:
            return; // Do not force a refresh if the timer is paused
        case WORK_RUNNING:
        case SHORT_BREAK_RUNNING:
        case LONG_BREAK_RUNNING:
            if (--_timeRemaining <= 0) { 
                if (state == WORK_RUNNING) { _numWorkPeriods++; }
                prevState = state; 
                state = ALARM; 
            } 
            break;
        default:
            break;
    }

    updateDisplay();

    while (state == ALARM) {
        peripherals.enableSpeaker();
        peripherals.playTone(1000, 1000);
        peripherals.enableNeoPixel();
        delay(5);
        peripherals.setNeoPixelFill(LED_OFF);
        delay(1000);
        peripherals.setNeoPixelFill(RED);
        delay(1000);
        // digitalWrite(LED_BUILTIN, HIGH);
        // delay(1000);
        // digitalWrite(LED_BUILTIN, LOW);
        // delay(1000);                
        continue;
    }
}

void PomodoroTimer::start() { 
    switch (state) {
    case WORK_PAUSE:
        prevState = state;
        state = WORK_RUNNING;
        break;
    case SHORT_BREAK_PAUSE:
        prevState = state;
        state = SHORT_BREAK_RUNNING;
        break;
    case LONG_BREAK_PAUSE:
        prevState = state;
        state = LONG_BREAK_RUNNING;
        break;
    default:
        return;
    }
    updateDisplay();
}

void PomodoroTimer::ack() {
    if (state == ALARM) {
        peripherals.disableNeoPixel();
        // peripherals.setNeoPixelBrightness(0.0);
        peripherals.disableSpeaker();
        switch (prevState) {
        case WORK_RUNNING:
            if (_numWorkPeriods < 4) {
                state = SHORT_BREAK_PAUSE;
                _timeRemaining = SHORT_BREAK_TIME_MINS;
            }
            else {
                state = LONG_BREAK_PAUSE;
                _numWorkPeriods = 0;
                _timeRemaining = LONG_BREAK_TIME_MINS;
            }
            break;
        case SHORT_BREAK_RUNNING:
        case LONG_BREAK_RUNNING:
            state = WORK_PAUSE;
            _timeRemaining = WORK_TIME_MINS;
            break;
        default:
            break;
        }
        prevState = ALARM;
        updateDisplay();
    }
}
void PomodoroTimer::pause() {
    switch (state) {
        case WORK_RUNNING:
            prevState = state;
            state = WORK_PAUSE;
            break;
        case SHORT_BREAK_RUNNING:
            prevState = state;
            state = SHORT_BREAK_PAUSE;
            break;
        case LONG_BREAK_RUNNING:
            prevState = state;
            state = LONG_BREAK_PAUSE;
        default:
            break;
    }
    updateDisplay();
}
void PomodoroTimer::cancel() {
    switch (state) {
        case WORK_RUNNING:
            prevState = state;
            state = WORK_PAUSE;
            _timeRemaining = WORK_TIME_MINS;
            break;
        case SHORT_BREAK_RUNNING:
            prevState = state;
            state = SHORT_BREAK_PAUSE;
            _timeRemaining = SHORT_BREAK_TIME_MINS;
            break;
        case LONG_BREAK_RUNNING:
            prevState = state;
            state = LONG_BREAK_PAUSE;
            _timeRemaining = LONG_BREAK_TIME_MINS;
        default:
            break;
    }
    // display.clearDisplay();
    updateDisplay();
}

void PomodoroTimer::renderWorkPeriods() {
    uint16_t posX = 240;
    uint16_t posY = 7;
    uint16_t radius = 4;
    uint16_t padding = 12;

    for (uint8_t i=0; i<MAX_NUM_WORK_PERIODS; i++) {
        if (i<_numWorkPeriods) {
            display.fillCircle(posX+radius + i*padding, posY+radius, radius, EPD_BLACK);
        }
        else {
            display.drawCircle(posX+radius + i*padding, posY+radius, radius, EPD_BLACK);
        }
    }
}

void PomodoroTimer::renderStateText() {
    const uint16_t FONT_SIZE = 1;
    const uint16_t WORK__POS_X = 105;
    const uint16_t SHORT_BREAK__POS_X = 68;
    const uint16_t LONG_BREAK__POS_X = 73;
    const uint16_t TEXT_POS_Y = 17;

    switch (state) {
        case WORK_PAUSE:
        case WORK_RUNNING:
            display.addText(WORK__POS_X, TEXT_POS_Y, &FreeSansBold9pt7b, FONT_SIZE, EPD_BLACK);
            display.print("WORK");
            break;
        case SHORT_BREAK_PAUSE:
        case SHORT_BREAK_RUNNING:
            display.addText(SHORT_BREAK__POS_X, TEXT_POS_Y, &FreeSansBold9pt7b, FONT_SIZE, EPD_BLACK);
            display.print("SHORT BREAK");
            break;
        case LONG_BREAK_PAUSE:
        case LONG_BREAK_RUNNING:
            display.addText(LONG_BREAK__POS_X, TEXT_POS_Y, &FreeSansBold9pt7b, FONT_SIZE, EPD_BLACK);
            display.print("LONG BREAK");
            break;
        default:
            break;
    }
}

void PomodoroTimer::renderLabelText() {
    const uint16_t LABEL_POS_Y = 120;

    display.addText(5, LABEL_POS_Y, &FreeSans9pt7b, 1, EPD_BLACK);
    display.print("START");

    display.addText(80, LABEL_POS_Y, &FreeSans9pt7b, 1, EPD_BLACK);
    display.print("ACK");

    if (state == WORK_PAUSE || state == SHORT_BREAK_PAUSE || state == LONG_BREAK_PAUSE) {
        display.fillRect(140, 105, 60, 20, EPD_BLACK);
        display.addText(140, LABEL_POS_Y, &FreeSans9pt7b, 1, EPD_WHITE);
    }
    else {
        display.addText(140, LABEL_POS_Y, &FreeSans9pt7b, 1, EPD_BLACK);
    }
    display.print("PAUSE");

    display.addText(210, LABEL_POS_Y, &FreeSans9pt7b, 1, EPD_BLACK);
    display.print("CANCEL");
}

void PomodoroTimer::updateDisplay() {
    displayMutex->lock(); // Block execution until display is released, then grab it
    display.clearBuffer();
    // display.clearDisplay();
    counterDisplay.setDigit(_timeRemaining);
    renderCounter();
    renderWorkPeriods();
    renderStateText();
    renderLabelText();
    display.display();
    displayMutex->unlock(); // Release display
}
