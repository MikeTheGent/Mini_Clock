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
#include <Espalexa.h>
#include "AlexaControl.h"

namespace AlexaControl {
    namespace {
        Espalexa alexa;
        displayChangeCallback onDisplayChange = NULL;

        void alexaCallback(EspalexaDevice* device) {
            if (onDisplayChange != NULL)
                (onDisplayChange)(device->getState());
        }
    }

    void begin(const char *deviceName, displayChangeCallback callback) {
        alexa.addDevice(deviceName, alexaCallback, EspalexaDeviceType::onoff);
        alexa.begin();        
        onDisplayChange = callback;
    }

    void loop() {
        alexa.loop();
    }
}
