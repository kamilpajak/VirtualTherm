#include <NickelRTD.h>
#include <PlatinumRTD.h>
#include <TemperatureUnit.h>
#include <stdexcept>
#include <unity.h>

void setUp(void) {
  // Set up any required resources before each test
}

void tearDown(void) {
  // Clean up any resources after each test
}

void test_temperatureConversionError(void) {
  bool errorThrown = false;
  try {
    // Intentionally using an invalid temperature unit to provoke an error
    Thermometer::convertTemperature(100.0, static_cast<TemperatureUnit>(999), TemperatureUnit::Celsius);
  } catch (const std::invalid_argument &e) {
    errorThrown = true;
  }
  if (!errorThrown) {
    TEST_FAIL_MESSAGE("Expected exception was not thrown.");
  }
}

void assertResistanceWithinTolerance(RTD &sensor, double tolerance, double expectedResistance, double temperature,
                                     TemperatureUnit unit) {
  double actualResistance = sensor.calculateResistance(temperature, unit);
  TEST_ASSERT_DOUBLE_WITHIN(tolerance, expectedResistance, actualResistance);
}

void test_calculatePt100Resistance(void) {
  PlatinumRTD sensor{100};
  const double TOLERANCE = 0.25;
  assertResistanceWithinTolerance(sensor, TOLERANCE, 18.49, -200.0, TemperatureUnit::Celsius);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 100.00, 0.0, TemperatureUnit::Celsius);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 390.26, 850.0, TemperatureUnit::Celsius);

  assertResistanceWithinTolerance(sensor, TOLERANCE, 18.49, -328.0, TemperatureUnit::Fahrenheit);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 100.00, 32.0, TemperatureUnit::Fahrenheit);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 390.26, 1562.0, TemperatureUnit::Fahrenheit);
}

void test_calculatePt1000Resistance(void) {
  PlatinumRTD sensor{1000};
  const double TOLERANCE = 0.05;
  assertResistanceWithinTolerance(sensor, TOLERANCE, 723.33, -70.0, TemperatureUnit::Celsius);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 1000.00, 0.0, TemperatureUnit::Celsius);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 2809.80, 500.0, TemperatureUnit::Celsius);

  assertResistanceWithinTolerance(sensor, TOLERANCE, 723.33, -94.0, TemperatureUnit::Fahrenheit);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 1000.00, 32.0, TemperatureUnit::Fahrenheit);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 2809.80, 932.0, TemperatureUnit::Fahrenheit);
}

void test_calculateNi120Resistance(void) {
  NickelRTD sensor{120};
  const double TOLERANCE = 0.05;
  // assertResistanceWithinTolerance(sensor, TOLERANCE, 66.60, -80.0, TemperatureUnit::Celsius);

  // assertResistanceWithinTolerance(sensor, TOLERANCE, 67.32, -110.0, TemperatureUnit::Fahrenheit);
  // assertResistanceWithinTolerance(sensor, TOLERANCE, 380.31, 500.0, TemperatureUnit::Fahrenheit);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 120.00, 0.0, TemperatureUnit::Celsius);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 127.17, 10.0, TemperatureUnit::Celsius);
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_temperatureConversionError);
  RUN_TEST(test_calculatePt100Resistance);
  RUN_TEST(test_calculatePt1000Resistance);
  RUN_TEST(test_calculateNi120Resistance);
  UNITY_END();
}
