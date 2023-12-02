// NickelRTD.h
#ifndef NICKEL_RTD_H
#define NICKEL_RTD_H

#include "RTD.h"
#include <cmath>

class NickelRTD : public RTD {
public:
  // Initialize R0 for NickelRTD in the constructor
  explicit NickelRTD(double r0) : RTD(r0) {}

  // Override the calculateResistance using nickel-specific coefficients
  double calculateResistance(double temperature, TemperatureUnit unit) override;

private:
  static constexpr double a = 0.005916007;           // Coefficient for temperature
  static constexpr double b = 0.000006760135;        // Coefficient for temperature squared
  static constexpr double c = 0.00000001997253;      // Coefficient for temperature cubed
  static constexpr double d = -0.00000000009988596;  // Coefficient for temperature to the fourth
  static constexpr double e = 0.0000000000002358126; // Coefficient for temperature to the fifth
};

inline double NickelRTD::calculateResistance(double temperature, TemperatureUnit unit) {
  temperature = TemperatureConverter::convert(temperature, unit, TemperatureUnit::Celsius);

  // Use the polynomial equation derived from the curve fitting process
  double resistance = R0 * (1 + a * temperature + b * std::pow(temperature, 2) + c * std::pow(temperature, 3) +
                            d * std::pow(temperature, 4) + e * std::pow(temperature, 5));

  return resistance;
}

#endif // NICKEL_RTD_H
