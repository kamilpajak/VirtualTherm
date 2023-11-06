// Pt100.h
#ifndef PT100_H
#define PT100_H

#include "Thermometer.h"
#include <cmath>

class Pt100 : public Thermometer {
public:
  static double calculateResistance(double temperature, TemperatureUnit unit);

private:
  static constexpr double R0 = 100.0; // Resistance at 0°C
  static constexpr double A = 3.9083e-3;
  static constexpr double B = -5.775e-7;
  static constexpr double C_above_0 = 0;
  static constexpr double C_below_0 = -4.183e-12;
};

inline double Pt100::calculateResistance(double temperature, TemperatureUnit unit) {
  temperature = convertTemperatureToCelsius(temperature, unit);
  double Rt;
  if (temperature >= 0) {
    Rt = R0 * (1 + A * temperature + B * std::pow(temperature, 2) +
               C_above_0 * (temperature - 100) * std::pow(temperature, 3));
  } else {
    Rt = R0 * (1 + A * temperature + B * std::pow(temperature, 2) +
               C_below_0 * (temperature - 100) * std::pow(temperature, 3));
  }
  return Rt;
}

#endif // PT100_H
