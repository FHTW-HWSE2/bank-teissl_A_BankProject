#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "src/logic/create_account.h"

void open_file_error(void);
void print_account_confirmation(const BankAccount *account);
void get_nonempty_input(const char *prompt, char *buffer);
void get_validated_input(const char *prompt, char *buffer, int size, int (*validate)(const char *), const char *error_msg);

#endif // USER_INTERFACE_H
