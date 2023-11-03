#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include "arduino_secrets.h"
#include <Arduino.h>
#include <WiFiNINA.h>

class WiFiManager {
public:
  WiFiManager() { attemptConnection(initialReconnectDelay); }

  void connect() { attemptConnection(initialReconnectDelay); }

  void reconnect() { attemptConnection(initialReconnectDelay); }

  bool isConnected() { return WiFi.status() == WL_CONNECTED; }

private:
  void attemptConnection(unsigned long delayAmount) {
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < reconnectAttempts) {
      WiFi.begin(SECRET_SSID, SECRET_PASS);
      Serial.print("Attempting connection... Status: ");
      Serial.println(WiFi.status());
      unsigned long startTime = millis();
      while (WiFi.status() != WL_CONNECTED && millis() - startTime < delayAmount) {
        delay(100);
      }
      attempts++;
      delayAmount *= delayMultiplier;
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Failed to connect. Resetting board...");
      delay(1000);        // Optional delay to allow the serial message to be sent.
      NVIC_SystemReset(); // Reset the board.
    } else {
      Serial.println("Connected to WiFi");
    }
  }

  static constexpr int reconnectAttempts = 5;
  static constexpr unsigned long initialReconnectDelay = 5000;
  static constexpr float delayMultiplier = 2.0;
};

#endif // WIFIMANAGER_H
