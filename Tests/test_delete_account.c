#include "unity/unity.h"
#include "src/logic/delete_account.h"
#include <stdio.h>
#include <string.h>

#define TEST_FILE "test_accounts_delete.csv"

void setUp(void) {
    FILE *file = fopen(TEST_FILE, "w");
    fputs("Name,Balance,AccountNumber\n"
          "John,100,12345678\n"
          "Alice,200,87654321\n", file);
    fclose(file);
}

void tearDown(void) {
    remove(TEST_FILE);
}

void test_delete_existing_account(void) {
    int result = delete_account(TEST_FILE, "12345678");
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

void test_delete_nonexistent_account(void) {
    int result = delete_account(TEST_FILE, "00000000");
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

void test_delete_with_invalid_file(void) {
    int result = delete_account("non_existing_file.csv", "12345678");
    TEST_ASSERT_EQUAL_INT(-1, result);  
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_delete_existing_account);
    RUN_TEST(test_delete_nonexistent_account);
    RUN_TEST(test_delete_with_invalid_file);
    return UNITY_END();
}
