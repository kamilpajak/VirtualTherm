#include "OpenMeteoManager.h"
#include "WiFiManager.h"
#include "arduino_secrets.h"

#include <Arduino.h>
#include <Pt1000.h>

#define DAC_PIN A0
#define DAC_RESOLUTION 10
#define MAX_RESISTANCE 2000.0
#define MAX_DAC_VALUE 4095

WiFiManager wifiManager;
WiFiClient wifiClient;
OpenMeteoManager openMeteoManager(wifiClient);

Pt1000 sensor; // Create an instance of Pt1000

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
    Serial.println("Temperature retrieval failed. Retrying...");
    // Optionally, add retry logic or error handling here.
    return; // Skip the rest of the loop iteration.
  }
  Serial.println("Temperature from API: " + String(temperature) + " °C");

  double resistance = sensor.calculateResistance(temperature, TemperatureUnit::Celsius);
  Serial.println("Calculated Resistance: " + String(resistance) + " Ω");

  int dacValue = resistanceToDAC(resistance);
  analogWrite(DAC_PIN, dacValue);

  delay(60000);
}

int resistanceToDAC(double resistance) {
  int dacValue = (resistance / MAX_RESISTANCE) * MAX_DAC_VALUE;
  dacValue = constrain(dacValue, 0, MAX_DAC_VALUE);
  return dacValue;
}
