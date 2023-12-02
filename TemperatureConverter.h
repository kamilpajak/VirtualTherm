// TemperatureConverter.h
#ifndef TEMPERATURE_CONVERTER_H
#define TEMPERATURE_CONVERTER_H

#include "TemperatureUnit.h"
#include <cmath>

class TemperatureConverter {
public:
  static double convert(double temperature, TemperatureUnit fromUnit, TemperatureUnit toUnit);

private:
  TemperatureConverter() {} // Private constructor to prevent instantiation
};

double TemperatureConverter::convert(double temperature, TemperatureUnit fromUnit, TemperatureUnit toUnit) {
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

#endif // TEMPERATURE_CONVERTER_H
