/**
 * @file test_report_logic.c
 * @brief Unit tests for report generation logic using Unity framework.
 *
 * This test suite verifies the correctness of generated reports,
 * including total money, active account count, detailed account listings,
 * and error handling for invalid report types.
 */

#include "unity/unity.h"
#include "src/data/report_data.h"
#include <string.h>
#include <stdio.h>

#define TEST_CSV "test_accounts_data.csv"

/**
 * @brief Setup function called before each test.
 *
 * Creates a temporary CSV file containing two sample accounts,
 * which will be used by the report generation logic.
 */
void setUp(void) {
    FILE *file = fopen(TEST_CSV, "w");
    fputs("FirstName,LastName,SSN,Address,phone,email,BranchCode,Balance,AccountNumber\n", file);
    fputs("John,Doe,1234567890,123 St,555-5555,john@example.com,B1,1000,00000001\n", file);
    fputs("Alice,Smith,9876543210,456 Ave,555-6666,alice@example.com,B2,2000,00000002\n", file);
    fclose(file);
}

/**
 * @brief Teardown function called after each test.
 *
 * Deletes the temporary test CSV file created during setup.
 */
void tearDown(void) {
    remove(TEST_CSV);
}

/**
 * @test Verifies that the "total_money" report correctly sums account balances.
 *
 * Expected output: "Total Money in Bank: 3000.00"
 */
void test_total_money_report(void) {
    Report report;
    int result = fetch_report_data("total_money", &report);

    printf("Report data: %s\n", report.data);  // Debug output

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_TRUE(strstr(report.data, "Total Money in Bank: 3000.00") != NULL);
}

/**
 * @test Verifies that the "active_accounts" report returns the correct count.
 *
 * Expected output: "Number of Active Accounts: 2"
 */
void test_active_accounts_report(void) {
    Report report;
    int result = fetch_report_data("active_accounts", &report);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_TRUE(strstr(report.data, "Number of Active Accounts: 2") != NULL);
}

/**
 * @test Verifies that the "account_details" report includes both sample accounts.
 */
void test_account_details_report(void) {
    Report report;
    int result = fetch_report_data("account_details", &report);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_TRUE(strstr(report.data, "Name: John Doe") != NULL);
    TEST_ASSERT_TRUE(strstr(report.data, "Name: Alice Smith") != NULL);
}

/**
 * @test Verifies that an invalid report type results in an appropriate error message.
 *
 * Expected output: "Invalid report type"
 */
void test_invalid_report_type(void) {
    Report report;
    int result = fetch_report_data("invalid_type", &report);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_TRUE(strstr(report.data, "Invalid report type") != NULL);
}

/**
 * @brief Unity test runner.
 *
 * Executes all test cases defined in this test suite.
 *
 * @return int Unity return code.
 */
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_total_money_report);
    RUN_TEST(test_active_accounts_report);
    RUN_TEST(test_account_details_report);
    RUN_TEST(test_invalid_report_type);
    return UNITY_END();
}
