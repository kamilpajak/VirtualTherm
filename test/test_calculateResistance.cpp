#include "Pt1000.h"
#include <unity.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

// Define a new test function for Pt1000::calculateResistance
void test_calculateResistance(void) {
  const double TOLERANCE = 0.05;
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 723.3, Pt1000::calculateResistance(-70.0));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 783.2, Pt1000::calculateResistance(-55.0));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 1000.0, Pt1000::calculateResistance(0.0));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 1213.2, Pt1000::calculateResistance(55.0));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 1270.8, Pt1000::calculateResistance(70.0));
  TEST_ASSERT_DOUBLE_WITHIN(TOLERANCE, 2809.8, Pt1000::calculateResistance(500.0));
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_calculateResistance);
  UNITY_END();
}
