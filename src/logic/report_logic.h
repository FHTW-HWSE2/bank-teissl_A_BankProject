#ifndef REPORT_LOGIC_H
#define REPORT_LOGIC_H

#include "../data/report_data.h"

int generate_report_request(const char *parameters);
int generate_report(const char *parameters, Report *report);

#endif
