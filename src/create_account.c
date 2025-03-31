#include "include/create_account.h"
#include "include/account_number.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 100
#define CSV_FILE "../assets/accounts.csv"

/**
 * @brief Clears the standard input buffer.
 *
 * This function discards all characters remaining in the input buffer until a newline or EOF is found.
 * Useful for avoiding unwanted input when using scanf.
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Prompts the user until a non-empty input is entered.
 *
 * Displays a prompt and waits for the user to enter a string. If the input is empty,
 * the user will be prompted again.
 *
 * @param prompt The message shown to the user.
 * @param buffer The buffer to store the user's input.
 * @param size The maximum number of characters to read.
 */
void get_valid_input(const char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0'; // remove newline
            if (strlen(buffer) > 0) {
                break;
            }
        }
        printf("Input must not be empty. Please try again.\n");
    }
}

/**
 * @brief Prompts the user until a valid double value is entered.
 *
 * Continues prompting until the user enters a valid numeric (double) value.
 *
 * @param prompt The message shown to the user.
 * @return The valid double entered by the user.
 */
double get_valid_double(const char *prompt) {
    double value;
    char dummy;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &value) == 1) {
            // Clear the input buffer.
            while ((dummy = getchar()) != '\n' && dummy != EOF);
            return value;
        } else {
            printf("Invalid number. Please try again.\n");
            while ((dummy = getchar()) != '\n' && dummy != EOF);
        }
    }
}

/**
 * @brief Prompts the user until a valid 10-digit SSN is entered.
 *
 * Ensures the SSN consists of exactly 10 numeric digits.
 *
 * @param prompt The message shown to the user.
 * @param buffer The buffer to store the SSN.
 * @param size The size of the buffer.
 */
void get_valid_ssn(const char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);
        if (scanf("%s", buffer) == 1) {
            clear_input_buffer();
            if (strlen(buffer) == 10) {
                bool allDigits = true;
                for (int i = 0; i < 10; i++) {
                    if (buffer[i] < '0' || buffer[i] > '9') {
                        allDigits = false;
                        break;
                    }
                }
                if (allDigits) {
                    break;
                }
            }
        }
        printf("Invalid SSN. It must have exactly 10 digits. Please try again.\n");
    }
}

/**
 * @brief Prompts the user until a valid branch code is entered.
 *
 * Only accepts "B1" or "B2" as valid branch codes.
 *
 * @param prompt The message shown to the user.
 * @param buffer The buffer to store the branch code.
 * @param size The size of the buffer.
 */
void get_valid_branch_code(const char *prompt, char *buffer, int size) {
    while (1) {
        printf("%s", prompt);
        if (scanf("%s", buffer) == 1) {
            clear_input_buffer();
            if (strcmp(buffer, "B1") == 0 || strcmp(buffer, "B2") == 0) {
                break;
            }
        }
        printf("Invalid branch code. Please enter 'B1' or 'B2'.\n");
    }
}

/**
 * @brief Creates a new bank account and stores the data in a CSV file.
 *
 * This function gathers user input with validation for personal details,
 * account type, and financial information. It generates a unique account number,
 * writes the data into a CSV file, and displays confirmation messages.
 */
void create_bank_account(void) {
    char first_name[MAX_STRING_LENGTH], last_name[MAX_STRING_LENGTH];
    char ssn[11], address[MAX_STRING_LENGTH], phone[MAX_STRING_LENGTH], email[MAX_STRING_LENGTH];
    char account_type[MAX_STRING_LENGTH], branch_code[3], account_number[9];
    double initial_balance = 0.0, overdraft_limit = 0.0;
    
    // Get user inputs with validation
    get_valid_input("Enter the account holder's first name: ", first_name, MAX_STRING_LENGTH);
    get_valid_input("Enter the account holder's last name: ", last_name, MAX_STRING_LENGTH);
    get_valid_ssn("Enter the social security number (10 digits): ", ssn, sizeof(ssn));
    get_valid_input("Enter the address: ", address, MAX_STRING_LENGTH);
    get_valid_input("Enter the phone number: ", phone, MAX_STRING_LENGTH);
    get_valid_input("Enter the email address: ", email, MAX_STRING_LENGTH);
    
    // Ask for and validate account type
    while (1) {
        get_valid_input("Enter the account type (Standard/Initial balance/Overdraft limit): ", account_type, MAX_STRING_LENGTH);
        if (strcmp(account_type, "Standard") == 0 ||
            strcmp(account_type, "Initial balance") == 0 ||
            strcmp(account_type, "Overdraft limit") == 0) {
            break;
        }
        printf("Invalid account type. Please enter 'Standard', 'Initial balance' or 'Overdraft limit'.\n");
    }
    
    // Depending on account type, ask for additional inputs.
    if (strcmp(account_type, "Initial balance") == 0) {
        initial_balance = get_valid_double("How much is the initial balance? ");
    } else if (strcmp(account_type, "Overdraft limit") == 0) {
        overdraft_limit = get_valid_double("How much overdraft limit is? ");
    } else if (strcmp(account_type, "Standard") == 0) {
        // For a standard account: set both to 0.
        initial_balance = 0.0;
        overdraft_limit = 0.0;
    }
    
    // Generate unique account number using the separate function.
    strcpy(account_number, generate_unique_account_number());
    
    // Ask for branch code.
    get_valid_branch_code("Select the branch code (B1/B2): ", branch_code, sizeof(branch_code));
    
    // Open CSV file: If the file doesn't exist or is empty, write the header.
    FILE *file = fopen(CSV_FILE, "r");
    bool writeHeader = false;
    if (file == NULL) {
        writeHeader = true;
    } else {
        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            writeHeader = true;
        }
        fclose(file);
    }
    
    file = fopen(CSV_FILE, "a+");
    if (file == NULL) {
        printf("Error opening file. (create_account.c)\n");
        return;
    }
    if (writeHeader) {
        fprintf(file, "FirstName,LastName,SSN,Address,phone,email,accountType,initialBalance,OverdraftLimit,BranchCode,AccountNumber\n");
    }
    
    // Write new account data to the CSV file.
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%.2f,%.2f,%s,%s\n",
            first_name, last_name, ssn, address, phone, email,
            account_type, initial_balance, overdraft_limit, branch_code, account_number);
    fclose(file);
    
    // Confirmation output.
    printf("\nAccount created successfully!\n");
    printf("Account holder: %s %s\n", first_name, last_name);
    printf("Account type: %s\n", account_type);
    if (strcmp(account_type, "Initial balance") == 0) {
        printf("Initial balance: %.2f\n", initial_balance);
    } else if (strcmp(account_type, "Overdraft limit") == 0) {
        printf("Overdraft limit: %.2f\n", overdraft_limit);
    }
    printf("SSN: %s\n", ssn);
    printf("Account number: %s\n", account_number);
    printf("Branch code: %s\n", branch_code);
}
