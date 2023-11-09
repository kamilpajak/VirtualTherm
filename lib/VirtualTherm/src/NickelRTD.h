// NickelRTD.h
#ifndef NICKEL_RTD_H
#define NICKEL_RTD_H

#include "RTD.h"
#include <cmath> // Include this to use std::pow

class NickelRTD : public RTD {
public:
  // Initialize R0 for NickelRTD in the constructor
  explicit NickelRTD(double r0) : RTD(r0) {}

  // Override the calculateResistance using nickel-specific coefficients
  double calculateResistance(double temperature, TemperatureUnit unit) override;

private:
  // Nickel RTD coefficients shared across all instances
  static constexpr double A = 5.485e-3;   // First coefficient
  static constexpr double B = 6.650e-6;   // Second coefficient
  static constexpr double C = 2.805e-11;  // Third coefficient for temperatures below 0°C
  static constexpr double D = -2.000e-17; // Fourth coefficient for temperatures below 0°C
};

inline double NickelRTD::calculateResistance(double temperature, TemperatureUnit unit) {
  temperature = Thermometer::convertTemperature(temperature, unit, TemperatureUnit::Celsius);

  double Rt; // Resistance of the RTD at the given temperature
  if (temperature >= 0) {
    Rt = R0 * (1 + A * temperature + B * std::pow(temperature, 2));
  } else {
    Rt = R0 * (1 + A * temperature + B * std::pow(temperature, 2) + C * std::pow(temperature, 4) +
               D * std::pow(temperature, 6));
  }
  return Rt;
}

#endif // NICKEL_RTD_H
