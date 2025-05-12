#include "src/data/account_data.h"
#include "src/data/transactions_db.h"
#include "src/logic/bank_logic.h"
#include <string.h>
#include <stdio.h>

#define ACCOUNT_CSV_PATH "../assets/accounts.csv"

int withdraw_funds(const char *account_number, const char *branch_code, int amount)
{
    if (amount <= 0 || amount % 1 != 0)
    {
        // printf("Invalid withdrawal amount.\n");
        return -1;
    }

    if (strcmp(branch_code, "B1") != 0 && strcmp(branch_code, "B2") != 0)
    {
        // printf("Invalid branch code.\n");
        return -2;
    }

    BankAccount account;
    if (get_account_by_account_number(account_number, &account) != 0)
    {
        // printf("Account does not exist.\n");
        return -3;
    }

    account.balance -= amount;

    if (remove_account(&account) != 0)
    {
        return -2;
    }

    save_account_to_csv(ACCOUNT_CSV_PATH, &account);

    Transaction txn;
    strcpy(txn.account_number, account_number);
    strcpy(txn.branch_code, branch_code);
    txn.amount = -amount;
    txn.balance_after = account.balance;
    txn.timestamp = time(NULL);
    strcpy(txn.type, "withdraw");

    store_transaction(&txn);

    return 0;
}