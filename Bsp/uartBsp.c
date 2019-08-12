/*
 * uartBsp.c
 *
 *  Created on: 2019年1月22日
 *      Author: shi
 */

/*****************************************  Include  ******************************************************/
#include "uartBsp.h"
#include <string.h>
#include "cmsis_os.h"
#include "shell.h"

/******************************************  Private mac`ro definition  ******************************************/
#define UART6_RECVBUFF_MAXLEN_M	200

/******************************************  Private type definition  *******************************************/

/******************************************  Private function declaration  **************************************/

/******************************************  Private variable definition  ***************************************/

/******************************************  Global variable definition  ****************************************/
static U8 uart6RecvBuffG[UART6_RECVBUFF_MAXLEN_M];

/******************************************  Function definition  ***********************************************/
#ifdef __GNUC__

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart6, (uint8_t*)&ch, 1, 0xff);

  return ch;

}

#endif

int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len;DataIdx++)
	{
		__io_putchar(*ptr++);
	}

	return len;
}

/*************************************************************************
  * @function:
  * @param[in]:
  * @param[out]:
  * @return:
  * @others:
**************************************************************************/
/*传输完成回调函数*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART6)
	HAL_UART_Receive_DMA(huart,uart6RecvBuffG,UART6_RECVBUFF_MAXLEN_M);
}

/*空闲中断回调函数*/
void vUartRecvIDLE_CallBack(UART_HandleTypeDef *huart) 
{

	U32 temp=0;
	static U8 dataStartAddr, len;

	if((__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET))
	{

		__HAL_UART_CLEAR_IDLEFLAG(huart);


		  
		if(huart->Instance == USART6)
		{
			temp = huart->Instance->SR;
			temp = huart->Instance->DR;
			HAL_UART_DMAStop(huart);

			if(shellRecvDataHandle.recvOkFlg == INVALID)
			{
				shellRecvDataHandle.len =  UART6_RECVBUFF_MAXLEN_M - __HAL_DMA_GET_COUNTER(&hdma_usart6_rx);


				if (shellRecvDataHandle.len <= SHELL_DATA_LEN)
				{
					memcpy(shellRecvDataHandle.pData, uart6RecvBuffG, shellRecvDataHandle.len);
					shellRecvDataHandle.recvOkFlg = VALID;

				}else
				{
					printf ("shell command lenth must not more than %d\n",SHELL_DATA_LEN);
				}
			}

			memset(uart6RecvBuffG,0x00,UART6_RECVBUFF_MAXLEN_M);

			HAL_UART_Receive_DMA(huart,uart6RecvBuffG,UART6_RECVBUFF_MAXLEN_M);
		}

	}
}

/*初始化*/
void vUartBspInit (void)
{
	__HAL_UART_ENABLE_IT(&huart6,UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart6,uart6RecvBuffG,UART6_RECVBUFF_MAXLEN_M);
}

