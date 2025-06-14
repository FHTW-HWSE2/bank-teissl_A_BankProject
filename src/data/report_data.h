#ifndef REPORT_DATA_H
#define REPORT_DATA_H

#define MAX_ACCOUNTS 100

typedef struct {
    char first_name[50];
    char last_name[50];
    char ssn[20];
    char address[100];
    char phone[20];
    char email[50];
    char branch_code[20];
    char account_number[20];
    double balance; 
} Account;

typedef struct {
    char data[4096]; // Large enough for detailed reports
} Report;

int fetch_report_data(const char *parameters, Report *report);

#endif
