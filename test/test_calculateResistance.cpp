#include <Pt100.h>
#include <Pt1000.h>
#include <TemperatureUnit.h>
#include <unity.h>

void setUp(void) {
  // Set up any required resources before each test
}

void tearDown(void) {
  // Clean up any resources after each test
}

void assertResistanceWithinTolerance(RTD &sensor, double tolerance, double expectedResistance, double temperature,
                                     TemperatureUnit unit) {
  double actualResistance = sensor.calculateResistance(temperature, unit);
  if (isnan(actualResistance)) {
    TEST_FAIL_MESSAGE("Received NaN for resistance value.");
  }
  TEST_ASSERT_DOUBLE_WITHIN(tolerance, expectedResistance, actualResistance);
}

void test_calculatePt100Resistance(void) {
  Pt100 sensor;
  const double TOLERANCE = 0.25;
  assertResistanceWithinTolerance(sensor, TOLERANCE, 18.49, -200.0, TemperatureUnit::Celsius);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 100.00, 0.0, TemperatureUnit::Celsius);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 390.26, 850.0, TemperatureUnit::Celsius);

  assertResistanceWithinTolerance(sensor, TOLERANCE, 18.49, -328.0, TemperatureUnit::Fahrenheit);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 100.00, 32.0, TemperatureUnit::Fahrenheit);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 390.26, 1562.0, TemperatureUnit::Fahrenheit);
}

void test_calculatePt1000Resistance(void) {
  Pt1000 sensor;
  const double TOLERANCE = 0.05;
  assertResistanceWithinTolerance(sensor, TOLERANCE, 723.33, -70.0, TemperatureUnit::Celsius);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 1000.00, 0.0, TemperatureUnit::Celsius);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 2809.80, 500.0, TemperatureUnit::Celsius);

  assertResistanceWithinTolerance(sensor, TOLERANCE, 723.33, -94.0, TemperatureUnit::Fahrenheit);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 1000.00, 32.0, TemperatureUnit::Fahrenheit);
  assertResistanceWithinTolerance(sensor, TOLERANCE, 2809.80, 932.0, TemperatureUnit::Fahrenheit);
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_calculatePt100Resistance);
  RUN_TEST(test_calculatePt1000Resistance);
  UNITY_END();
}
