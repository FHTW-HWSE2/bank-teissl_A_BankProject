#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H



#define MAX_STRING_LENGTH 100
typedef struct {
    char account_number[9];
    char first_name[50];
    char last_name[50];
    char address[100];
    char phone[20];
    char email[100];
    char ssn[11];
    char branch_code[3];
    double balance;
} BankAccount;

void create_account_logic(void);
char* generate_unique_account_number(void);
void start_account_creation_ui(BankAccount *account);
int is_valid_ssn(const char *ssn);
int is_valid_branch_code(const char *branch_code);

#endif
