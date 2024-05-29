
#include <ESP8266WiFi.h>
#include "WiFiConnection.h"

namespace WiFiConnection {
    namespace {
        String ssid;
        String password;
    }

    wiFiStatus begin(const char *wiFiSsid, const char *wifiPassword) {
        wiFiStatus status = disconnected;
        ssid = wiFiSsid;
        password = wifiPassword;

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

    wiFiStatus reconnect() {
        return begin(ssid.c_str(), password.c_str());
    }

    wiFiStatus getStatus() {
        if (WiFi.status() == WL_CONNECTED) {
            return connected;
        }
        else {
            return disconnected;
        }
    }
}

