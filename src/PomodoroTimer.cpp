#include "PomodoroTimer.h"

PomodoroTimer timer = PomodoroTimer();

PomodoroTimer::PomodoroTimer() 
: counterDisplay(100, 32, 0) {

}

PomodoroTimer::~PomodoroTimer() {

}

void PomodoroTimer::init() {
    this->MagTag::begin();

}

// void PomodoroTimer::