// File: src/logic/update_account.c

#include "update_account.h"
#include "src/data/account_data.h"
#include "src/presentation/user_interface.h"
#include <stdio.h>
#include <string.h>

void update_account_details_ui() {
    char account_number[9];
    BankAccount account;

    printf("Enter Account Number to Update: ");
    scanf("%8s", account_number);

    if (get_account_by_account_number(account_number, &account) != 0) {
        printf("Account not found.\n");
        return;
    }

    get_nonempty_input("New First Name: ", account.first_name);
    get_nonempty_input("New Last Name: ", account.last_name);
    get_validated_input("New Branch Code (B1/B2): ", account.branch_code, sizeof(account.branch_code), is_valid_branch_code, "Invalid Branch Code.\n");

    if (remove_account(&account) != 0) {
        printf("Failed to remove original account.\n");
        return;
    }

    save_account_to_csv("../assets/accounts.csv", &account);

    printf("Account details updated successfully.\n");
}
