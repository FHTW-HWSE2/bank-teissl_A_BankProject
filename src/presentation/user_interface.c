#include "user_interface.h"
#include "src/logic/create_account.h"
#include "src/logic/delete_account.h"
#include <stdio.h>
#include <string.h>

void open_file_error() {
    printf("Error opening file.\n");
}

static void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int show_menu() {
    int choice;

    printf("\n========= Bank Project Menu =========\n");
    printf("1. Create New Account\n");
    printf("2. Delete Account\n");
    printf("9. Exit\n");
    printf("Choose an option: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n');  // Clear invalid input
        return -1;
    }

    clear_input_buffer();
    return choice;
}

void get_nonempty_input(const char *prompt, char *buffer) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, 100, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline
            if (strlen(buffer) > 0) break;
        }
        printf("Input must not be empty. Please try again.\n");
    }
}

void get_validated_input(const char *prompt, char *buffer, int size, int (*validate)(const char *), const char *error_msg) {
    while (1) {
        printf("%s", prompt);
        if (scanf("%s", buffer) == 1) {
            clear_input_buffer();
            if (validate(buffer)) break;
        }
        printf("%s\n", error_msg);
    }
}

void print_account_confirmation(const BankAccount *account) {
    printf("\nAccount created successfully!\n");
    printf("Account holder: %s %s\n", account->first_name, account->last_name);
    printf("SSN: %s\n", account->ssn);
    printf("Branch code: %s\n", account->branch_code);
    printf("Account number: %s\n", account->account_number);
    printf("Account balance: %lu\n", account->balance);
}

void delete_account_ui() {
    char account_number[9];

    printf("Enter the Account number to delete: ");
    scanf("%8s", account_number);  // Limit input to 8 characters

    int result = delete_account(account_number);

    switch (result) {
        case 0:
            printf("Account successfully deleted and archived.\n");
            break;
        case -1:
            printf("Error: Account not found.\n");
            break;
        case -2:
            printf("Error: Could not delete account from active list.\n");
            break;
        case -3:
            printf("Error: Could not archive deleted account.\n");
            break;
        default:
            printf("Unknown error occurred.\n");
    }
}
