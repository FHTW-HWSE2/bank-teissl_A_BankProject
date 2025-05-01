#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "src/logic/create_account.h"

/**
 * @brief Displays a file opening error message.
 */
void open_file_error(void);

/**
 * @brief Clears the input buffer to handle leftover characters.
 */
void clear_input_buffer();

/**
 * @brief Displays the main menu and returns the user's choice.
 * 
 * @return int The selected menu option or -1 on invalid input.
 */
int show_menu();

/**
 * @brief Prompts the user for non-empty input.
 * 
 * @param prompt Prompt message to display.
 * @param buffer Buffer to store the input string.
 */
void get_nonempty_input(const char *prompt, char *buffer);

/**
 * @brief Prompts the user for input and validates it using a custom function.
 * 
 * @param prompt Prompt message to display.
 * @param buffer Buffer to store the input string.
 * @param size Size of the buffer.
 * @param validate Function pointer to validate the input.
 * @param error_msg Message to display on invalid input.
 */
void get_validated_input(const char *prompt, char *buffer, int size, int (*validate)(const char *), const char *error_msg);

/**
 * @brief Displays a summary of the newly created account.
 * 
 * @param account Pointer to the created BankAccount.
 */
void print_account_confirmation(const BankAccount *account);

/**
 * @brief Handles the user interface for deleting an account.
 */
void delete_account_ui();

#endif
