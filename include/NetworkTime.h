
#pragma once
#include <RTClib.h>

namespace NetworkTime {
    bool begin(void);
    DateTime now(void);
    void synchronise(void);
}

