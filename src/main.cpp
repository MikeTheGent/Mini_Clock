/*
** Clock with two displays -- a larger LED display that can be read across a typical
** living room and a smaller TFT to display environment information.
**
** (C) 2024, Mike Wilson. MIT License -- see LICENSE file included in the distribution.
*/

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

void onDisplayChange(bool state);
static WiFiConnection::wiFiStatus connectWiFi(void);
static Settings::settingStatus openSettings();
static void updateEnvironment(void);

void setup() {
    Wire.begin();
    Serial.begin(115200);

    while(! Serial) {
        delay(10);
    }

    EnvironmentDisplay::begin();
    ClockDisplay::begin();
    Sensors::begin();

    if (openSettings() == Settings::ok) {
        if (connectWiFi() == WiFiConnection::connected) {
            AlexaControl::begin(Settings::get("Alexa_Name"), onDisplayChange);

            if (! NetworkTime::begin()) {
                EnvironmentDisplay::displayMessage("RTC not found");
            }
        }
    }
}

void loop() {
    static unsigned long nextSensorUpdate = 0;
    static unsigned long previousMillis = 0;
    static DateTime lastRefreshTime = DateTime();
    static uint8_t currentMinute = 61;

    AlexaControl::loop();
    DateTime now = NetworkTime::now();
    TimeSpan lastRefresh = now - lastRefreshTime;

    /*
    ** Periodically refresh the RTC from NTP.
    */

    if (lastRefresh.hours() > 4) {
        if (WiFiConnection::getStatus() != WiFiConnection::connected) {
            if (WiFiConnection::reconnect() == WiFiConnection::connected) {
                NetworkTime::synchronise();
            }
        }

        lastRefreshTime = now;
    }

    if (now.minute() != currentMinute) {
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

static Settings::settingStatus openSettings() {
    Settings::settingStatus status = Settings::fileNotFound;

    if (LittleFS.begin()) {
        status = Settings::begin();

        switch (status) {
            case Settings::ok:
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

        LittleFS.end();
        EnvironmentDisplay::displayMessage(Settings::get("WiFi_SSID"));
    }
    else {
        EnvironmentDisplay::displayMessage("No file system");
    }

    return status;
}

static WiFiConnection::wiFiStatus connectWiFi() {
    EnvironmentDisplay::displayMessage("Connecting");
    WiFiConnection::wiFiStatus connected = WiFiConnection::begin(
            Settings::get("WiFi_SSID"), Settings::get("WiFi_Password"));

    switch (connected) {
        case WiFiConnection::connected:
            EnvironmentDisplay::displayMessage("Connected");
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

void onDisplayChange(bool state) {
    EnvironmentDisplay::switchDisplay(state);
    ClockDisplay::switchDisplay(state);
}

/*
** Update the environment display.
*/

static void updateEnvironment() {
    Sensors::update();
    EnvironmentDisplay::displayTemperature(Sensors::getTemperature());
    EnvironmentDisplay::displayHumidity(Sensors::getHumidity());
    EnvironmentDisplay::displayPressure(Sensors::getPressure());
    long brightness = Sensors::getBrightness();
    Serial.printf("Brightness %ld\n", brightness);
    EnvironmentDisplay::adjustBrightness(brightness);
    ClockDisplay::adjustBrightness(brightness);
}

