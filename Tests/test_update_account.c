#include "unity/src/unity.h"
#include "src/logic/update_account.h"
#include "src/data/account_data.h"
#include <stdio.h>
#include <string.h>

#define TEST_FILE "test_accounts_update.csv"

void setUp(void) {
    FILE *file = fopen(TEST_FILE, "w");
    fputs("FirstName,LastName,SSN,Address,Phone,Email,BranchCode,AccountNumber\n"
          "John,Doe,123456789,123 Street,123-4567,john@example.com,001,11112222\n"
          "Jane,Smith,987654321,456 Avenue,987-6543,jane@example.com,002,33334444\n", file);
    fclose(file);
}

void tearDown(void) {
    remove(TEST_FILE);
}

void test_update_existing_account(void) {
    BankAccount updated = {
        .first_name = "JohnUpdated",
        .last_name = "DoeUpdated",
        .ssn = "123456789",
        .address = "New Address",
        .phone = "000-0000",
        .email = "john@updated.com",
        .branch_code = "003",
        .account_number = "11112222"
    };

    int result = update_account(TEST_FILE, &updated);
    TEST_ASSERT_EQUAL_INT(1, result);

    FILE *file = fopen(TEST_FILE, "r");
    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "JohnUpdated") && strstr(line, "DoeUpdated") && strstr(line, "11112222")) {
            found = 1;
            break;
        }
    }
    fclose(file);
    TEST_ASSERT_TRUE(found);
}

void test_update_nonexistent_account(void) {
    BankAccount updated = {
        .first_name = "Ghost",
        .last_name = "User",
        .ssn = "000000000",
        .address = "Nowhere",
        .phone = "000-0000",
        .email = "ghost@none.com",
        .branch_code = "999",
        .account_number = "99999999"
    };

    int result = update_account(TEST_FILE, &updated);
    TEST_ASSERT_EQUAL_INT(0, result);  // Pretpostavljamo da vraca 0 ako nalog ne postoji
}

void test_update_with_invalid_file(void) {
    BankAccount dummy = {
        .first_name = "Test",
        .last_name = "User",
        .account_number = "00000000"
    };

    int result = update_account("non_existing_file.csv", &dummy);
    TEST_ASSERT_EQUAL_INT(-1, result);  // Pretpostavljamo -1 kod greške
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_update_existing_account);
    RUN_TEST(test_update_nonexistent_account);
    RUN_TEST(test_update_with_invalid_file);
    return UNITY_END();
}
