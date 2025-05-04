#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_cmock_config.yml"


static struct mock_cmock_configInstance
{
  unsigned char placeHolder;
} Mock;


void mock_cmock_config_Verify(void)
{
}

void mock_cmock_config_Init(void)
{
  mock_cmock_config_Destroy();
}

void mock_cmock_config_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

