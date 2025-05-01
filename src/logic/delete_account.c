#include "controller.h"
#include "delete_account.h"
#include "src/data/account_data.h"
#include "src/presentation/user_interface.h"
#include <stdio.h>
#include <stdlib.h>

#define DELETED_ACCOUNTS_FILE "../assets/deleted_accounts.csv"

int delete_account(const char *account_number) {
    BankAccount account;

    if (get_account_by_account_number(account_number, &account) != 0) {
        return -1;
    }

    if (remove_account(&account) != 0) {
        return -2;
    }

    if (save_account_to_csv(DELETED_ACCOUNTS_FILE, &account) != 0) {
        return -3;
    }

    return 0; // Success
}
