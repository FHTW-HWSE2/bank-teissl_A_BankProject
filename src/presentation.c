#include "include/presentation.h"
#include "include/create_account_logic.h"
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

void start_account_creation_ui(void) {
    char first[MAX_STRING_LENGTH], last[MAX_STRING_LENGTH], ssn[11];
    char address[MAX_STRING_LENGTH], phone[MAX_STRING_LENGTH], email[MAX_STRING_LENGTH];
    char type[MAX_STRING_LENGTH], branch[3];
    double balance = 0.0, overdraft = 0.0;

    get_valid_input("First name: ", first, MAX_STRING_LENGTH);
    get_valid_input("Last name: ", last, MAX_STRING_LENGTH);
    get_valid_ssn("SSN (10 digits): ", ssn, sizeof(ssn));
    get_valid_input("Address: ", address, MAX_STRING_LENGTH);
    get_valid_input("Phone: ", phone, MAX_STRING_LENGTH);
    get_valid_input("Email: ", email, MAX_STRING_LENGTH);

    while (1) {
        get_valid_input("Account type (Standard/Initial balance/Overdraft limit): ", type, MAX_STRING_LENGTH);
        if (strcmp(type, "Standard") == 0 || strcmp(type, "Initial balance") == 0 || strcmp(type, "Overdraft limit") == 0) break;
        printf("Invalid type.\n");
    }

    if (strcmp(type, "Initial balance") == 0) balance = get_valid_double("Enter initial balance: ");
    else if (strcmp(type, "Overdraft limit") == 0) overdraft = get_valid_double("Enter overdraft limit: ");

    get_valid_branch_code("Branch code (B1/B2): ", branch, sizeof(branch));

    create_account_logic(first, last, ssn, address, phone, email, type, balance, overdraft, branch);
}
