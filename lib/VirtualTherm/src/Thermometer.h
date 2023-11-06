// Thermometer.h
#ifndef THERMOMETER_H
#define THERMOMETER_H

#include "TemperatureUnit.h"
#include <cmath>

class Thermometer {
protected:
  static double convertTemperature(double temperature, TemperatureUnit fromUnit, TemperatureUnit toUnit);
};

inline double Thermometer::convertTemperature(double temperature, TemperatureUnit fromUnit, TemperatureUnit toUnit) {
  // First convert the input to Celsius, which is the intermediate unit
  double tempCelsius;
  switch (fromUnit) {
  case TemperatureUnit::Celsius:
    tempCelsius = temperature;
    break;
  case TemperatureUnit::Fahrenheit:
    tempCelsius = (temperature - 32) * 5.0 / 9.0;
    break;
  case TemperatureUnit::Kelvin:
    tempCelsius = temperature - 273.15;
    break;
  }

  // Then, convert from Celsius to the desired unit
  switch (toUnit) {
  case TemperatureUnit::Celsius:
    return tempCelsius;
  case TemperatureUnit::Fahrenheit:
    return tempCelsius * 9.0 / 5.0 + 32;
  case TemperatureUnit::Kelvin:
    return tempCelsius + 273.15;
  }

  // If we reach this point, the unit was not recognized. Handle the error as appropriate.
  // Possibly throw an exception or return a sentinel value.
}

#endif // THERMOMETER_H
