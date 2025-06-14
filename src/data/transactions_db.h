#ifndef TRANSACTIONS_DB_H
#define TRANSACTIONS_DB_H

#include <time.h>

// Transaction struct definition
typedef struct {
    char account_number[20];
    char branch_code[10];
    int amount;
    int balance_after;
    time_t timestamp;
    char type[10]; // e.g. "deposit"
} Transaction;

// Function declarations
void store_transaction(const Transaction* txn);

#endif // TRANSACTIONS_DB_H
