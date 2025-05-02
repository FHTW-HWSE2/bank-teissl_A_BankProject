// File: src/logic/update_account.c

#include "update_account.h"
#include "src/data/account_data.h"
#include "src/presentation/user_interface.h"
#include <stdio.h>
#include <string.h>

int update_account_details(const char *account_number) {
    BankAccount account;

    // Load the account from the file
    if (get_account_by_account_number(account_number, &account) != 0) {
        printf("Error: Account not found.\n");
        return -1;
    }

    // Prompt user for new editable values
    get_nonempty_input("New First Name: ", account.first_name);
    get_nonempty_input("New Last Name: ", account.last_name);
    get_validated_input("New Branch Code (B1/B2): ", account.branch_code, sizeof(account.branch_code), is_valid_branch_code, "Invalid branch code.");

    // Remove the original account
    if (remove_account(&account) != 0) {
        printf("Failed to remove original account.\n");
        return -2;
    }

    // Save updated account
    if (save_account_to_csv("../assets/accounts.csv", &account) != 0) {
        printf("Failed to save updated account.\n");
        return -3;
    }

    printf("Account details updated successfully.\n");
    return 0;
}

void update_account_details_ui() {
    char account_number[9];

    printf("Enter the Account Number to update: ");
    scanf("%8s", account_number);

    int result = update_account_details(account_number);
    switch (result) {
        case 0:
            printf("Update successful.\n");
        break;
        case -1:
            printf("Error: Account not found.\n");
        break;
        case -2:
            printf("Error: Failed to remove account.\n");
        break;
        case -3:
            printf("Error: Failed to save updated account.\n");
        break;
        default:
            printf("Unknown error occurred.\n");
    }
}
