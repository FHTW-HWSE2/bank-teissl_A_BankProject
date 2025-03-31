#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/account_number.h"

#define TEST_CSV_FILE "tests/test_accounts.csv"

// Override the path from production for testing
#undef CSV_FILE
#define CSV_FILE TEST_CSV_FILE

// Declare the static function for test access
bool account_exists(const char *account_number);

void create_test_csv(const char *content) {
    FILE *file = fopen(TEST_CSV_FILE, "w");
    fputs(content, file);
    fclose(file);
}

void test_account_exists() {
    create_test_csv("Name,Balance,AccountNumber\nJohn,100,12345678\nAlice,200,87654321\n");

    assert(account_exists("12345678") == true);
    assert(account_exists("87654321") == true);
    assert(account_exists("00000000") == false);

    printf("✅ test_account_exists passed\n");
}

void test_generate_unique_account_number() {
    create_test_csv("Name,Balance,AccountNumber\nJohn,100,12345678\n");

    char *acc = generate_unique_account_number();
    assert(strcmp(acc, "00000000") != 0);
    assert(strlen(acc) == 8);
    printf("✅ test_generate_unique_account_number passed: %s\n", acc);
}

int main() {
    test_account_exists();
    test_generate_unique_account_number();
    printf("🎉 All tests passed!\n");
    return 0;
}

