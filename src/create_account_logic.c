#include "include/create_account_logic.h"
#include "include/account_data.h"
#include <stdio.h>
#include <string.h>

void create_account_logic(
    const char *first,
    const char *last,
    const char *ssn,
    const char *address,
    const char *phone,
    const char *email,
    const char *type,
    double balance,
    double overdraft,
    const char *branch
) {
    char *account_number = generate_unique_account_number();
    save_account_to_csv(first, last, ssn, address, phone, email, type, balance, overdraft, branch, account_number);

    printf("\nAccount created successfully!\n");
    printf("Account holder: %s %s\n", first, last);
    printf("Account type: %s\n", type);
    if (strcmp(type, "Initial balance") == 0) printf("Initial balance: %.2f\n", balance);
    if (strcmp(type, "Overdraft limit") == 0) printf("Overdraft limit: %.2f\n", overdraft);
    printf("SSN: %s\n", ssn);
    printf("Account number: %s\n", account_number);
    printf("Branch code: %s\n", branch);
}