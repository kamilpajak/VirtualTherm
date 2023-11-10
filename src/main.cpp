#include "OpenMeteoManager.h"
#include "SensorOutputSimulator.h"
#include "WiFiManager.h"
#include "arduino_secrets.h"

#include <Arduino.h>
#include <PlatinumRTD.h>

// Constants for program behavior
const int DelayBetweenMeasurements = 60000; // Delay between measurements in milliseconds

WiFiManager wifiManager;
WiFiClient wifiClient;
OpenMeteoManager openMeteoManager(wifiClient);

PlatinumRTD sensor(1000); // Create an instance of PlatinumRTD with base resistance of 1000 ohms

// Initialize the SensorOutputSimulator with appropriate DAC settings
SensorOutputSimulator dacSimulator(A0, 10, 2000.0, 4095);

void setup() {
  Serial.begin(115200);
  wifiManager.init();
}

void loop() {
  if (!wifiManager.isConnected()) {
    wifiManager.init();
  }

  double temperature = openMeteoManager.getTemperature();
  if (isnan(temperature)) {
    Serial.println("Temperature retrieval failed.");
    return; // Wait for the next iteration of loop() to retry
  }

  Serial.println("Temperature from API: " + String(temperature) + " °C");

  double resistance = sensor.calculateResistance(temperature, TemperatureUnit::Celsius);
  if (isnan(resistance)) {
    Serial.println("Resistance calculation failed. Check temperature range or sensor parameters.");
    return; // Wait for the next iteration of loop() to retry
  }
  Serial.println("Calculated Resistance: " + String(resistance) + " Ω");

  dacSimulator.simulateResistance(resistance);

  delay(DelayBetweenMeasurements);
}
