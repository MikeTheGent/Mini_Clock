
#pragma once

namespace WiFiConnection {
    typedef enum {
        connected = 0,
        disconnected
    } wiFiStatus;

    wiFiStatus begin(const char *ssid, const char *password);
    wiFiStatus reconnect(void);
    wiFiStatus getStatus(void);
}

