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

    printf("\n");
    printf("+--------------------------------------+\n");
    printf("|         BANK MANAGEMENT SYSTEM       |\n");
    printf("+--------------------------------------+\n");
    printf("|  1. Create New Bank Account          |\n");
    printf("|  2. Delete Existing Account          |\n");
    printf("|  3. Update Account Information       |\n");
    printf("|  4. Deposit Funds                    |\n");
    printf("|  5. Withdraw Funds                   |\n");
    printf("|  9. Exit                             |\n");
    printf("+--------------------------------------+\n");

    printf("Enter your choice: ");

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
// TODO weitermachen
void transaction_ui(const char type)
{
    char account_number[9];
    char branch_code[3];
    int amount;

    get_validated_input("Enter Branch code (B1/B2): ", branch_code, sizeof(branch_code), is_valid_branch_code, "Invalid branch code. Use 'B1' or 'B2'.");
    get_validated_input("Enter account number: ", account_number, sizeof(account_number), is_valid_account_number, "Invalid account number. Must be 8 digits.");

    if (type == 'd')
    {
        printf("Enter amount to deposit (in whole cents): ");
    }
    else if (type == 'w')
    {
        printf("Enter amount to withdraw (in whole cents): ");
    }
    scanf("%d", &amount);

    // Check that the amount is in whole cents and greater than 0
    // TODO
    if (amount <= 0 || amount % 1 != 0)
    {
        printf("Invalid amount.\n");
        return;
    }

    int result = do_transaction(account_number, branch_code, amount, type);

    switch (result)
    {
    case 0:
        printf("Transaction done.\n");
        break;
    case -1:
        printf("Error: Account not found.\n");
        break;
    case -2:
        printf("Error: Insufficient funds.\n");
        break;
    case -3:
        printf("Error: Could not delete account.\n");
        break;
    case -4:
        printf("Error: Could not save account.\n");
        break;
    default:
        printf("Unknown error occurred.\n");
    }
}
