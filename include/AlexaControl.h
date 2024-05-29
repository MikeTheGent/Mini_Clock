
#pragma once

namespace AlexaControl {
    typedef void (*displayChangeCallback)(bool);
    void begin(const char *deviceName, displayChangeCallback callback);
    void loop(void);
}

