// Thermometer.h
#ifndef THERMOMETER_H
#define THERMOMETER_H

#include "TemperatureUnit.h"
#include <cmath> // Include this to use NAN

class Thermometer {
public:
  static double convertTemperature(double temperature, TemperatureUnit fromUnit, TemperatureUnit toUnit);

private:
  Thermometer() {} // Private constructor to prevent instantiation
};

double Thermometer::convertTemperature(double temperature, TemperatureUnit fromUnit, TemperatureUnit toUnit) {
  // First convert the input to Celsius as a base for further conversion
  double tempCelsius = temperature;
  if (fromUnit == TemperatureUnit::Fahrenheit) {
    tempCelsius = (temperature - 32) * 5.0 / 9.0;
  } else if (fromUnit == TemperatureUnit::Kelvin) {
    tempCelsius = temperature - 273.15;
  } else if (fromUnit != TemperatureUnit::Celsius) {
    // Unsupported 'from' temperature unit, return NAN
    return NAN;
  }

  // Then convert from Celsius to the desired unit
  if (toUnit == TemperatureUnit::Celsius) {
    return tempCelsius;
  } else if (toUnit == TemperatureUnit::Fahrenheit) {
    return tempCelsius * 9.0 / 5.0 + 32;
  } else if (toUnit == TemperatureUnit::Kelvin) {
    return tempCelsius + 273.15;
  } else {
    // Unsupported 'to' temperature unit, return NAN
    return NAN;
  }
}

#endif // THERMOMETER_H
