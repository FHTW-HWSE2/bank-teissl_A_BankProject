#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "Mockconfig.yml"


static struct MockconfigInstance
{
  unsigned char placeHolder;
} Mock;


void Mockconfig_Verify(void)
{
}

void Mockconfig_Init(void)
{
  Mockconfig_Destroy();
}

void Mockconfig_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

