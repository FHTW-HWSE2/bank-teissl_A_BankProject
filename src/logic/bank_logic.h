#ifndef BANK_LOGIC_H
#define BANK_LOGIC_H

int do_transaction(const char *account_number, const char *branch_code, int amount, const char type);
int transfer_funds(const char* branch_code, const char* from_account, const char* to_account, int amount);

#endif
