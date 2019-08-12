
/*****************************************  Include  ******************************************************/
#include "shell.h"
#include "stdio.h"
#include "string.h"
#include "cmd.h"

/******************************************  Private macro definition  ******************************************/

/******************************************  Private type definition  *******************************************/

/******************************************  Private function declaration  **************************************/

/******************************************  Private variable definition  ***************************************/
U8 shellRecvBuf[SHELL_DATA_LEN];
/******************************************  Global variable definition  ****************************************/
shellRecvDataHandleT shellRecvDataHandle =
{
	.recvOkFlg = INVALID,
	.len = 0,
	.pData = shellRecvBuf
};

/******************************************  Function definition  ***********************************************/
/****************************************************************************
* 名    称：void uart_gets(uint8_t *buf, uint32_t len)
* 功    能：从终端获取一个字符串
* 入口参数：uint8_t *buf, uint32_t len
* 出口参数：无
* 说    明：shell
* 调用方法：无
****************************************************************************/


void Shell_Init (void)
{
	printf ("\n/**********start**********");
	printf ("\n1.input 'shell' to entry shell mode\r\n");
	printf ("\n2.input 'quit' to leave shell mode\r\n");
	printf ("\n3.input 'help' to display shell direction\r\n");
	printf ("\nPS:\r\n");
	printf ("\n1.uart baud:115200\r\n");
	printf ("\n2.command lenth not more than 32 chars\r\n");
	printf ("**********end**********/\n");
}


ValidStatus uart_gets(uint8_t *pCmdBuff, shellRecvDataHandleT* pDataHandle, uint32_t len)
{
	ValidStatus status = INVALID;

    int i = 0;
    uint8_t tmp = 0;

    if (VALID == pDataHandle->recvOkFlg)
    {
    	memset (pCmdBuff, 0, len);

    	while(i < (len-1))
		{
			tmp = pDataHandle->pData[i];

			if((tmp == '\r') || (tmp == 0) || (tmp == '\n'))
				break;
			else
				pCmdBuff[i] = tmp;
			i++;
		}

		pCmdBuff[i] = '\0';

		memset (pDataHandle->pData, 0, len);
		pDataHandle->recvOkFlg = INVALID;
		status = VALID;
    }

   return status;
}

/****************************************************************************
* 名    称：void Shell_Mode(void)
* 功    能：进入Shell模式
* 入口参数：无
* 出口参数：无
* 说    明：shell
* 调用方法：无
****************************************************************************/
uint8_t cmd_buf[SHELL_DATA_LEN];
void Shell_Mode(void)
{

	_cmd *ptr = (_cmd *)0;

//	memset (cmd_buf, 0, SHELL_DATA_LEN);
	/*判断是否输入进入Shell的命令*/
	if (VALID == uart_gets(cmd_buf, &shellRecvDataHandle, SHELL_DATA_LEN))			//等待输入"shell"命令
	{
		if(!strcmp((char *)cmd_buf,"help"))
		{
			ptr = find_cmd(cmd_buf);				//查找命令是否存在
			if(ptr) {
				printf("\ncall command function:%s\r\n",cmd_buf);
				ptr->cmd_func();					//命令处理函数
			}

			return;
		}

		if(!strcmp((char *)cmd_buf,"shell"))
		{
			printf("\nEntry Shell!\n");
		}
		else
		{
			printf("\nPlease input shell to entry shell mode!\n");
			return;
		}


	}
	else
	{
		return;
	}

	/*Shell模式*/
	while(1)
	{
		while (VALID != uart_gets(cmd_buf, &shellRecvDataHandle, SHELL_DATA_LEN));

		if(!strcmp((char *)cmd_buf,"quit")){	//退出Shell模式
			printf("\nQuit Shell!\n\r");
			break;
		}

		ptr = find_cmd(cmd_buf);				//查找命令是否存在
		if(ptr) {
			printf("\n/**********start**********\n1.call command function:%s\r\n2.",cmd_buf);
			ptr->cmd_func();					//命令处理函数
			printf("\n3.command function:%s run over\r\n**********end**********/\n",cmd_buf);

		}
		else{
			printf("\n/**********start**********\nUnkonwn command:%s\r\n**********end**********/\n",cmd_buf);
//			uart_puts("\nUnkonwn command ");
//			uart_puts(cmd_buf);
		}
	}

}
/****************************************************************************
* 名    称：uint8_t Kill(void)
* 功    能：杀掉当前函数
* 入口参数：无
* 出口参数：被杀返回1 无操作返回0
* 说    明：shell
* 调用方法：无
****************************************************************************/
//uint8_t Kill(void)
//{
//	uint8_t cmd_buf[32];
//
//	if(rec_f){
//		rec_f = 0;
//
//		uart_gets(cmd_buf,sizeof(cmd_buf));
//
//		if(!strcmp((char *)cmd_buf,"kill")){		//结束函数执行
//			printf("\nFunction terminated+\n");
//			return 1;
//		}
//		else
//			return 0;
//
//	}
//	return 0;
//}


