
#include <Arduino.h>
#include <LittleFS.h>
#include <Wire.h>
#include "Settings.h"
#include "WiFiConnection.h"
#include "AlexaControl.h"
#include "EnvironmentDisplay.h"
#include "ClockDisplay.h"
#include "Sensors.h"

static void connectWiFi(void);
static void openSettings();
static void onDisplayChange(bool, unsigned char value);
static void updateEnvironment(void);

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

static void openSettings() {
    if (LittleFS.begin()) {
        switch (Settings::begin()) {
            case Settings::ok:
                connectWiFi();
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

        EnvironmentDisplay::displayMessage(Settings::get("WiFi_SSID"));
    }
    else {
        EnvironmentDisplay::displayMessage("No file system");
    }
}

static void connectWiFi() {
    WiFiConnection::wiFiStatus connected = WiFiConnection::begin(
            Settings::get("WiFi_SSID"), Settings::get("WiFi_Password"));

    switch (connected) {
        case WiFiConnection::connected:
            EnvironmentDisplay::displayMessage("Connected");
            AlexaControl::begin(Settings::get("Alexa_Name"), onDisplayChange);
            break;

        case WiFiConnection::disconnected:
            EnvironmentDisplay::displayMessage("WiFi connection failed");
            break;

        default:
            break;
    }
}

/*
** Callback for Alexa events. Change on/off state and/or brightness of the displays.
*/

static void onDisplayChange(bool state, unsigned char value) {
    EnvironmentDisplay::switchDisplay(state, value);
    ClockDisplay::switchDisplay(state, value);
}

/*
** Update the environment display.
*/

static void updateEnvironment() {
    /*
    Sensors::update();
    EnvironmentDisplay::displayTemperature(Sensors::getTemperature());
    EnvironmentDisplay::displayHumidity(Sensors::getHumidity());
    EnvironmentDisplay::displayBrightness(Sensors::getBrightness());
    */
}

