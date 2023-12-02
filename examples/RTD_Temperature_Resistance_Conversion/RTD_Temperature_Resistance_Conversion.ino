#include <Arduino.h>
#include <NickelRTD.h>
#include <PlatinumRTD.h>
#include <TemperatureUnit.h>

PlatinumRTD pt100(100);   // Pt100 with a resistance of 100 ohms at 0°C
PlatinumRTD pt1000(1000); // Pt1000 with a resistance of 1000 ohms at 0°C
NickelRTD ni120(120);     // Ni120 with a resistance of 120 ohms at 0°C

void setup() { Serial.begin(9600); }

void loop() {
  // Calculating resistance at 25 degrees Celsius using Pt100
  float resistanceCelsius = pt100.calculateResistance(25.0, TemperatureUnit::CELSIUS);
  Serial.print("Resistance at 25 °C (Pt100) = ");
  Serial.print(resistanceCelsius);
  Serial.println(" Ohm");

  // Calculating resistance at 50 degrees Fahrenheit using Pt1000
  float resistanceFahrenheit = pt1000.calculateResistance(50.0, TemperatureUnit::FAHRENHEIT);
  Serial.print("Resistance at 50 °F (Pt1000) = ");
  Serial.print(resistanceFahrenheit);
  Serial.println(" Ohm");

  // Calculating resistance at 300 degrees Kelvin using Ni120
  float resistanceKelvin = ni120.calculateResistance(300.0, TemperatureUnit::KELVIN);
  Serial.print("Resistance at 300 K (Ni120) = ");
  Serial.print(resistanceKelvin);
  Serial.println(" Ohm");

  Serial.println();
  delay(500);
}
