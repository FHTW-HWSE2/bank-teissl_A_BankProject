#ifndef ACCOUNT_DATA_H
#define ACCOUNT_DATA_H
#include <stdbool.h>

#define MAX_STRING_LENGTH 100

typedef struct {
    char first_name[MAX_STRING_LENGTH];
    char last_name[MAX_STRING_LENGTH];
    char ssn[11];
    char address[MAX_STRING_LENGTH];
    char phone[MAX_STRING_LENGTH];
    char email[MAX_STRING_LENGTH];
    char account_type[MAX_STRING_LENGTH];
    double initial_balance;
    double overdraft_limit;
    char branch_code[3];
    char account_number[9];
} BankAccount;

void save_account_to_csv(const BankAccount *account);
bool account_exists(const char *account_number);

#endif
