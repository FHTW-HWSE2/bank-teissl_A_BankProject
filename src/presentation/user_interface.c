#include "user_interface.h"
#include "src/logic/create_account.h"
#include "src/logic/delete_account.h"
#include "src/logic/update_account.h"
#include "src/logic/bank_logic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Error display for file-related issues
void open_file_error()
{
    printf("Error opening file.\n");
}

// Clear leftover input in buffer
static void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Show menu to user and return selected option
int show_menu()
{
    int choice;

    printf("\n========= Bank Project Menu =========\n");
    printf("1. Create New Account\n");
    printf("2. Delete Account\n");
    printf("3. Update Account Details\n");
    printf("4. Deposit Funds\n");
    printf("9. Exit\n");
    printf("Choose an option: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n')
            ;
        return -1;
    }

    clear_input_buffer();
    return choice;
}

// Get string input from user and ensure it's not empty
void get_nonempty_input(const char *prompt, char *buffer)
{
    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, 100, stdin) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0)
                break;
        }
        printf("Input must not be empty. Please try again.\n");
    }
}

// Input with validation function
void get_validated_input(const char *prompt, char *buffer, int size, int (*validate)(const char *), const char *error_msg)
{
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%s", buffer) == 1)
        {
            clear_input_buffer();
            if (validate(buffer))
                break;
        }
        printf("%s\n", error_msg);
    }
}

// Print confirmation after account creation
void print_account_confirmation(const BankAccount *account)
{
    printf("\nAccount created successfully!\n");
    printf("Account holder: %s %s\n", account->first_name, account->last_name);
    printf("SSN: %s\n", account->ssn);
    printf("Branch code: %s\n", account->branch_code);
    printf("Account number: %s\n", account->account_number);
    printf("Account balance: %lu\n", account->balance);
}

// UI for deleting account
void delete_account_ui()
{
    char account_number[9];
    printf("Enter the Account number to delete: ");
    scanf("%8s", account_number);

    int result = delete_account(account_number);

    switch (result)
    {
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

// UI for updating account
void update_account_ui()
{
    char account_number[9];
    printf("Enter the Account number to update: ");
    scanf("%8s", account_number);
    clear_input_buffer();

    int result = update_account(account_number);

    switch (result)
    {
    case 0:
        printf("Account successfully updated.\n");
        break;
    case -1:
        printf("Error: Account not found.\n");
        break;
    case -2:
        printf("Error: Could not delete account.\n");
        break;
    case -3:
        printf("Error: Could not save updated account.\n");
        break;
    default:
        printf("Unknown error occurred.\n");
    }
}

// 🆕 UI for deposit funds
void deposit_ui()
{
    char account_number[20];
    char branch_code[10];
    int amount;

    printf("\n--- Deposit Funds ---\n");
    printf("Enter account number: ");
    scanf("%19s", account_number);

    printf("Enter branch code (B1 or B2): ");
    scanf("%9s", branch_code);

    printf("Enter amount to deposit (in whole cents): ");
    scanf("%d", &amount);

    // Check that the amount is in whole cents and greater than 0
    if (amount <= 0 || amount % 1 != 0)
    {
        printf("Invalid deposit amount.\n");
        return;
    }

    // Check that the branch code is valid
    if (strcmp(branch_code, "B1") != 0 && strcmp(branch_code, "B2") != 0)
    {
        printf("Invalid branch code.\n");
        return;
    }

    int result = deposit_funds(account_number, branch_code, amount);

    switch (result)
    {
    case 0:
        printf("deposit added successfully.\n");
        break;
    case -1:
        printf("Error: Account not found.\n");
        break;
    case -2:
        printf("Error: Could not delete account.\n");
        break;
    case -3:
        printf("Error: Could not save updated account.\n");
        break;
    default:
        printf("Unknown error occurred.\n");
    }
}
