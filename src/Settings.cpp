
#include <ArduinoJson.h>
#include <LittleFS.h>
#include "Settings.h"

namespace Settings {
    namespace {
        JsonDocument doc;
    }

    settingStatus begin() {
        settingStatus status = ok;
        File settingsFile = LittleFS.open("settings.json", "r");

        if (settingsFile) {
            if (settingsFile.size() <= 1024) {
                String json = settingsFile.readString();
                deserializeJson(doc, json);
            }
            else {
                status = oversizeFile;
            }

            settingsFile.close();
        }
        else {
            status = fileNotFound;
        }

        return status;
    }

    const char *get(const char *id) {
        return doc[id];
    }
}
