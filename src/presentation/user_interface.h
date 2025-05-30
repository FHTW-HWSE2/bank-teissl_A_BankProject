#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "src/logic/create_account.h"

void clear_input_buffer();
void print_message(const char *message);
void print_account_confirmation(const BankAccount *account);
void get_nonempty_input(const char *prompt, char *buffer);
void get_validated_input(const char *prompt, char *buffer, int size, int (*validate)(const char *), const char *error_msg);
int show_menu();
void delete_account_ui();
void update_account_ui();
void transaction_ui(const char type);
void transfer_ui();

#endif
