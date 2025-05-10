#include "../data/account_data.h"
#include "../data/transactions_db.h"
#include "bank_logic.h"
#include <string.h>
#include <stdio.h>

void deposit_funds(const char* account_number, const char* branch_code, int amount) {
    // Check that the amount is in whole cents and greater than 0
    if (amount <= 0 || amount % 1 != 0) {
        printf("Invalid deposit amount.\n");
        return;
    }

    // Check that the branch code is valid
    if (strcmp(branch_code, "B1") != 0 && strcmp(branch_code, "B2") != 0) {
        printf("Invalid branch code.\n");
        return;
    }

    // Find account
    BankAccount account;
    if (!get_account_by_account_number(account_number, &account)) {
        printf("Account does not exist.\n");
        return;
    }

    // Get current balance from transactions
    int current_balance = get_latest_balance(account_number);

    // Calculate new balance
    int new_balance = current_balance + amount;

    // Update balance in account structure
    account.balance = new_balance;
    update_account_balance(account.account_number, account.balance);


    // Create and store transaction
    Transaction txn;
    strcpy(txn.account_number, account_number);
    strcpy(txn.branch_code, branch_code);
    txn.amount = amount;
    txn.balance_after = new_balance;
    txn.timestamp = time(NULL);
    strcpy(txn.type, "deposit");

    store_transaction(&txn);

    printf("Deposit successful. New balance: %d\n", new_balance);
}
