#include "include/account_number.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define CSV_FILE "../assets/accounts.csv"

/**
 * @brief Checks whether an account number already exists in the CSV file.
 *
 * This function reads through each line of the CSV file and compares the last field
 * (assumed to be the account number) to the provided value.
 *
 * @param account_number The account number to search for.
 * @return true if the account number exists in the CSV file, false otherwise.
 */
static bool account_exists(const char *account_number) {
    FILE *file = fopen(CSV_FILE, "r");
    if (file == NULL) {
        return false;
    }
    char line[256];
    // Read and skip the header line (if present)
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return false;
    }
    while (fgets(line, sizeof(line), file)) {
        char *token;
        char *lastToken = NULL;
        token = strtok(line, ",");
        while (token != NULL) {
            lastToken = token;
            token = strtok(NULL, ",");
        }
        if (lastToken != NULL) {
            lastToken[strcspn(lastToken, "\n")] = '\0';
            if (strcmp(lastToken, account_number) == 0) {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false;
}

/**
 * @brief Generates a unique 8-digit account number.
 *
 * This function repeatedly generates a random 8-digit numeric string until it finds one
 * that is not "00000000" and does not already exist in the CSV file. The result is stored
 * in a static buffer and returned as a string.
 *
 * @return A pointer to a unique 8-digit null-terminated account number string.
 */
char* generate_unique_account_number(void) {
    static char account_number[9]; // 8 digits + null terminator
    srand((unsigned int)time(NULL));
    do {
        snprintf(account_number, sizeof(account_number), "%08d", rand() % 100000000);
    } while (strcmp(account_number, "00000000") == 0 || account_exists(account_number));
    return account_number;
}
