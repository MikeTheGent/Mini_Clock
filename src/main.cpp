
#include <Arduino.h>
#include <LittleFS.h>
#include <Wire.h>
#include "Settings.h"
#include "EnvironmentDisplay.h"
#include "ClockDisplay.h"
#include "Sensors.h"

void setup() {
    Serial.begin(115200);
    Wire.begin();
    EnvironmentDisplay::begin();
    ClockDisplay::begin();
    Sensors::begin();

    /*
    for (int i = 0 ; i < 5 ; i++) {
        delay(1000);
        Serial.printf("Sleep %d\n", i + 1);
    }
    */

    if (LittleFS.begin()) {
        switch (Settings::begin()) {
            case Settings::ok:
                EnvironmentDisplay::displayMessage(Settings::get("WiFi_SSID"));
                break;

            case Settings::oversizeFile:
                EnvironmentDisplay::displayMessage("Settings too big");
                break;

            case Settings::fileNotFound:
                EnvironmentDisplay::displayMessage("No settings file");
                break;

            default:
                break;
        }
    }
}

void loop() {
    Sensors::update();
    Serial.printf("Temperature %.1f\n", Sensors::getTemperature());
    Serial.printf("Humidity    %.0f\n", Sensors::getHumidity());
    Serial.printf("Pressure    %.0f\n", Sensors::getPressure());
    Serial.printf("Brightness  %ld\n", Sensors::getBrightness());
    delay(3000);
}

