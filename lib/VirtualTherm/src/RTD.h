// RTD.h
#ifndef RTD_H
#define RTD_H

#include "Thermometer.h"
#include <cmath>

class RTD {
protected:
  double R0; // Base resistance at 0°C, specific to the RTD type (e.g., Pt100, Pt1000)

  static constexpr double A = 3.9083e-3;          // First Callendar-Van Dusen coefficient
  static constexpr double B = -5.775e-7;          // Second Callendar-Van Dusen coefficient
  static constexpr double C_above_0 = 0;          // Third Callendar-Van Dusen coefficient for temperatures above 0°C
  static constexpr double C_below_0 = -4.183e-12; // Third Callendar-Van Dusen coefficient for temperatures below 0°C

public:
  double calculateResistance(double temperature, TemperatureUnit unit);

protected:
  RTD(double r0) : R0(r0) {} // Constructor initializing base resistance
};

inline double RTD::calculateResistance(double temperature, TemperatureUnit unit) {
  temperature = Thermometer::convertTemperature(temperature, unit, TemperatureUnit::Celsius);
  double Rt; // Resistance of the RTD at the given temperature
  if (temperature >= 0) {
    // Calculate resistance for temperatures above 0°C using Callendar-Van Dusen equation
    Rt = R0 * (1 + A * temperature + B * std::pow(temperature, 2) +
               C_above_0 * (temperature - 100) * std::pow(temperature, 3));
  } else {
    // Calculate resistance for temperatures below 0°C using Callendar-Van Dusen equation
    Rt = R0 * (1 + A * temperature + B * std::pow(temperature, 2) +
               C_below_0 * (temperature - 100) * std::pow(temperature, 3));
  }
  return Rt;
}

#endif // RTD_H
