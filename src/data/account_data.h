#ifndef ACCOUNT_DATA_H
#define ACCOUNT_DATA_H

#include "src/logic/create_account.h"
#include <stdbool.h>

// Check if an account number already exists in the CSV file
bool account_exists(const char *filename, const char *account_number);

// Save account info to the CSV file
int save_account_to_csv(const char *filename, const BankAccount *account);

int get_account_by_id(BankAccount *account);

int remove_account(const char *account_number);

#endif // ACCOUNT_DATA_H
