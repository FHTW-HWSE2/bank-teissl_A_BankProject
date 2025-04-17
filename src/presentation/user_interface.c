#include "user_interface.h"
#include "src/logic/create_account.h"
#include <stdio.h>
#include <string.h>

void open_file_error() {
    printf("Error opening file.\n");
}

static void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void get_nonempty_input(const char *prompt, char *buffer) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, 100, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
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
    printf("Account number: %s\n", account->account_number);
    printf("Branch code: %s\n", account->branch_code);
}
