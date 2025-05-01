#ifndef CONTROLLER_H
#define CONTROLLER_H

#define MAX_STRING_LENGTH 100

/**
 * @brief Represents a bank account.
 * 
 * Stores personal and account-related information.
 * The balance is stored in cents (e.g., 1050 = €10.50) to avoid floating-point inaccuracies.
 */
typedef struct {
    char first_name[MAX_STRING_LENGTH];
    char last_name[MAX_STRING_LENGTH];
    char ssn[11];
    char address[MAX_STRING_LENGTH];
    char phone[MAX_STRING_LENGTH];
    char email[MAX_STRING_LENGTH];
    char branch_code[3];
    char account_number[9];
    unsigned long balance;
} BankAccount;

/**
 * @brief Starts the main menu loop for user interaction.
 * 
 * Based on user selection, it triggers account creation, deletion, or exits the program.
 */
void start();

#endif
