/*
** Environment sensors. Eg, temperature, humidity, light level. Originally designed
** to use a BH1750 light sensor & BME208 temperature & humidity sensor.
** Either of these can be substituted with appropriate alternatives.
**
** (C) 2024, Mike Wilson. MIT License -- see LICENSE file included in the distribution.
*/

#include <hp_BH1750.h>
#include "Sensors.h"
#include <Adafruit_BME280.h>

namespace Sensors {
    namespace {
        hp_BH1750 bh1750;
        Adafruit_BME280 bme;
        Adafruit_Sensor *temperatureSensor = bme.getTemperatureSensor();
        Adafruit_Sensor *pressureSensor = bme.getPressureSensor();
        Adafruit_Sensor *humiditySensor = bme.getHumiditySensor();
        sensors_event_t temperatureEvent;
        sensors_event_t pressureEvent;
        sensors_event_t humidityEvent;

    }

    bool begin() {
        bme.begin(0x76);
        return bh1750.begin(BH1750_TO_GROUND);
    }

    void update() {
        temperatureSensor->getEvent(&temperatureEvent);
        humiditySensor->getEvent(&humidityEvent);
        pressureSensor->getEvent(&pressureEvent);
    }

    float getTemperature() {
        return temperatureEvent.temperature;
    }

    float getHumidity() {
        return humidityEvent.relative_humidity;
    }

    float getPressure() {
        return pressureEvent.pressure;
    }

    long getBrightness() {
        bh1750.start();
        return long(bh1750.getLux());
    }
}

