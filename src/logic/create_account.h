#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#define MAX_STRING_LENGTH 100

typedef struct {
    char first_name[MAX_STRING_LENGTH];
    char last_name[MAX_STRING_LENGTH];
    char ssn[11];
    char address[MAX_STRING_LENGTH];
    char phone[MAX_STRING_LENGTH];
    char email[MAX_STRING_LENGTH];
    double initial_balance;
    double overdraft_limit;
    char branch_code[3];
    char account_number[9];
} BankAccount;

// Core logic function to create and save an account
void create_account_logic(void);

// Allows UI input to fill in account fields
void start_account_creation_ui(BankAccount *account);

// Generates a unique 8-digit account number
char* generate_unique_account_number(void);

// Validation functions
int is_valid_ssn(const char *ssn);
int is_valid_branch_code(const char *branch_code);

#endif // CREATE_ACCOUNT_H
