#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_addition(void) {
    TEST_ASSERT_EQUAL_INT(4, 2 + 2);
}

void test_false_condition(void) {
    TEST_ASSERT_FALSE(0); // 0 ist false
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addition);
    RUN_TEST(test_false_condition);
    return UNITY_END();
}
