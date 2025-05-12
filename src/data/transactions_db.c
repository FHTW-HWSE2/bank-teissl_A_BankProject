#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../data/transactions_db.h"

#define TRANSACTIONS_FILE "../assets/transactions.csv"

void store_transaction(const Transaction* txn) {
    FILE* file = fopen(TRANSACTIONS_FILE, "a+");
    if (!file) {
        printf("Error: Unable to open transactions file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        // Write header
        fprintf(file, "AccountNumber,BranchCode,Amount,BalanceAfter,Timestamp,Type\n");
    }

    fprintf(file, "%s,%s,%d,%d,%ld,%s\n",
            txn->account_number,
            txn->branch_code,
            txn->amount,
            txn->balance_after,
            (long long)txn->timestamp,
            txn->type);

    fclose(file);
}

int get_latest_balance(const char* account_number) {
    FILE* file = fopen(TRANSACTIONS_FILE, "r");
    if (!file) return 0; // If no file, assume zero balance

    char line[256];
    fgets(line, sizeof(line), file); // skip header

    int latest_balance = 0;
    while (fgets(line, sizeof(line), file)) {
        Transaction txn;
        sscanf(line, "%[^,],%*[^,],%*d,%d,%*ld,%*s",
               txn.account_number, &txn.balance_after);

        if (strcmp(txn.account_number, account_number) == 0) {
            latest_balance = txn.balance_after;
        }
    }

    fclose(file);
    return latest_balance;
}
