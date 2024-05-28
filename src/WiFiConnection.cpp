
#include <ESP8266WiFi.h>
#include "WiFiConnection.h"

namespace WiFiConnection {
    namespace {
        wiFiStatus status = disconnected;
    }

    wiFiStatus begin(const char *ssid, const char *password) {
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        int waits = 0;

        while (WiFi.status() != WL_CONNECTED && waits < 40) {
            delay(500);
            waits++;
        }

        if (WiFi.status() == WL_CONNECTED) {
            status = connected;
        }

        return status;
    }

    wiFiStatus getStatus() {
        return status;
    }
}

