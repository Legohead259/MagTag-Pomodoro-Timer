#ifndef POMODORO_TIMER_H
#define POMODORO_TIMER_H

#include <Arduino.h>
#include "MagTag.h"
#include "SevenSegmentWidget.h"

#define MAX_NUM_WORK_PERIODS 4

class PomodoroTimer : public MagTag {
public:
    PomodoroTimer();
    ~PomodoroTimer();

    void init();

    void renderCounter() { counterDisplay.render(&display); }
    void renderWorkPeriods();
    void renderStateText(const char* stateStr);
    void updateDisplay();
private:
    bool _isLedOn = false;
    uint8_t _timeRemaining = 0;
    uint8_t _numWorkPeriods = 0;

    SevenSegmentWidget counterDisplay;
};

extern PomodoroTimer timer;

#endif // POMODORO_TIMER_H