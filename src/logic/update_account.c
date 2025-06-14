#include "update_account.h"
#include "src/data/account_data.h"
#include "src/presentation/user_interface.h"
#include "src/logic/validations.h"
#include <stdio.h>
#include <string.h>

#define ACCOUNT_CSV_PATH "../assets/accounts.csv"

int update_account(const char *account_number) {
    BankAccount account;

    if (get_account_by_account_number(account_number, &account) != 0) {
        return -1;
    }

    get_nonempty_input("New First Name: ", account.first_name);
    get_nonempty_input("New Last Name: ", account.last_name);
    get_nonempty_input("Address: ", account.address);
    get_nonempty_input("Phone: ", account.phone);
    get_nonempty_input("Email: ", account.email);
    get_validated_input("New Branch Code (B1/B2): ", account.branch_code, sizeof(account.branch_code), is_valid_branch_code, "Invalid branch code.");

    if (remove_account(&account) != 0) {
        return -2;
    }

    if (save_account_to_csv(ACCOUNT_CSV_PATH, &account) != 0) {
        return -3;
    }

    return 0;
}
