#ifndef VALIDATIONS_H
#define VALIDATIONS_H

int is_valid_account_number(const char *number);
int is_valid_ssn(const char *ssn);
int is_valid_branch_code(const char *branch_code);
int is_valid_phone_number(const char *phone);
int is_valid_email(const char *email);
void get_validated_input(const char *prompt, char *buffer, int size, int (*validate)(const char *), const char *error_msg);
void get_nonempty_input(const char *prompt, char *buffer);

#endif