#include "unity/unity.h"
#include "account_number.h"
#include <stdio.h>
#include <string.h>

#define TEST_CSV "test_accounts.csv"

#undef CSV_FILE
#define CSV_FILE TEST_CSV

void setUp(void) {
    FILE *file = fopen(TEST_CSV, "w");
    fputs("Name,Balance,AccountNumber\nJohn,100,12345678\nAlice,200,87654321\n", file);
    fclose(file);
}

void tearDown(void) {}

void test_account_exists_finds_existing_accounts(void) {
    TEST_ASSERT_TRUE(account_exists("12345678"));
    TEST_ASSERT_TRUE(account_exists("87654321"));
}

void test_account_exists_rejects_nonexisting_accounts(void) {
    TEST_ASSERT_FALSE(account_exists("00000000"));
    TEST_ASSERT_FALSE(account_exists("99999999"));
}

void test_generate_unique_account_number_returns_valid_number(void) {
    char *number = generate_unique_account_number();
    TEST_ASSERT_NOT_NULL(number);
    TEST_ASSERT_EQUAL_INT(8, strlen(number));
    TEST_ASSERT_NOT_EQUAL(0, strcmp(number, "00000000"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_account_exists_finds_existing_accounts);
    RUN_TEST(test_account_exists_rejects_nonexisting_accounts);
    RUN_TEST(test_generate_unique_account_number_returns_valid_number);
    return UNITY_END();
}
