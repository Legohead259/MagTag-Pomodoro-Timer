#ifndef POMODORO_TIMER_H
#define POMODORO_TIMER_H

#include <Arduino.h>
#include "MagTag.h"
#include "SevenSegmentWidget.h"
#include <mutex>

#define MINS_TO_MS              60e3
#define WORK_TIME_MINS          5
#define SHORT_BREAK_TIME_MINS   2
#define LONG_BREAK_TIME_MINS    2
#define WORK_TIME_MS            WORK_TIME_MINS*MINS_TO_MS
#define SHORT_BREAK_TIME_MS     SHORT_BREAK_TIME_MINS*MINS_TO_MS
#define LONG_BREAK_TIME_MS      LONG_BREAK_TIME_MINS*MINS_TO_MS
#define MAX_NUM_WORK_PERIODS    4

enum TimerStates_t {
    INITIALIZATION,
    WORK_PAUSE,
    WORK_RUNNING,
    SHORT_BREAK_PAUSE,
    SHORT_BREAK_RUNNING,
    LONG_BREAK_PAUSE,
    LONG_BREAK_RUNNING,
    ALARM
};

class PomodoroTimer : public MagTag {
public:
    PomodoroTimer();
    ~PomodoroTimer();

    void init();
    void update();

    void start();
    void ack();
    void pause();
    void cancel();

    void renderCounter() { counterDisplay.render(&display); }
    void renderWorkPeriods();
    void renderStateText();
    void renderLabelText();
    void updateDisplay();
private:
    bool _isLedOn = false;
    uint8_t _timeRemaining = 0;
    uint8_t _numWorkPeriods = 0;
    std::mutex* displayMutex;

    SevenSegmentWidget counterDisplay;
    TimerStates_t prevState = INITIALIZATION;
    TimerStates_t state = INITIALIZATION;
};

extern PomodoroTimer timer;

#endif // POMODORO_TIMER_H