/*
** Display for environment information -- tempertaure, humidity etc.
**
** (C) 2024, Mike Wilson. MIT License -- see LICENSE file included in the distribution.
*/

#include <TFT_eSPI.h>
#include "EnvironmentDisplay.h"

namespace EnvironmentDisplay {
    namespace {
        TFT_eSPI tft = TFT_eSPI();
        const uint8_t backlightChannel = 1;
        const uint8_t backlightPin = TFT_BL;
        const GFXfont *largeFont = &FreeSerif18pt7b;
        const uint16_t backgroundColour = TFT_BLACK;
    }

    void begin() {
        tft.init();
        tft.setRotation(1);
        tft.fillScreen(backgroundColour);
        analogWrite(TFT_BL, 128);

        tft.setFreeFont(largeFont);
        tft.setCursor(10, 34);
        tft.setTextColor(TFT_ORANGE, backgroundColour);
        tft.print("Temperature");

        tft.setCursor(10, 74);
        tft.setTextColor(TFT_CYAN, backgroundColour);
        tft.print("Humidity");

        tft.setCursor(10, 114);
        tft.setTextColor(TFT_YELLOW, backgroundColour);
        tft.print("Pressure");

        displayTemperature(0.0);
        displayHumidity(0);
        displayPressure(0);
        switchDisplay(true);
    }

    void displayTemperature(float temperature) {
        tft.fillRect(200, 9, 99, 34, backgroundColour);
        tft.setTextColor(TFT_ORANGE, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(200, 34);
        tft.printf("%.1f", temperature);
    }
    
    void displayHumidity(long humidity) {
        tft.fillRect(200, 49, 99, 34, backgroundColour);
        tft.setTextColor(TFT_CYAN, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(200, 74);
        tft.printf("%ld%%", humidity);
    }

    void displayPressure(float pressure) {
        tft.fillRect(200, 89, 99, 34, backgroundColour);
        tft.setTextColor(TFT_YELLOW, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(200, 114);
        tft.printf("%.1f", pressure);
    }

    void displayMessage(const char *message) {
        tft.fillRect(10, 129, 310, 34, backgroundColour);
        tft.setTextColor(TFT_GREEN, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(10, 154);
        tft.print(message);
    }

    void switchDisplay(bool state) {
        if (state) {
            analogWrite(TFT_BL, 32);
        }
        else {
            analogWrite(TFT_BL, 0);
        }
    }

    void adjustBrightness(long brightness) {
        uint8_t constrained = constrain(map(brightness, 0, 1000, 1, 255), 1, 255);
        analogWrite(TFT_BL, constrained);
    }
}
