#ifndef ACCOUNT_DATA_H
#define ACCOUNT_DATA_H

#include "src/logic/create_account.h"
#include <stdbool.h>

// Check if an account number already exists in the CSV file
bool account_exists(const char *account_number);

// Save account info to the CSV file
void save_account_to_csv(const BankAccount *account);

#endif // ACCOUNT_DATA_H
