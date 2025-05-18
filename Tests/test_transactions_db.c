#include "unity/src/unity.h"
#include "src/data/transactions_db.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEST_FILE "test_transactions.csv"

// Override default macro in test mode
#undef TRANSACTIONS_FILE
#define TRANSACTIONS_FILE TEST_FILE

void setUp(void) {
    FILE *file = fopen(TEST_FILE, "w");
    if (file) fclose(file);
}

void tearDown(void) {
    remove(TEST_FILE);
}

void test_store_transaction_creates_file_and_writes_data(void) {
    Transaction txn = {
        .account_number = "11112222",
        .branch_code = "B1",
        .amount = 1500,
        .balance_after = 5000,
        .timestamp = 1716123456,  // Simulirani timestamp
        .type = "DEPOSIT"
    };

    store_transaction(&txn);

    FILE *file = fopen(TEST_FILE, "r");
    TEST_ASSERT_NOT_NULL(file);

    char line[512];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "11112222") && strstr(line, "DEPOSIT") && strstr(line, "1500")) {
            found = 1;
            break;
        }
    }

    fclose(file);
    TEST_ASSERT_TRUE(found);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_store_transaction_creates_file_and_writes_data);
    return UNITY_END();
}
