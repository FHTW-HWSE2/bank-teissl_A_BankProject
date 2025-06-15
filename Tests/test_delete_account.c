/**
 * @file test_delete_account.c
 * @brief Unit tests for the delete_account logic using the Unity framework.
 *
 * This test suite validates account deletion behavior from a CSV file,
 * including deletion of existing accounts, handling of non-existent accounts,
 * and behavior when the file is invalid.
 */

#include "unity/unity.h"
#include "src/logic/delete_account.h"
#include <stdio.h>
#include <string.h>

#define TEST_FILE "test_accounts_delete.csv"

/**
 * @brief Setup function run before each test.
 *
 * Creates a test CSV file with two account entries and a header line.
 */
void setUp(void) {
    FILE *file = fopen(TEST_FILE, "w");
    fputs("Name,Balance,AccountNumber\nJohn,100,12345678\nAlice,200,87654321\n", file);
    fclose(file);
}

/**
 * @brief Teardown function run after each test.
 *
 * Removes the test CSV file to reset the test environment.
 */
void tearDown(void) {
    remove(TEST_FILE);
}

/**
 * @test Verifies that an existing account can be deleted.
 *
 * The test deletes account number "12345678" and confirms
 * that it no longer exists in the file afterward.
 */
void test_delete_existing_account(void) {
    int result = delete_account("12345678");
    TEST_ASSERT_EQUAL_INT(1, result);

    FILE *file = fopen(TEST_FILE, "r");
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "12345678")) {
            found = 1;
            break;
        }
    }
    fclose(file);
    TEST_ASSERT_EQUAL_INT(0, found);
}

/**
 * @test Verifies that trying to delete a non-existent account has no effect.
 *
 * The CSV file should remain unchanged, and the function should return 0.
 */
void test_delete_nonexistent_account(void) {
    int result = delete_account("00000000");
    TEST_ASSERT_EQUAL_INT(0, result);

    FILE *file = fopen(TEST_FILE, "r");
    char line[256];
    int line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        line_count++;
    }
    fclose(file);
    TEST_ASSERT_EQUAL_INT(3, line_count);  // header + 2 accounts
}

/**
 * @test Verifies that deleting an account fails gracefully if the file is invalid.
 *
 * This test assumes the file is missing or corrupt and expects a return value of -1.
 * To simulate this, you may need to temporarily rename or remove the file before the test.
 */
void test_delete_with_invalid_file(void) {
    remove(TEST_FILE);  // Simulate missing file
    int result = delete_account("12345678");
    TEST_ASSERT_EQUAL_INT(-1, result);  
}

/**
 * @brief Main test runner function.
 *
 * Runs all unit tests for account deletion functionality.
 *
 * @return int Unity test framework result code.
 */
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_delete_existing_account);
    RUN_TEST(test_delete_nonexistent_account);
    RUN_TEST(test_delete_with_invalid_file);
    return UNITY_END();
}
