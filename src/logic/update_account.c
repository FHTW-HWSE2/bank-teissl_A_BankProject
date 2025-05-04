// File: src/logic/update_account.c

#include "update_account.h"
#include "src/data/account_data.h"
#include "src/presentation/user_interface.h"
#include <stdio.h>
#include <string.h>

#define ACCOUNT_CSV_PATH "../assets/accounts.csv"

void update_account_details_ui(void) {
    char account_number[9];
    BankAccount account;

    printf("Enter Account Number to update: ");
    scanf("%8s", account_number);

    if (get_account_by_account_number(account_number, &account) != 0) {
        printf("Error: Account not found.\n");
        return;
    }

    get_nonempty_input("New First Name: ", account.first_name);
    get_nonempty_input("New Last Name: ", account.last_name);
    get_validated_input("New Branch Code (B1/B2): ", account.branch_code, sizeof(account.branch_code), is_valid_branch_code, "Invalid branch code.");

    if (remove_account(&account) != 0) {
        printf("Error: Failed to remove account.\n");
        return;
    }

    save_account_to_csv(ACCOUNT_CSV_PATH, &account);

    printf("Account details updated successfully.\n");
}
