#ifndef BANK_LOGIC_H
#define BANK_LOGIC_H

void deposit_funds(const char* account_number, const char* branch_code, int amount);
void withdraw_funds(const char* account_number, const char* branch_code, int amount);
void transfer_funds(const char* from_account, const char* to_account, int amount);

#endif //BANK_LOGIC_H
