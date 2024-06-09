
#pragma once

namespace ClockDisplay {
    void begin(void);
    void displayTime(uint8_t hour, uint8_t minute);
    void adjustBrightness(long brightness);
    void switchDisplay(bool state);
    void displayError(int errorCode);
}
