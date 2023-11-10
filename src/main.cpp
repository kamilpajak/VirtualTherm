#include "OpenMeteoManager.h"
#include "WiFiManager.h"
#include "arduino_secrets.h"

#include <Arduino.h>
#include <PlatinumRTD.h>

#define DAC_PIN A0
#define DAC_RESOLUTION 10
#define MAX_RESISTANCE 2000.0
#define MAX_DAC_VALUE 4095

// Constants for program behavior
const int DelayBetweenMeasurements = 60000; // Delay between measurements in milliseconds
const int MaxRetries = 5;                   // Number of retries for temperature retrieval

WiFiManager wifiManager;
WiFiClient wifiClient;
OpenMeteoManager openMeteoManager(wifiClient);

PlatinumRTD sensor(1000); // Create an instance of PlatinumRTD with base resistance of 1000 ohms

int resistanceToDAC(double resistance);

void setup() {
  Serial.begin(115200);
  analogWriteResolution(DAC_RESOLUTION);
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
    Serial.println("Resistance calculation failed due to invalid temperature conversion.");
    return; // Wait for the next iteration of loop() to retry
  }
  Serial.println("Calculated Resistance: " + String(resistance) + " Ω");

  int dacValue = resistanceToDAC(resistance);
  analogWrite(DAC_PIN, dacValue);

  delay(DelayBetweenMeasurements);
}

int resistanceToDAC(double resistance) {
  int dacValue = (resistance / MAX_RESISTANCE) * MAX_DAC_VALUE;
  dacValue = constrain(dacValue, 0, MAX_DAC_VALUE);
  return dacValue;
}
