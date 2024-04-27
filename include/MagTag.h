#ifndef MAGTAG_H
#define MAGTAG_H

#include "MagTag_Display.h"
#include "MagTag_Peripherals.h"

class MagTag {
public:
    MagTag(/* args */);
    ~MagTag();

    void begin();

    MagTag_Peripherals peripherals = MagTag_Peripherals();
    MagTag_Display display = MagTag_Display();

private:
    
};

extern MagTag magTag;

static void buttonAISR() { magTag.peripherals.handleButtonA(); }
static void buttonBISR() { magTag.peripherals.handleButtonB(); }
static void buttonCISR() { magTag.peripherals.handleButtonC(); }
static void buttonDISR() { magTag.peripherals.handleButtonD(); }

#endif // MAGTAG_H