#include "PomodoroTimer.h"

PomodoroTimer timer = PomodoroTimer();

PomodoroTimer::PomodoroTimer() 
: counterDisplay(CENTER_DISPLAY_X_PX-36, CENTER_DISPLAY_Y_PX-29, 00, 2) {

}

PomodoroTimer::~PomodoroTimer() {

}

void PomodoroTimer::init() {
    this->MagTag::begin();

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

void PomodoroTimer::renderStateText(const char* stateStr) {

}

void PomodoroTimer::updateDisplay() {
    display.clearDisplay();
    renderCounter();
    renderWorkPeriods();
    display.display();
}

// void PomodoroTimer::