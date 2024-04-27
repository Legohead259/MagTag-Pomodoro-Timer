#ifndef POMODORO_TIMER_H
#define POMODORO_TIMER_H

#include <Arduino.h>
#include "MagTag.h"
#include "SevenSegmentWidget.h"

class PomodoroTimer : public MagTag {
public:
    PomodoroTimer();
    ~PomodoroTimer();

    void init();

    void renderCounter() { counterDisplay.render(&display); }
    void updateDisplay() { display.clearDisplay(); renderCounter(); display.display(); }
    void incrementCounter() { counter++; counterDisplay.setDigit(counter); }
    void decrementCounter() { counter--; counterDisplay.setDigit(counter); }
private:
    bool _isLedOn = false;
    int counter = 0;

    SevenSegmentWidget counterDisplay = SevenSegmentWidget(100, 32, counter);
};

extern PomodoroTimer timer;

static void startAlarm() {
    timer.peripherals.enableSpeaker();
}

static void stopAlarm() {
    timer.peripherals.disableSpeaker();
}

static void incrementCounter() {
    timer.incrementCounter();
    timer.updateDisplay();
}

#endif // POMODORO_TIMER_H