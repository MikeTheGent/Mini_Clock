
#include <ESP8266WiFi.h>
#include "WiFiConnection.h"

namespace WiFiConnection {
    namespace {
        wiFiStatus status = disconnected;
    }

    wiFiStatus begin(const char *ssid, const char *password) {
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);

        if (WiFi.status() == WL_CONNECTED) {
            status = connected;
        }

        return status;
    }

    wiFiStatus getStatus() {
        return status;
    }
}

