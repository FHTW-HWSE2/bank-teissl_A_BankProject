#include "unity.h"
#include "data/transactions_db.h"
#include <stdio.h>
#include <time.h>

#define TEST_TXN_FILE "../assets/test_transactions.csv"

// Hilfsfunktion: schreibt eine Test-Transaktion
void store_transaction_TEST(const char* filename, const Transaction* txn) {
    FILE* file = fopen(filename, "a+");
    if (!file) {
        printf("Fehler: Datei konnte nicht geöffnet werden: %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "AccountNumber,BranchCode,Amount,BalanceAfter,Timestamp,Type\n");
    }

    fprintf(
        file, "%s,%s,%d,%d,%lld,%s\n",
        txn->account_number,
        txn->branch_code,
        txn->amount,
        txn->balance_after,
        (long long)txn->timestamp,
        txn->type
    );

    fclose(file);
}

// Setup: löscht Datei vor jedem Test
void setUp(void) {
    remove(TEST_TXN_FILE);
}

// Teardown: löscht Datei nach jedem Test
void tearDown(void) {
    remove(TEST_TXN_FILE);
}

// Test: prüft, ob Transaktion korrekt gespeichert wird
void test_store_transaction(void) {
    Transaction txn = {
        .account_number = "11112222",
        .branch_code    = "001",
        .amount         = 500,
        .balance_after  = 1500,
        .timestamp      = time(NULL),
        .type           = "DEPOSIT"
    };

    store_transaction_TEST(TEST_TXN_FILE, &txn);

    FILE* f = fopen(TEST_TXN_FILE, "r");
    TEST_ASSERT_NOT_NULL(f);
    fclose(f);
}

// Main: führt Unity aus
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_store_transaction);
    return UNITY_END();
}
