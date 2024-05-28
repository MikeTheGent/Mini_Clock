/*
** Alexa Control uses the fauxmoESP library to emulate a Phillips bulb. This can
** control the brightness of the clock displays and turn the displays off without
** turning off the GPS receiver. If Alexa control isn't required, this module &
** the WiFi Connection module can probably be removed -- I haven't tested this, but
** I believe it would be a trivial change.
**
** (C) 2024, Mike Wilson. MIT License -- see LICENSE file included in the distribution.
*/

#include <Arduino.h>
#include <fauxmoESP.h>
#include "AlexaControl.h"

namespace AlexaControl {
    namespace {
        fauxmoESP fauxmo;
        displayChangeCallback onDisplayChange = NULL;

        void alexaCallback(unsigned char deviceId, const char *deviceName,
                bool state, unsigned char value) {

            if (onDisplayChange != NULL)
                (onDisplayChange)(state, value);
        }
    }

    void begin(const char *deviceName, displayChangeCallback callback) {
        fauxmo.createServer(true);
        fauxmo.setPort(80);
        fauxmo.enable(true);
        fauxmo.addDevice(deviceName);
        fauxmo.onSetState(alexaCallback);
        onDisplayChange = callback;
    }

    void loop() {
        fauxmo.handle();
    }
}
