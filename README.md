
# VirtualTherm

## Overview
VirtualTherm is an Arduino library designed for simulating Resistance Temperature Detector (RTD) sensors. It enables the calculation of resistance for a wide range of RTD sensors, adapting to various types of thermometers based on platinum or nickel, such as Pt100, Pt500, Pt1000, and Ni120. This library is ideal for applications that require accurate RTD sensor simulations without the need for physical sensors.

## Features
- Supports a wide range of RTD types: Pt100, Pt500, Pt1000, Ni120, etc.
- Accurate temperature to resistance conversion.
- Handles multiple temperature units: Celsius, Fahrenheit, and Kelvin.
- Flexible and easy to use with Arduino, allowing simulation of different types of RTD sensors.

## Installation
Download this repository and place it in the Arduino 'libraries' folder. Restart the Arduino IDE, and the VirtualTherm library will be available for use.

## Usage
Include the necessary headers in your Arduino sketch. Here's a basic example using the Pt100 sensor:

```cpp
#include <PlatinumRTD.h>
#include <TemperatureUnit.h>

PlatinumRTD pt100(100); // Pt100 sensor

void setup() {
  Serial.begin(9600);
  float resistance = pt100.calculateResistance(25.0, TemperatureUnit::CELSIUS);
  Serial.print("Resistance: ");
  Serial.print(resistance);
  Serial.println(" Ohm");
}

void loop() {
  // Your code here
}
```

## Examples
Check out the `examples` directory for various ways to use the library with different RTD sensors and temperature units.

- `RTD_Temperature_Resistance_Conversion.ino`: Demonstrates converting temperature to resistance for different RTD types.

## License
This library is released under the [BSD 3-Clause License](LICENSE).

## Acknowledgements
Thank you to all the users and supporters of the VirtualTherm. Your engagement is greatly appreciated.
