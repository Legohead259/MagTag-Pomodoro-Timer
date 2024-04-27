#include "PomodoroTimer.h"

PomodoroTimer timer = PomodoroTimer();

PomodoroTimer::PomodoroTimer() {

}

PomodoroTimer::~PomodoroTimer() {

}

void PomodoroTimer::init() {
    this->MagTag::begin();

    peripherals.setCallbackBtnB(startAlarm);
    peripherals.setCallbackBtnC(stopAlarm);
}