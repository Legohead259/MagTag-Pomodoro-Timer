#include "MagTag.h"

MagTag magTag = MagTag();

MagTag::MagTag(/* args */) {
    
}

MagTag::~MagTag() {

}

void MagTag::begin() {
    // Initialize peripherals
    peripherals.begin();
    display.begin();

    // Button interrupt handling
    attachInterrupt(BUTTON_A, buttonAISR, FALLING);
    attachInterrupt(BUTTON_B, buttonBISR, FALLING);
    attachInterrupt(BUTTON_C, buttonCISR, FALLING);
    attachInterrupt(BUTTON_D, buttonDISR, FALLING);
}