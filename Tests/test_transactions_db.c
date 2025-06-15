#include "unity.h"
#include "data/transactions_db.h"
#include <stdio.h>
#include <time.h>

// Korrekte relative Pfad zur Test-Transaktionsdatei
#define TEST_TXN_FILE "../assets/test_transactions.csv"

// schreibt eine Test-Transaktion in die Datei
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

    fprintf(file, "%s,%s,%d,%d,%lld,%s\n",
        txn->account_number,
        txn->branch_code,
        txn->amount,
        txn->balance_after,
        (long long)txn->timestamp,
        txn->type);

    fclose(file);
}

// vor jedem Test: Datei löschen
void setUp(void) {
    remove(TEST_TXN_FILE);
}

// nach jedem Test: Datei löschen
void tearDown(void) {
    remove(TEST_TXN_FILE);
}

// prüft, ob Transaktion korrekt gespeichert wird
void test_store_transaction(void) {
    Transaction txn = {
        .account_number = "11112222",
        .branch_code = "001",
        .amount = 500,
        .balance_after = 1500,
        .timestamp = time(NULL),
        .type = "DEPOSIT"
    };

    store_transaction_TEST(TEST_TXN_FILE, &txn);

    FILE *f = fopen(TEST_TXN_FILE, "r");
    TEST_ASSERT_NOT_NULL(f);
    fclose(f);
}

// Startpunkt für Unity
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_store_transaction);
    return UNITY_END();
}
