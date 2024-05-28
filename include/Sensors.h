
#pragma once

namespace Sensors {
    bool begin(void);
    void update(void);
    float getTemperature(void);
    float getHumidity(void);
    float getPressure();
    long getBrightness(void);
}
