#include "create_account.h"
#include "src/data/account_data.h"
#include <string.h>
#include <stdlib.h> // für srand
#include <time.h>   // für time
#include <stdio.h> // für snprintf

void create_account_logic(BankAccount *account) {
    strcpy(account->account_number, generate_unique_account_number());
    save_account_to_csv(account);
}

char* generate_unique_account_number(void) {
    static char account_number[9];
    srand((unsigned int)time(NULL));
    do {
        snprintf(account_number, sizeof(account_number), "%08d", rand() % 100000000);
    } while (strcmp(account_number, "00000000") == 0 || account_exists(account_number));
    return account_number;
}
