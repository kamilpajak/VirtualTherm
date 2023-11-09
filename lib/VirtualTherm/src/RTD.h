// RTD.h
#ifndef RTD_H
#define RTD_H

#include "TemperatureUnit.h"
#include "Thermometer.h"

class RTD {
protected:
  double R0; // Base resistance at 0°C
public:
  // Constructor initializing base resistance
  explicit RTD(double r0) : R0(r0) {}
  virtual double calculateResistance(double temperature, TemperatureUnit unit) = 0;
  virtual ~RTD() = default;
};

#endif // RTD_H
