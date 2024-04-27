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

void PomodoroTimer::updateDisplay() {
    
}

// void PomodoroTimer::