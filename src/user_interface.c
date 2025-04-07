#include "include/user_interface.h"
#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void get_valid_input(const char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0) break;
        }
        printf("Input must not be empty. Please try again.\n");
    }
}

static double get_valid_double(const char *prompt) {
    double value;
    char dummy;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &value) == 1) {
            while ((dummy = getchar()) != '\n' && dummy != EOF);
            return value;
        } else {
            printf("Invalid number. Please try again.\n");
            while ((dummy = getchar()) != '\n' && dummy != EOF);
        }
    }
}

static void get_valid_ssn(const char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);
        if (scanf("%s", buffer) == 1) {
            clear_input_buffer();
            if (strlen(buffer) == 10) {
                int valid = 1;
                for (int i = 0; i < 10; i++) {
                    if (buffer[i] < '0' || buffer[i] > '9') valid = 0;
                }
                if (valid) break;
            }
        }
        printf("Invalid SSN. Must be 10 digits.\n");
    }
}

static void get_valid_branch_code(const char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);
        if (scanf("%s", buffer) == 1) {
            clear_input_buffer();
            if (strcmp(buffer, "B1") == 0 || strcmp(buffer, "B2") == 0) break;
        }
        printf("Invalid branch code. Use 'B1' or 'B2'.\n");
    }
}

void print_account_confirmation(const BankAccount *account) {
    printf("\nAccount created successfully!\n");
    printf("Account holder: %s %s\n", account->first_name, account->last_name);
    printf("Account type: %s\n", account->account_type);
    if (strcmp(account->account_type, "Initial balance") == 0) {
        printf("Initial balance: %.2f\n", account->initial_balance);
    }
    if (strcmp(account->account_type, "Overdraft limit") == 0) {
        printf("Overdraft limit: %.2f\n", account->overdraft_limit);
    }
    printf("SSN: %s\n", account->ssn);
    printf("Account number: %s\n", account->account_number);
    printf("Branch code: %s\n", account->branch_code);
}

void start_account_creation_ui(void) {
    BankAccount account = {0};

    get_valid_input("First name: ", account.first_name, MAX_STRING_LENGTH);
    get_valid_input("Last name: ", account.last_name, MAX_STRING_LENGTH);
    get_valid_ssn("SSN (10 digits): ", account.ssn, sizeof(account.ssn));
    get_valid_input("Address: ", account.address, MAX_STRING_LENGTH);
    get_valid_input("Phone: ", account.phone, MAX_STRING_LENGTH);
    get_valid_input("Email: ", account.email, MAX_STRING_LENGTH);

    while (1) {
        get_valid_input("Account type (Standard/Initial balance/Overdraft limit): ", account.account_type, MAX_STRING_LENGTH);
        if (strcmp(account.account_type, "Standard") == 0 || strcmp(account.account_type, "Initial balance") == 0 || strcmp(account.account_type, "Overdraft limit") == 0) break;
        printf("Invalid type.\n");
    }

    if (strcmp(account.account_type, "Initial balance") == 0) account.initial_balance = get_valid_double("Enter initial balance: ");
    else if (strcmp(account.account_type, "Overdraft limit") == 0) account.overdraft_limit = get_valid_double("Enter overdraft limit: ");

    get_valid_branch_code("Branch code (B1/B2): ", account.branch_code, sizeof(account.branch_code));

    create_account_logic(&account);
    print_account_confirmation(&account);
}

