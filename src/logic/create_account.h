#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include "controller.h"

// Core logic function to create and save an account
int create_account_logic();

// Allows UI input to fill in account fields
void start_account_creation_ui(BankAccount *account);

// Generates a unique 8-digit account number
char* generate_unique_account_number(void);

#endif
