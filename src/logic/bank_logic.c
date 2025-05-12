#include "../data/account_data.h"
#include "../data/transactions_db.h"
#include "bank_logic.h"
#include <string.h>
#include <stdio.h>

#define ACCOUNT_CSV_PATH "../assets/accounts.csv"


int deposit_funds(const char* account_number, const char* branch_code, int amount) {
    // Find account
    BankAccount account;
    if (get_account_by_account_number(account_number, &account) != 0) {
        printf("**********%s*********\n", account_number); // Debugging
        return -1;
    }

    // Update balance in account structure
    account.balance += amount;

    if (remove_account(&account) != 0) {
        return -2;
    }

    save_account_to_csv(ACCOUNT_CSV_PATH, &account);

    Transaction txn;
    strcpy(txn.account_number, account_number);
    strcpy(txn.branch_code, branch_code);
    txn.amount = amount;
    txn.balance_after = account.balance;
    txn.timestamp = time(NULL);
    strcpy(txn.type, "deposit");

    store_transaction(&txn);

    return 0;
}
