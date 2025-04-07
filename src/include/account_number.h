#ifndef ACCOUNT_NUMBER_H
#define ACCOUNT_NUMBER_H

#include <stdbool.h>

// Returns an 8-digit unique account number that is not "00000000"
// and does not exist yet in the CSV file.
char* generate_unique_account_number(void);

// Checks if the given account number exists in the CSV file.
bool account_exists(const char *account_number);

#endif // ACCOUNT_NUMBER_H
