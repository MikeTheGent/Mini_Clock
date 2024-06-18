
#pragma once 

namespace EnvironmentDisplay {
    void begin();
    void displayTemperature(float temperature);
    void displayHumidity(long humidity);
    void displayPressure(float pressure);
    void displayMessage(const char *message);
    void switchDisplay(bool state);
    void adjustBrightness(long brightness);
}
