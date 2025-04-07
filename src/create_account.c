#include "include/create_account.h"
#include <string.h>

void create_account_logic(BankAccount *account) {
    strcpy(account->account_number, generate_unique_account_number());
    save_account_to_csv(account);
}
