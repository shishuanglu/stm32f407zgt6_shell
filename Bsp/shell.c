
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
* ��    �ƣ�void uart_gets(uint8_t *buf, uint32_t len)
* ��    �ܣ����ն˻�ȡһ���ַ���
* ��ڲ�����uint8_t *buf, uint32_t len
* ���ڲ�������
* ˵    ����shell
* ���÷�������
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
* ��    �ƣ�void Shell_Mode(void)
* ��    �ܣ�����Shellģʽ
* ��ڲ�������
* ���ڲ�������
* ˵    ����shell
* ���÷�������
****************************************************************************/
uint8_t cmd_buf[SHELL_DATA_LEN];
void Shell_Mode(void)
{

	_cmd *ptr = (_cmd *)0;

//	memset (cmd_buf, 0, SHELL_DATA_LEN);
	/*�ж��Ƿ��������Shell������*/
	if (VALID == uart_gets(cmd_buf, &shellRecvDataHandle, SHELL_DATA_LEN))			//�ȴ�����"shell"����
	{
		if(!strcmp((char *)cmd_buf,"help"))
		{
			ptr = find_cmd(cmd_buf);				//���������Ƿ����
			if(ptr) {
				printf("\ncall command function:%s\r\n",cmd_buf);
				ptr->cmd_func();					//�������
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

	/*Shellģʽ*/
	while(1)
	{
		while (VALID != uart_gets(cmd_buf, &shellRecvDataHandle, SHELL_DATA_LEN));

		if(!strcmp((char *)cmd_buf,"quit")){	//�˳�Shellģʽ
			printf("\nQuit Shell!\n\r");
			break;
		}

		ptr = find_cmd(cmd_buf);				//���������Ƿ����
		if(ptr) {
			printf("\n/**********start**********\n1.call command function:%s\r\n2.",cmd_buf);
			ptr->cmd_func();					//�������
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
* ��    �ƣ�uint8_t Kill(void)
* ��    �ܣ�ɱ����ǰ����
* ��ڲ�������
* ���ڲ�������ɱ����1 �޲�������0
* ˵    ����shell
* ���÷�������
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
//		if(!strcmp((char *)cmd_buf,"kill")){		//��������ִ��
//			printf("\nFunction terminated+\n");
//			return 1;
//		}
//		else
//			return 0;
//
//	}
//	return 0;
//}


