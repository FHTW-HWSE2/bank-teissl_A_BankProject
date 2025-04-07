#include "unity/unity.h"
#include "create_account.h"
#include <stdio.h>
#include <string.h>

#define TEST_CSV "test_accounts_output.csv"

void setUp(void) {
    // clear the file before each test
    FILE *file = fopen(TEST_CSV, "w");
    if (file) fclose(file);
}

void tearDown(void) {}

void test_save_account_to_csv_creates_file_and_writes_data(void) {
    Account acc = {
        "Alice", "Smith", "1234567890", "123 Lane", "555-1234", "alice@test.com",
        "Standard", 0.0, 0.0, "B1", "12345678"
    };

    int result = save_account_to_csv(&acc, TEST_CSV);
    TEST_ASSERT_EQUAL_INT(0, result);

    FILE *file = fopen(TEST_CSV, "r");
    TEST_ASSERT_NOT_NULL(file);

    char line[512];
    int found_data = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Alice") && strstr(line, "Smith") && strstr(line, "12345678")) {
            found_data = 1;
            break;
        }
    }

    fclose(file);
    TEST_ASSERT_TRUE(found_data);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_save_account_to_csv_creates_file_and_writes_data);
    return UNITY_END();
}
