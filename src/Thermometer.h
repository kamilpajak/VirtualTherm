// Thermometer.h
#ifndef THERMOMETER_H
#define THERMOMETER_H

#include "TemperatureUnits.h"
#include <cmath>

class Thermometer {
protected:
  static double convertTemperatureToCelsius(double temperature, TemperatureUnit unit);
};

inline double Thermometer::convertTemperatureToCelsius(double temperature, TemperatureUnit unit) {
  switch (unit) {
  case TemperatureUnit::Celsius:
    return temperature;
  case TemperatureUnit::Fahrenheit:
    return (temperature - 32) * 5.0 / 9.0;
  case TemperatureUnit::Kelvin:
    return temperature - 273.15;
  }
}

#endif // THERMOMETER_H