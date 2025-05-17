#include "../data/account_data.h"
#include "../data/transactions_db.h"
#include "src/logic/validations.h"
#include "bank_logic.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define ACCOUNT_CSV_PATH "../assets/accounts.csv"

int do_transaction(const char* account_number, const char* branch_code, int amount, const char type) {
    BankAccount account;

    if (get_account_by_account_number(account_number, &account) != 0)
        return -1;

    if (type == 'w') {
        if (account.balance < amount) {
            return -2; // Insufficient funds
        }
        account.balance -= amount;
    } else if (type == 'd')  // Invalid transaction type
    {
        account.balance += amount;
    }

    if (remove_account(&account) != 0) {
        return -3;
    }
    
    if (save_account_to_csv(ACCOUNT_CSV_PATH, &account) != 0) {
        return -4;
    }

    Transaction txn;
    strcpy(txn.account_number, account_number);
    strcpy(txn.branch_code, branch_code);
    txn.amount = amount;
    txn.balance_after = account.balance;
    txn.timestamp = time(NULL);

    if (type == 'd')
        strcpy(txn.type, "deposit");
    else if (type == 'w')
        strcpy(txn.type, "withdraw");
    
    store_transaction(&txn);

    return 0;
}
