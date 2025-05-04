#include "unity/src/unity.h"
#include "src/data/account_data.h"
#include <stdio.h>
#include <string.h>

#define TEST_CSV "test_accounts_output.csv"

void setUp(void) {
    // clear the file before each test
    FILE *file = fopen(TEST_CSV, "w");
    if (file) fclose(file);
}

void tearDown(void) {
    remove(TEST_CSV); // Optional: Delete after test if you want
}

void test_save_account_to_csv_creates_file_and_writes_data(void) {
    BankAccount account = {
        .first_name = "John",
        .last_name = "Doe",
        .ssn = "123456789",
        .address = "123 Main St",
        .phone = "555-1234",
        .email = "john@example.com",
        .branch_code = "001",
        .account_number = "98765432"
    };

    save_account_to_csv(TEST_CSV, &account);

    FILE *file = fopen(TEST_CSV, "r");
    TEST_ASSERT_NOT_NULL(file);

    char line[512];
    int found_data = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "John") && strstr(line, "Doe") && strstr(line, "98765432")) {
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
