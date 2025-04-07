#ifndef CREATE_ACCOUNT_LOGIC_H
#define CREATE_ACCOUNT_LOGIC_H

#include "data/account_data.h"

void create_account_logic(BankAccount *account);
char* generate_unique_account_number(void);

#endif