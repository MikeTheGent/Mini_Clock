
#include <Arduino.h>
#include "NetworkTime.h"
#include "Settings.h"

namespace NetworkTime {
    namespace {
        //long gmtOffsetSeconds = 0;
        //long daylightOffsetSeconds = 0;
        const char *ntpServer = NULL;
        RTC_DS3231 rtc;
    }

    void begin() {
        //configTime(gmtOffsetSeconds, daylightOffsetSeconds, ntpServer);
        ntpServer = Settings::get("NTP_Server");
        configTime(0, 0, ntpServer);
        setenv("TZ", Settings::get("TZ"), 1);
        rtc.begin();
    }

    DateTime now() {
        return rtc.now();
    }
}

