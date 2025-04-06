#ifndef ACCOUNT_DATA_H
#define ACCOUNT_DATA_H

char* generate_unique_account_number(void);
void save_account_to_csv(
    const char *first,
    const char *last,
    const char *ssn,
    const char *address,
    const char *phone,
    const char *email,
    const char *type,
    double balance,
    double overdraft,
    const char *branch,
    const char *account_number);

#endif