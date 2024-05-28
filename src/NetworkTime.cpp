
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

        if (rtc.begin()) {
            struct tm timeinfo;
            getLocalTime(&timeinfo);
            Serial.printf("Timeinfo %s\n", asctime(&timeinfo));
            DateTime now(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, 
                    timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
            rtc.adjust(now);
            Serial.printf("Adjust %s\n", now.timestamp().c_str());
            Serial.printf("Adjusted %s\n", rtc.now().timestamp().c_str());
        }
        else {
            Serial.println("No RTC");
        }
    }

    DateTime now() {
        return rtc.now();
    }
}

