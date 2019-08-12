#ifndef __SHELL_H_
#define __SHELL_H_

/*****************************************  Include  ******************************************************/
#include "typedef.h"
#include "stm32f4xx_hal.h"

/******************************************  Global macro definition  ******************************************/
#define SHELL_DATA_LEN	32
/******************************************  Global type definition  *******************************************/
typedef struct{
	ValidStatus recvOkFlg;
	U8 len;
	U8* pData;
}shellRecvDataHandleT;
/******************************************  Global variable declaration  **************************************/
extern shellRecvDataHandleT shellRecvDataHandle;

/******************************************  Global function declaration  **************************************/
void Shell_Init (void);
void Shell_Mode(void);

#endif









