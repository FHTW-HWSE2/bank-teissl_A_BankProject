#ifndef CONTROLLER_H
#define CONTROLLER_H

#define MAX_STRING_LENGTH 100

typedef struct {
    char first_name[MAX_STRING_LENGTH];
    char last_name[MAX_STRING_LENGTH];
    char ssn[11];
    char address[MAX_STRING_LENGTH];
    char phone[MAX_STRING_LENGTH];
    char email[MAX_STRING_LENGTH];
    char branch_code[3];
    unsigned long balance;  // balance stored in cents (e.g., 1050 = €10.50) Double has error with math
    char account_number[9];
} BankAccount;

void start();

#endif
