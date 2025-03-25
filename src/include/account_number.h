#ifndef ACCOUNT_NUMBER_H
#define ACCOUNT_NUMBER_H

#include <stdbool.h>

// Generates an 8-digit unique account number (rejecting "00000000")
// by checking against the CSV file (../assets/accounts.csv).
char* generate_unique_account_number(void);

#endif // ACCOUNT_NUMBER_H
