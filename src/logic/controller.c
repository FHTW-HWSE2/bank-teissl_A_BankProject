#include "create_account.h"
#include "delete_account.h"
#include "update_account.h"
#include "src/presentation/user_interface.h"
#include "src/presentation/report_ui.h"
#include <stdio.h>
#include <stdlib.h>

void start()
{
    int choice;

    while (1)
    {
        choice = show_menu();

        switch (choice)
        {
        case 1:
            create_account_logic();
            break;
        case 2:
            delete_account_ui();
            break;
        case 3:
            update_account_ui();
            break;
        case 4:
            transaction_ui('d'); // deposit
            break;
        case 5:
            transaction_ui('w'); // withdraw
            break;
        case 6:
            transfer_ui();
            break;
         case 7:
            request_financial_report();
            break;
        case 9:
            exit(0);
            break;
        default:
            break;
        }
    }
}
