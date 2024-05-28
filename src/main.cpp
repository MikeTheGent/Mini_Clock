
#include <Arduino.h>
#include <LittleFS.h>
#include <Wire.h>
#include <RTClib.h>
#include "Settings.h"
#include "WiFiConnection.h"
#include "AlexaControl.h"
#include "NetworkTime.h"
#include "EnvironmentDisplay.h"
#include "ClockDisplay.h"
#include "Sensors.h"

static WiFiConnection::wiFiStatus connectWiFi(void);
static bool openSettings();
static void onDisplayChange(bool, unsigned char value);
static void updateEnvironment(void);

void setup() {
    Serial.begin(115200);
    Wire.begin();
    EnvironmentDisplay::begin();
    ClockDisplay::begin();
    Sensors::begin();

    if (openSettings()) {
        connectWiFi();
    }
}

void loop() {
    static unsigned long nextSensorUpdate = 0;
    static unsigned long previousMillis = 0;
    AlexaControl::loop();

    DateTime now = NetworkTime::now();
    static uint8_t currentMinute = 61;

    if (now.minute() != currentMinute) {
        Serial.printf("Now %s\n", now.timestamp().c_str());
        ClockDisplay::displayTime(now.hour(), now.minute());
        currentMinute = now.minute();
    }

    if (millis() < previousMillis) {
        nextSensorUpdate = millis();
    }

    previousMillis = millis();

    if (millis() > nextSensorUpdate) {
        updateEnvironment();
        nextSensorUpdate = millis() + 10000;
    }
}

static bool openSettings() {
    bool result = false;

    if (LittleFS.begin()) {
        switch (Settings::begin()) {
            case Settings::ok:
                result = true;
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

    return result;
}

static WiFiConnection::wiFiStatus connectWiFi() {
    EnvironmentDisplay::displayMessage("Connecting");
    WiFiConnection::wiFiStatus connected = WiFiConnection::begin(
            Settings::get("WiFi_SSID"), Settings::get("WiFi_Password"));

    switch (connected) {
        case WiFiConnection::connected:
            EnvironmentDisplay::displayMessage("Connected");
            AlexaControl::begin(Settings::get("Alexa_Name"), onDisplayChange);
            NetworkTime::begin();
            break;

        case WiFiConnection::disconnected:
            EnvironmentDisplay::displayMessage("WiFi connection failed");
            break;

        default:
            break;
    }

    return connected;
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
    Sensors::update();
    EnvironmentDisplay::displayTemperature(Sensors::getTemperature());
    EnvironmentDisplay::displayHumidity(Sensors::getHumidity());
    EnvironmentDisplay::displayBrightness(Sensors::getBrightness());
}

