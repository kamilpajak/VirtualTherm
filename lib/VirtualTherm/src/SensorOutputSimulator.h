// SensorOutputSimulator.h
#ifndef SENSOR_OUTPUT_SIMULATOR_H
#define SENSOR_OUTPUT_SIMULATOR_H

#include <Arduino.h>

class SensorOutputSimulator {
public:
  SensorOutputSimulator(int pin, int resolution, double maxResistance, int maxValue)
    : DAC_PIN(pin), DAC_RESOLUTION(resolution), MAX_RESISTANCE(maxResistance), MAX_DAC_VALUE(maxValue) {
    analogWriteResolution(DAC_RESOLUTION);
  }

  void simulateResistance(double resistance) const {
    int dacValue = resistanceToDAC(resistance);
    analogWrite(DAC_PIN, dacValue);
  }

private:
  const int DAC_PIN;
  const int DAC_RESOLUTION;
  const double MAX_RESISTANCE;
  const int MAX_DAC_VALUE;

  int resistanceToDAC(double resistance) const {
    int dacValue = static_cast<int>((resistance / MAX_RESISTANCE) * MAX_DAC_VALUE);
    return constrain(dacValue, 0, MAX_DAC_VALUE);
  }
};

#endif // SENSOR_OUTPUT_SIMULATOR_H
