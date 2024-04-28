#include <Arduino.h>
#include "PomodoroTimer.h"

TickType_t xLastWakeTime;
const TickType_t xFrequency = MINS_TO_MS; //delay for mS

static void startTimer() { timer.start(); }   
static void acknowledgeAlarm() { timer.ack(); }
static void pauseTimer() { timer.pause(); }
static void cancelTimer() { timer.cancel(); }

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    timer.init();

    attachInterrupt(BUTTON_A, startTimer, FALLING);
    attachInterrupt(BUTTON_B, acknowledgeAlarm, FALLING);
    attachInterrupt(BUTTON_C, pauseTimer, FALLING);
    attachInterrupt(BUTTON_D, cancelTimer, FALLING);
}

// the loop function runs over and over again forever
void loop() {
    timer.update();
    delay(xFrequency);
}
