/*
 * uartBsp.h
 *
 *  Created on: 2019Äê1ÔÂ22ÈÕ
 *      Author: shi
 */

#ifndef UARTBSP_H_
#define UARTBSP_H_

/*****************************************  Include  ******************************************************/
#include "typedef.h"
#include "stm32f4xx_hal.h"

/******************************************  Global macro definition  ******************************************/

/******************************************  Global type definition  *******************************************/

/******************************************  Global variable declaration  **************************************/


extern DMA_HandleTypeDef hdma_usart6_rx;

extern UART_HandleTypeDef huart6;

/******************************************  Global function declaration  **************************************/
//void vSendData2LeftScreen (U8* pData, U8 len);
//void vSendData2RightScreen (U8* pData, U8 len);
//
//
void vSendRadarData (U8* pData, U8 len);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void vUartRecvIDLE_CallBack(UART_HandleTypeDef *huart);
void vUartBspInit (void);

#endif /* UARTBSP_H_ */
