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

    if (get_account_by_account_number(ACCOUNT_CSV_PATH, account_number, &account) != 0)
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

    if (remove_account(ACCOUNT_CSV_PATH, &account) != 0) {
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

int transfer_funds(const char* from_account, const char* to_account, int amount) {

    BankAccount sender, receiver;

    if (get_account_by_account_number(ACCOUNT_CSV_PATH, from_account, &sender) != 0) {
        return -1;
    }

    if (get_account_by_account_number(ACCOUNT_CSV_PATH, to_account, &receiver) != 0) {
        return -2;
    }

    if (amount > sender.balance) {
        return -3;
    }

    // Withdraw from sender
    sender.balance -= amount;
    receiver.balance += amount;

    if (remove_account(ACCOUNT_CSV_PATH, &sender) != 0) {
        return -4;
    }

    if (save_account_to_csv(ACCOUNT_CSV_PATH, &sender) != 0) {
        return -5;
    }

    if (remove_account(ACCOUNT_CSV_PATH, &receiver) != 0) {
        return -6;
    }
    
    if (save_account_to_csv(ACCOUNT_CSV_PATH, &receiver) != 0) {
        return -7;
    }

    Transaction sender_txn;
    strcpy(sender_txn.account_number, from_account);
    strcpy(sender_txn.branch_code, sender.branch_code);
    sender_txn.amount = -amount;
    sender_txn.balance_after = sender.balance;
    sender_txn.timestamp = time(NULL);
    strcpy(sender_txn.type, "transfer-out");
    store_transaction(&sender_txn);

    Transaction receiver_txn;
    strcpy(receiver_txn.account_number, to_account);
    strcpy(receiver_txn.branch_code, receiver.branch_code);
    receiver_txn.amount = amount;
    receiver_txn.balance_after = receiver.balance;
    receiver_txn.timestamp = time(NULL);
    strcpy(receiver_txn.type, "transfer-in");
    store_transaction(&receiver_txn);

    return 0;
}