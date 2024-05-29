/*
** Clock display -- probably sometime big enough to be seen across a typical 
** living room. Originally designed to use a 4x7 segment display driven by a HT16K33.
**
** (C) 2024, Mike Wilson. MIT License -- see LICENSE file included in the distribution.
*/

#include <Arduino.h>
#include <HT16K33.h>
#include "ClockDisplay.h"

namespace ClockDisplay {
    namespace {
        HT16K33 display(0x70);
    }

    void begin() {
        display.begin();
        switchDisplay(true);
        display.setBlink(3);
        display.displayTime(99, 99);
        display.brightness(32);
    }

    void displayTime(const struct tm *clockTime) {
        displayTime(clockTime->tm_hour, clockTime->tm_min);
    }

    void displayTime(uint8_t hour, uint8_t minute) {
        display.displayTime(hour, minute);
        display.setBlink(0);
    }

    void switchDisplay(bool state) {
        if (state) {
            display.displayOn();
        }
        else {
            display.displayOff();
        }
    }

    void displayError(int errorCode) {
        display.setBlink(3);
        display.displayTime(errorCode * 11, errorCode * 11);
    }
}
