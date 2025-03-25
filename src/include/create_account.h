#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include <stdbool.h>

// Creates a new bank account by prompting the user for required fields,
// validates input until correct values are entered, and saves the data in CSV with header:
// FirstName,LastName,SSN,Address,phone,email,accountType,initialBalance,OverdraftLimit,BranchCode,AccountNumber.
void create_bank_account(void);

#endif // CREATE_ACCOUNT_H
