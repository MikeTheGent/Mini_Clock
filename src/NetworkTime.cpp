
#include <Arduino.h>
#include "NetworkTime.h"
#include "Settings.h"

namespace NetworkTime {
    namespace {
        const char *ntpServer = NULL;
        RTC_DS3231 rtc;
        bool rtcPresent = false;

    }

    bool begin() {
        ntpServer = Settings::get("NTP_Server");
        configTime(0, 0, ntpServer);
        setenv("TZ", Settings::get("TZ"), 1);

        if (rtc.begin()) {
            synchronise();
        }

        return rtcPresent;
    }

    DateTime now() {
        if (rtcPresent) {
            return rtc.now();
        }
        else {
            return DateTime();
        }
    }

    void synchronise() {
        struct tm timeinfo;
        getLocalTime(&timeinfo);
        DateTime now(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, 
                timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        rtc.adjust(now);
    }
}

