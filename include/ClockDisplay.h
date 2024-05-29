
#pragma once

namespace ClockDisplay {
    void begin(void);
    void displayTime(const struct tm *clockTime);
    void displayTime(uint8_t hour, uint8_t minute);
    void adjustBrightness(short brightness);
    void switchDisplay(bool state);
    void displayError(int errorCode);
}
