#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "/unity/unity.h"
#include "../src/include/account_number.h"

#define TEST_CSV_FILE "tests/test_accounts.csv"

// Override the path from production for testing
#undef CSV_FILE
#define CSV_FILE TEST_CSV_FILE

// Declare the static function for test access
bool account_exists(const char *account_number);

// Utility: Create CSV for test
void create_test_csv(const char *content) {
    FILE *file = fopen(TEST_CSV_FILE, "w");
    fputs(content, file);
    fclose(file);
}

// === Test Functions ===

void test_account_exists(void) {
    create_test_csv("Name,Balance,AccountNumber\nJohn,100,12345678\nAlice,200,87654321\n");

    TEST_ASSERT_TRUE(account_exists("12345678"));
    TEST_ASSERT_TRUE(account_exists("87654321"));
    TEST_ASSERT_FALSE(account_exists("00000000"));
}

void test_generate_unique_account_number(void) {
    create_test_csv("Name,Balance,AccountNumber\nJohn,100,12345678\n");

    char *acc = generate_unique_account_number();
    TEST_ASSERT_NOT_NULL(acc);
    TEST_ASSERT_NOT_EQUAL(0, strcmp(acc, "00000000"));
    TEST_ASSERT_EQUAL_UINT(8, strlen(acc));
    free(acc); 
}

// === Unity Entry Point ===

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_account_exists);
    RUN_TEST(test_generate_unique_account_number);

    return UNITY_END();
}
