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
