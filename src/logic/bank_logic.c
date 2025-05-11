#include "../data/account_data.h"
#include "../data/transactions_db.h"
#include "bank_logic.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

void deposit_funds(const char* account_number, const char* branch_code, int amount) {
    if (amount <= 0) {
        printf("Invalid deposit amount.\n");
        return;
    }

    if (strcmp(branch_code, "B1") != 0 && strcmp(branch_code, "B2") != 0) {
        printf("Invalid branch code.\n");
        return;
    }

    BankAccount account;
    if (get_account_by_account_number(account_number, &account) != 0) {
        printf("Account does not exist.\n");
        return;
    }

    int current_balance = get_latest_balance(account_number);
    int new_balance = current_balance + amount;
    account.balance = new_balance;
    update_account_balance(account.account_number, account.balance);

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

void withdraw_funds(const char* account_number, const char* branch_code, int amount) {
    if (amount <= 0) {
        printf("Invalid withdrawal amount.\n");
        return;
    }

    if (strcmp(branch_code, "B1") != 0 && strcmp(branch_code, "B2") != 0) {
        printf("Invalid branch code.\n");
        return;
    }

    BankAccount account;
    if (get_account_by_account_number(account_number, &account) != 0) {
        printf("Account does not exist.\n");
        return;
    }

    int current_balance = get_latest_balance(account_number);
    if (amount > current_balance) {
        printf("Insufficient funds.\n");
        return;
    }

    int new_balance = current_balance - amount;
    account.balance = new_balance;
    update_account_balance(account.account_number, account.balance);

    Transaction txn;
    strcpy(txn.account_number, account_number);
    strcpy(txn.branch_code, branch_code);
    txn.amount = -amount;
    txn.balance_after = new_balance;
    txn.timestamp = time(NULL);
    strcpy(txn.type, "withdraw");

    store_transaction(&txn);
    printf("Withdrawal successful. New balance: %d\n", new_balance);
}

void transfer_funds(const char* from_account, const char* to_account, int amount) {
    if (amount <= 0) {
        printf("Invalid transfer amount.\n");
        return;
    }

    BankAccount sender, receiver;
    if (get_account_by_account_number(from_account, &sender) != 0) {
        printf("Sender account does not exist.\n");
        return;
    }

    if (get_account_by_account_number(to_account, &receiver) != 0) {
        printf("Receiver account does not exist.\n");
        return;
    }

    int sender_balance = get_latest_balance(from_account);
    if (amount > sender_balance) {
        printf("Insufficient funds in sender's account.\n");
        return;
    }

    // Withdraw from sender
    int new_sender_balance = sender_balance - amount;
    sender.balance = new_sender_balance;
    update_account_balance(sender.account_number, sender.balance);

    Transaction sender_txn;
    strcpy(sender_txn.account_number, from_account);
    strcpy(sender_txn.branch_code, sender.branch_code);
    sender_txn.amount = -amount;
    sender_txn.balance_after = new_sender_balance;
    sender_txn.timestamp = time(NULL);
    strcpy(sender_txn.type, "transfer-out");
    store_transaction(&sender_txn);

    // Deposit to receiver
    int receiver_balance = get_latest_balance(to_account);
    int new_receiver_balance = receiver_balance + amount;
    receiver.balance = new_receiver_balance;
    update_account_balance(receiver.account_number, receiver.balance);

    Transaction receiver_txn;
    strcpy(receiver_txn.account_number, to_account);
    strcpy(receiver_txn.branch_code, receiver.branch_code);
    receiver_txn.amount = amount;
    receiver_txn.balance_after = new_receiver_balance;
    receiver_txn.timestamp = time(NULL);
    strcpy(receiver_txn.type, "transfer-in");
    store_transaction(&receiver_txn);

    printf("Transfer successful.\n");
}
