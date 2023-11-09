// PlatinumRTD.h
#ifndef PLATINUM_RTD_H
#define PLATINUM_RTD_H

#include "RTD.h"
#include <cmath>

class PlatinumRTD : public RTD {
public:
  // Initialize R0 for PlatinumRTD in the constructor
  explicit PlatinumRTD(double r0) : RTD(r0) {}

  // Override the calculateResistance using nickel-specific coefficients
  double calculateResistance(double temperature, TemperatureUnit unit) override;

private:
  // Nickel RTD coefficients shared across all instances
  static constexpr double A = 3.9083e-3;   // First Callendar-Van Dusen coefficient
  static constexpr double B = -5.775e-7;   // Second Callendar-Van Dusen coefficient
  static constexpr double C0 = 0;          // Third Callendar-Van Dusen coefficient for temperatures above 0°C
  static constexpr double C1 = -4.183e-12; // Third Callendar-Van Dusen coefficient for temperatures below 0°C
};

inline double PlatinumRTD::calculateResistance(double temperature, TemperatureUnit unit) {
  temperature = Thermometer::convertTemperature(temperature, unit, TemperatureUnit::Celsius);
  double Rt; // Resistance of the RTD at the given temperature
  if (temperature >= 0) {
    // Calculate resistance for temperatures above 0°C using Callendar-Van Dusen equation
    Rt =
        R0 * (1 + A * temperature + B * std::pow(temperature, 2) + C0 * (temperature - 100) * std::pow(temperature, 3));
  } else {
    // Calculate resistance for temperatures below 0°C using Callendar-Van Dusen equation
    Rt =
        R0 * (1 + A * temperature + B * std::pow(temperature, 2) + C1 * (temperature - 100) * std::pow(temperature, 3));
  }
  return Rt;
}

#endif // PLATINUM_RTD_H
