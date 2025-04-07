#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include <stdbool.h>

typedef struct {
    char first_name[100];
    char last_name[100];
    char ssn[11];
    char address[100];
    char phone[100];
    char email[100];
    char account_type[100];
    double initial_balance;
    double overdraft_limit;
    char branch_code[3];
    char account_number[9];
} Account;

// Save account to a CSV file (used in testing)
int save_account_to_csv(const Account *acc, const char *file_path);

#endif
