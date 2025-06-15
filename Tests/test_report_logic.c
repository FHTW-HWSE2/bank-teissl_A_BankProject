#include "unity/unity.h"
#include "src/data/report_data.h"
#include <string.h>
#include <stdio.h>

#define TEST_CSV "test_accounts_data.csv"

void setUp(void) {
    // Setup a small test accounts CSV file
    FILE *file = fopen(TEST_CSV, "w");
    fputs("FirstName,LastName,SSN,Address,phone,email,BranchCode,Balance,AccountNumber\n", file);
    fputs("John,Doe,1234567890,123 St,555-5555,john@example.com,B1,1000,00000001\n", file);
    fputs("Alice,Smith,9876543210,456 Ave,555-6666,alice@example.com,B2,2000,00000002\n", file);
    fclose(file);
}

void tearDown(void) {
    remove(TEST_CSV);
}

void test_total_money_report(void) {
    Report report;
    int result = fetch_report_data(TEST_CSV, "total_money", &report);

    printf("Report data: %s\n", report.data);  // Debug output

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_TRUE(strstr(report.data, "Total Money in Bank: 3000.00") != NULL);
}


void test_active_accounts_report(void) {
    Report report;
    int result = fetch_report_data(TEST_CSV, "active_accounts", &report);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_TRUE(strstr(report.data, "Number of Active Accounts: 2") != NULL);
}

void test_account_details_report(void) {
    Report report;
    int result = fetch_report_data(TEST_CSV, "account_details", &report);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_TRUE(strstr(report.data, "Name: John Doe") != NULL);
    TEST_ASSERT_TRUE(strstr(report.data, "Name: Alice Smith") != NULL);
}

void test_invalid_report_type(void) {
    Report report;
    int result = fetch_report_data(TEST_CSV, "invalid_type", &report);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_TRUE(strstr(report.data, "Invalid report type") != NULL);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_total_money_report);
    RUN_TEST(test_active_accounts_report);
    RUN_TEST(test_account_details_report);
    RUN_TEST(test_invalid_report_type);
    return UNITY_END();
}
