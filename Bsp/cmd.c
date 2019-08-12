
/*****************************************  Include  ******************************************************/
#include "cmd.h"
#include "string.h"
/******************************************  Private macro definition  ******************************************/

/******************************************  Private type definition  *******************************************/

/******************************************  Private function declaration  **************************************/

/******************************************  Private variable definition  ***************************************/

/******************************************  Global variable definition  ****************************************/
/*支持的命令处理函数*/
static void Hello(void);
static void Help (void);
/******************************************  Function definition  ***********************************************/


/**************************************************************************
  * @function: 
  * @param[in]: 
  * @param[out]: 
  * @return: 
  * @others: 
***************************************************************************/
_cmd cmd_list[]=
{
	{"help",Help},
	{"hello",Hello},
};
/****************************************************************************
* 名    称：_cmd *find_cmd(char *user_cmd)
* 功    能：查找命令对应的执行函数
* 入口参数：char *user_cmd
* 出口参数：_cmd *
* 说    明：
* 调用方法：无
****************************************************************************/
_cmd *find_cmd(uint8_t *user_cmd)
{
    uint32_t i = 0;
    for(i = 0; i<sizeof(cmd_list)/sizeof(cmd_list[0]); i++){
        if(strcmp((char *)user_cmd, cmd_list[i].cmd_name) == 0)
            return &(cmd_list[i]);
    }
    return (_cmd *)0;
}
static void Hello(void)
{
	printf("Hello,this is my shell!");
}

static void Help (void)
{
	printf ("\n1.input 'shell' to entry shell mode\r\n");
	printf ("\n2.input 'quit' to leave shell mode\r\n");
}














