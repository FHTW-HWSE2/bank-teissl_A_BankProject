/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCKACCOUNT_DATA_H
#define _MOCKACCOUNT_DATA_H

#include "Tests/unity/unity.h"
#include "src/data/account_data.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

#ifdef __cplusplus
extern "C" {
#endif

void Mockaccount_data_Init(void);
void Mockaccount_data_Destroy(void);
void Mockaccount_data_Verify(void);




#define account_exists_Expect(filename, account_number) TEST_FAIL_MESSAGE("account_exists requires _ExpectAndReturn");
#define account_exists_ExpectAndReturn(filename, account_number, cmock_retval) account_exists_CMockExpectAndReturn(__LINE__, filename, account_number, cmock_retval)
void account_exists_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, const char* filename, const char* account_number, bool cmock_to_return);
#define save_account_to_csv_Expect(filename, account) TEST_FAIL_MESSAGE("save_account_to_csv requires _ExpectAndReturn");
#define save_account_to_csv_ExpectAndReturn(filename, account, cmock_retval) save_account_to_csv_CMockExpectAndReturn(__LINE__, filename, account, cmock_retval)
void save_account_to_csv_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, const char* filename, const BankAccount* account, int cmock_to_return);
#define get_account_by_account_number_Expect(filename, account_number, account) TEST_FAIL_MESSAGE("get_account_by_account_number requires _ExpectAndReturn");
#define get_account_by_account_number_ExpectAndReturn(filename, account_number, account, cmock_retval) get_account_by_account_number_CMockExpectAndReturn(__LINE__, filename, account_number, account, cmock_retval)
void get_account_by_account_number_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, const char* filename, const char* account_number, BankAccount* account, int cmock_to_return);
#define remove_account_Expect(filename, account) TEST_FAIL_MESSAGE("remove_account requires _ExpectAndReturn");
#define remove_account_ExpectAndReturn(filename, account, cmock_retval) remove_account_CMockExpectAndReturn(__LINE__, filename, account, cmock_retval)
void remove_account_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, const char* filename, const BankAccount* account, int cmock_to_return);

#ifdef __cplusplus
}
#endif

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
