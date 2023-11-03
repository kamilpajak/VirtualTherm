#ifndef OPENMETEOMANAGER_H
#define OPENMETEOMANAGER_H

#include "arduino_secrets.h"

#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <WiFiNINA.h>

class OpenMeteoManager {
public:
  OpenMeteoManager(WiFiClient &wifiClient) : httpClient(wifiClient, "api.open-meteo.com", 80) {}

  double getTemperature() {
    httpClient.beginRequest();
    httpClient.get("/v1/forecast?latitude=" + String(LATITUDE) + "&longitude=" + String(LONGITUDE) +
                   "&current=temperature_2m&timezone=auto&forecast_days=1");
    httpClient.endRequest();

    int statusCode = httpClient.responseStatusCode();
    String response = httpClient.responseBody();
    if (statusCode != 200) {
      Serial.println("Failed to get temperature from API: " + String(statusCode));
      return NAN;
    }

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.println("Failed to parse JSON response: " + String(error.c_str()));
      return NAN;
    }

    double temperature = doc["current"]["temperature_2m"];
    return temperature;
  }

private:
  HttpClient httpClient;
};

#endif // OPENMETEOMANAGER_H
