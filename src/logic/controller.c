#include "create_account.h"
#include "delete_account.h"
#include "src/presentation/user_interface.h"
#include <stdio.h>
#include <stdlib.h>

void start() {
    int choice;

    while (1) {
        choice = show_menu();

        switch (choice) {
        case 1:
            create_account_logic();
            exit(0); // Exit after creating the account
        case 2:
            delete_account();
            break;
        case 3:
            break;
        case 9:
            exit(0);
            break;
        default:
            break;
        }
    }

}