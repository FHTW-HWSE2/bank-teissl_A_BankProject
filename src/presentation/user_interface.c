#include "user_interface.h"
#include "src/logic/create_account.h"
#include "src/logic/delete_account.h"
#include "src/logic/update_account.h"
#include "src/logic/bank_logic.h"
#include "src/logic/validations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ACCOUNT_CSV_PATH "../assets/accounts.csv"

// Clear leftover input in buffer
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void print_message(const char *message) {
    printf("%s\n", message);
}

int show_menu()
{
    int choice;
    
    printf("______  ___   _   _  _   __      ___  ___  ___   _   _   ___  _____  ________  ___ _____ _   _ _____ \n");
    printf("| ___ \\/ _ \\ | \\ | || | / /      |  \\/  | / _ \\ | \\ | | / _ \\|  __ \\|  ___|  \\/  ||  ___| \\ | |_   _|\n");
    printf("| |_/ / /_\\ \\|  \\| || |/ /       | .  . |/ /_\\ \\|  \\| |/ /_\\ \\ |  \\/| |__ | .  . || |__ |  \\| | | |  \n");
    printf("| ___ \\  _  || . ` ||    \\       | |\\/| ||  _  || . ` ||  _  | | __ |  __|| |\\/| ||  __|| . ` | | |  \n");
    printf("| |_/ / | | || |\\  || |\\  \\      | |  | || | | || |\\  || | | | |_\\ \\| |___| |  | || |___| |\\  | | |  \n");
    printf("\\____/\\_| |_/\\_| \\_/\\_| \\_/      \\_|  |_/\\_| |_/\\_| \\_/\\_| |_/\\____/\\____/\\_|  |_/\\____/\\_| \\_/ \\_/  \n");
    printf("                                                                                                 \n");
    printf("                                                                                                 \n");

printf("\n");
printf("                        +========================================+\n");
printf("                        ||          BANK MAIN MENU              ||\n");
printf("                        +========================================+\n");
printf("                        ||  [1]     Create New Bank Account     ||\n");
printf("                        ||--------------------------------------||\n");
printf("                        ||  [2]     Delete Existing Account     ||\n");
printf("                        ||--------------------------------------||\n");
printf("                        ||  [3]     Update Account Information  ||\n");
printf("                        ||--------------------------------------||\n");
printf("                        ||  [4]     Deposit Funds               ||\n");
printf("                        ||--------------------------------------||\n");
printf("                        ||  [5]     Withdraw Funds              ||\n");
printf("                        ||--------------------------------------||\n");
printf("                        ||  [6]     Internal Transfer           ||\n");
printf("                        ||--------------------------------------||\n");
printf("                        ||  [7]     Generate Report             ||\n");
printf("                        ||--------------------------------------||\n");
printf("                        ||  [9]     Exit                        ||\n");
printf("                        +========================================+\n");
printf("\n");
printf("                        Enter your choice: ");

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

// Print confirmation after account creation
void print_account_confirmation(const BankAccount *account)
{
    printf("\nAccount created successfully!\n");
    printf("Account holder: %s %s\n", account->first_name, account->last_name);
    printf("SSN: %s\n", account->ssn);
    printf("Branch code: %s\n", account->branch_code);
    printf("Account balance: %lu\n", account->balance);
    printf("Account number: %s\n", account->account_number);
}

void create_account_ui()
{
    int result = create_account_logic();

    switch (result)
    {
    case 0:
        printf("Account successfully created.\n");
        break;
    case -1:
        printf("Error saving account to file.\n");
        break;
    default:
        printf("Unknown error occurred.\n");
    }
}

// UI for deleting account
void delete_account_ui()
{
    char account_number[9];
    printf("Enter the Account number to delete: ");
    scanf("%8s", account_number);
    int result = delete_account(ACCOUNT_CSV_PATH, account_number);

    switch (result)
    {
    case 0:
        printf("Account successfully deleted and archived.\n");
        break;
    case -1:
        printf("Error: Account not found.\n");
        break;
    case -2:
        printf("Error deleting account.\n");
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
    if (amount <= 0)
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

void transfer_ui() {
    char from_account[9];
    char to_account[9];
    char branch_code[3];
    int amount;

    printf("\n--- Internal Transfer ---\n");
    get_validated_input("Enter Branch code (B1/B2): ", branch_code, sizeof(branch_code), is_valid_branch_code, "Invalid branch code. Use 'B1' or 'B2'.");
    get_validated_input("Enter FROM account number: ", from_account, sizeof(from_account), is_valid_account_number, "Invalid account number. Must be 8 digits.");
    get_validated_input("Enter TO account number: ", to_account, sizeof(to_account), is_valid_account_number, "Invalid account number. Must be 8 digits.");

    printf("Enter amount to transfer (in whole cents): "); // TODO
    scanf("%d", &amount);
    if (amount <= 0) {
        printf("Invalid transfer amount.\n");
        return;
    }

    int result = transfer_funds(branch_code, from_account, to_account, amount);
    switch (result)
    {
    case 0:
        printf("Transfer made successfully.\n");
        break;
    case -1:
        printf("Error: Sender account not found.\n");
        break;
    case -2:
        printf("Error: Receiver account not found.\n");
        break;
    case -3:
        printf("Error: Insufficient funds in sender's account.\n");
        break;
    case -4:
        printf("Error: Could not delete sender's account.\n");
        break;
    case -5:
        printf("Error: Could not save sender's account.\n");
        break;
    case -6:
        printf("Error: Could not delete receiver's account.\n");
        break;
    case -7:
        printf("Error: Could not save receiver's account.\n");
        break;
    default:
        printf("Unknown error occurred.\n");
    }
}
