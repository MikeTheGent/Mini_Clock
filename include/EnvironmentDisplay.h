
#pragma once 

namespace EnvironmentDisplay {
    void begin();
    void displayTemperature(float temperature);
    void displayHumidity(long humidity);
    void displayBrightness(long light);
    void displayMessage(const char *message);
    void clearMessage(void);
    void switchDisplay(bool state);
}
