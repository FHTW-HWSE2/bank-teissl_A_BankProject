#include "unity/src/unity.h"
#include "src/logic/validations.h"

void setUp(void) {}
void tearDown(void) {}

void test_is_valid_account_number(void) {
    TEST_ASSERT_TRUE(is_valid_account_number("12345678"));
    TEST_ASSERT_FALSE(is_valid_account_number("1234567"));   // 7 cifara
    TEST_ASSERT_FALSE(is_valid_account_number("123456789")); // 9 cifara
    TEST_ASSERT_FALSE(is_valid_account_number("abcd5678"));  // slova
}

void test_is_valid_ssn(void) {
    TEST_ASSERT_TRUE(is_valid_ssn("1234567890"));
    TEST_ASSERT_FALSE(is_valid_ssn("12345"));      // prekratko
    TEST_ASSERT_FALSE(is_valid_ssn("abcdefghij")); // slova
}

void test_is_valid_branch_code(void) {
    TEST_ASSERT_TRUE(is_valid_branch_code("B1"));
    TEST_ASSERT_TRUE(is_valid_branch_code("b2"));
    TEST_ASSERT_FALSE(is_valid_branch_code("C3"));
    TEST_ASSERT_FALSE(is_valid_branch_code(""));   // prazan
}

void test_is_valid_phone_number(void) {
    TEST_ASSERT_TRUE(is_valid_phone_number("0123456789"));
    TEST_ASSERT_FALSE(is_valid_phone_number("123-456"));  // crtica
    TEST_ASSERT_FALSE(is_valid_phone_number("(555)123")); // zagrade
    TEST_ASSERT_FALSE(is_valid_phone_number(""));         // prazan
}

void test_is_valid_email(void) {
    TEST_ASSERT_TRUE(is_valid_email("user@example.com"));
    TEST_ASSERT_FALSE(is_valid_email("userexample.com"));   // bez @
    TEST_ASSERT_FALSE(is_valid_email("@example.com"));      // počinje sa @
    TEST_ASSERT_FALSE(is_valid_email("user@.com"));         // . odmah posle @
    TEST_ASSERT_FALSE(is_valid_email("user@example."));     // završava se sa .
    TEST_ASSERT_FALSE(is_valid_email(""));                  // prazan
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_is_valid_account_number);
    RUN_TEST(test_is_valid_ssn);
    RUN_TEST(test_is_valid_branch_code);
    RUN_TEST(test_is_valid_phone_number);
    RUN_TEST(test_is_valid_email);
    return UNITY_END();
}
