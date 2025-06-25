#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "src/presentation/user_interface.h"

int is_valid_account_number(const char *number)
{
    if (strlen(number) != 8)
        return 0;
    for (int i = 0; i < 8; i++)
    {
        if (!isdigit(number[i]))
            return 0;
    }
    return 1;
}

int is_valid_ssn(const char *ssn) {
    if (strlen(ssn) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(ssn[i])) return 0;
    }
    return 1;
}

int is_valid_branch_code(const char *branch_code) {
    return (strcmp(branch_code, "B1") == 0 || strcmp(branch_code, "B2") == 0 || strcmp(branch_code, "b1") == 0 || strcmp(branch_code, "b2") == 0);
}

int is_valid_phone_number(const char *phone) {
    if (phone[0] == '\0') return 0; // empty string is invalid

    for (int i = 0; phone[i]; i++) {
        if (!isdigit((unsigned char)phone[i])) {
            return 0; // not a digit → invalid
        }
    }
    return 1; // valid
}

int is_valid_email(const char *email) {
    const char *at = strchr(email, '@');
    if (!at || at == email) return 0; // no @ or starts with @

    const char *dot = strchr(at, '.');
    if (!dot || dot == at + 1) return 0; // no dot after @ or immediate

    // optional: make sure dot is not at end
    if (dot[1] == '\0') return 0;

    return 1; // looks okay
}

void get_validated_input(const char *prompt, char *buffer, int size, int (*validate)(const char *), const char *error_msg)
{
    while (1)
    {
        print_message(prompt);
        //printf("%s", prompt);
        if (scanf("%s", buffer) == 1)
        {
            clear_input_buffer();
            if (validate(buffer))
                break;
        }
        print_message(error_msg);
        //printf("%s\n", error_msg);
    }
}

// Get string input from user and ensure it's not empty
void get_nonempty_input(const char *prompt, char *buffer)
{
    while (1)
    {
        print_message(prompt);
        //printf("%s", prompt);
        if (fgets(buffer, 100, stdin) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strlen(buffer) > 0)
                break;
        }
        print_message("Input cannot be empty. Please try again.");
        //printf("Input must not be empty. Please try again.\n");
    }
}
