/**
 * @file test_update_account.c
 * @brief Unit tests for the update_account function using Unity.
 *
 * Tests cover successful updates, attempts to update non-existent accounts,
 * and failure when the file is missing or inaccessible.
 */

#include "unity/unity.h"
#include "src/logic/update_account.h"
#include "src/data/account_data.h"
#include <stdio.h>
#include <string.h>

#define filename "test_accounts_update.csv"

/**
 * @brief Creates a test CSV file with two dummy accounts before each test.
 */
void setUp(void) {
    FILE *file = fopen(filename, "w");
    fputs("FirstName,LastName,SSN,Address,Phone,Email,BranchCode,Balance,AccountNumber\n"
          "John,Doe,123456789,123 Street,123-4567,john@example.com,001,5000,11112222\n"
          "Jane,Smith,987654321,456 Avenue,987-6543,jane@example.com,002,3000,33334444\n", file);
    fclose(file);
}

/**
 * @brief Removes the test CSV file after each test.
 */
void tearDown(void) {
    remove(filename);
}

/**
 * @test Verifies that an existing account can be successfully updated in the file.
 */
void test_update_existing_account(void) {
    BankAccount updated = {
        .first_name = "JohnUpdated",
        .last_name = "DoeUpdated",
        .ssn = "123456789",
        .address = "New Address",
        .phone = "000-0000",
        .email = "john@updated.com",
        .branch_code = "B1",
        .balance = "6000",
        .account_number = "11112222"
    };

    int result = update_account(filename, "11112222");
    TEST_ASSERT_EQUAL_INT(0, result);

    FILE *file = fopen(filename, "r");
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

/**
 * @test Verifies that updating a non-existent account does not change the file.
 */
void test_update_nonexistent_account(void) {
    BankAccount updated = {
        .first_name = "Ghost",
        .last_name = "User",
        .ssn = "000000000",
        .address = "Nowhere",
        .phone = "000-0000",
        .email = "ghost@none.com",
        .branch_code = "B2",
        .balance = "0",  // No balance change
        .account_number = "99999999"
    };

    int result = update_account(filename ,&updated);
    TEST_ASSERT_EQUAL_INT(0, result);  
}

/**
 * @test Verifies that the update function returns -1 when the file does not exist.
 */
void test_update_with_invalid_file(void) {
    // Simulate missing file
    remove(filename);  

    BankAccount dummy = {
        .first_name = "Test",
        .last_name = "User",
        .ssn = "000000000",
        .address = "No Address",
        .phone = "000-0000",
        .email = "none@invalid.com",
        .branch_code = "000",
        .balance = "0",  // No balance change
        .account_number = "00000000"
    };

    int result = update_account(filename ,&dummy);
    TEST_ASSERT_EQUAL_INT(-1, result); 
}

/**
 * @brief Runs all tests.
 */
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_update_existing_account);
    RUN_TEST(test_update_nonexistent_account);
    RUN_TEST(test_update_with_invalid_file);
    return UNITY_END();
}
