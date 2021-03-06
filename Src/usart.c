/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "stdio.h"
#include "gpio.h"

/* USER CODE BEGIN 0 */
u8 buf[16];
int BUF_L = 0;
/* USER CODE END 0 */
uint8_t *res;
uint8_t ret;
UART_HandleTypeDef huart1;
u8 V_Targe;
/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_USART1_ENABLE();

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
//int fputc(int ch, FILE *f) 
//{
//	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
//	 
//	return ch;
//}
//int fgetc(FILE *f)
//{uint8_t ch = 0;
//	HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
//	return ch;
//}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)  
{  
	
	if (UartHandle->Instance == USART1)
	{
		if(HAL_UART_Receive_IT(UartHandle, (uint8_t *)res, 1) != HAL_OK)              //���������ж�
			{
				while (1);
			}
		ret = *res;
		if (state == 255) {
			buf[BUF_L] = ret;
			BUF_L++;
			if (ret == 0xFF && BUF_L == 7) {
				state = 254;
			}
			if (BUF_L > 7) {
				BUF_L = 0;
				state = 0;
			}
			return;
		}
		switch (*res) {
		case 'O':
			state = 1;

			break;
		case 'B':
			state = 2;

			break;
		case 'E':
			state = 3;

			break;
		case 'R':
			state = 4;

			break;
		case 'P':
			state = 5;

			break;
		case 'T':
			state = 6;

			break;
		case 'S':
			state = 7;

			break;
		case 'J':
			state = 8;

			break;
		case 'Q':
			state = 9;

			break;
		case 0xEE:
			buf[0] = 0xEE;
			BUF_L = 1;
			state = 255;
			break;
		default:
			break;
		}
	}
} 
void Decoder_(u8 *code)
{
	if (code[0] != 0xEE || code[6] != 0xFF || code[5] != ((code[1] + code[2] + code[3] + code[4]) & 0x7F)) return;	
	//printf("Decoder....\r\n");
	HandlingData(code[1], code[2], code[3], code[4]);	
	
}

void HandlingData(u8 index, u8 data_H, u8 data_L, u8 Func) {
	//printf("I will handle Data.\r\n");	
	//	printf("index = %x,data_H = %x,data_L = %x, Func = %x\r\n", index ,data_H,data_L , Func);
	switch(Func)
	{
		

	
	case 0x10:
		{
			if (index == 0x01) {
				//printf("data_H = %d.\r\n", data_H);
				MotorA_Ctr(data_H);
				//printf("data_L = %d.\r\n", data_L);
				if (data_L != 0x00) {
					V_Targe = data_L;
				}
			}
			break;
		}		
	}
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/