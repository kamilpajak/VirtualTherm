#include <Pt100.h>
#include <Pt1000.h>
#include <TemperatureUnit.h>
#include <unity.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_calculatePt100Resistance(void) {
  Pt100 sensor;
  const double TOLERANCE = 0.25;
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 18.49, sensor.calculateResistance(-200.0, TemperatureUnit::Celsius));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 100.00, sensor.calculateResistance(0.0, TemperatureUnit::Celsius));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 390.26, sensor.calculateResistance(850.0, TemperatureUnit::Celsius));

  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 18.49, sensor.calculateResistance(-328.0, TemperatureUnit::Fahrenheit));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 100.00, sensor.calculateResistance(32.0, TemperatureUnit::Fahrenheit));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 390.26, sensor.calculateResistance(1562.0, TemperatureUnit::Fahrenheit));
}

void test_calculatePt1000Resistance(void) {
  Pt1000 sensor;
  const double TOLERANCE = 0.05;
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 723.33, sensor.calculateResistance(-70.0, TemperatureUnit::Celsius));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 1000.00, sensor.calculateResistance(0.0, TemperatureUnit::Celsius));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 2809.80, sensor.calculateResistance(500.0, TemperatureUnit::Celsius));

  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 723.33, sensor.calculateResistance(-94.0, TemperatureUnit::Fahrenheit));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 1000.00, sensor.calculateResistance(32.0, TemperatureUnit::Fahrenheit));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 2809.80, sensor.calculateResistance(932.0, TemperatureUnit::Fahrenheit));
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_calculatePt100Resistance);
  RUN_TEST(test_calculatePt1000Resistance);
  UNITY_END();
}
