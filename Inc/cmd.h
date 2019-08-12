#ifndef __CMD_H_
#define __CMD_H_

/*****************************************  Include  ******************************************************/
#include "typedef.h"
#include "stm32f4xx_hal.h"

/******************************************  Global macro definition  ******************************************/

/******************************************  Global type definition  *******************************************/
typedef struct cmd
{
    char *cmd_name;//命令
    void (*cmd_func)(void);//对应处理函数
}_cmd;
/******************************************  Global variable declaration  **************************************/


/******************************************  Global function declaration  **************************************/
extern _cmd *find_cmd(uint8_t *user_cmd);




#endif	//__CMD_H__










