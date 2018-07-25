#include "Motor.h"
#include "gpio.h"
#include "stm32f1xx_hal_gpio.h"
#include "math.h"
#include "tim.h"

u16 EncodeLast[EncodeBuffLen] = { 0 };
u16 EncodeNow = 0;
u16 sum = 0;
u16 err[EncodeBuffLen] = { 0 };


u16 Search(u16 a[], int len)
{
	int max = 0; //保持到目前为此出现次数最多的那个数
	int count = 1;
	int maxnum = count; //保存最大计数次
	int maxd;
	int i,j;
	int t =  0;

	//冒泡法
	for (i = 0; i < len; i++)
	{
		for (j = i + 1; j < len; j++) {
			if (a[i] > a[j])
			{
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
	
	for (i = 0; i < len - 1; i++)
	{

		max = a[i];
		if (a[i + 1] == max)
			count++;
		else
			count = 1;
		if (count > maxnum)
		{
			maxnum = count;
			maxd = max;
		}
	}
	return maxd;
}	

u16 GetEncodeCount(void)
{
	int i;
	sum = 0;
	
	for ( i = 1; i < EncodeBuffLen; i++)
	{
		err[i - 1] = EncodeLast[i] - EncodeLast[i - 1];
		EncodeLast[i - 1] = EncodeLast[i];
		if (err[i - 1] > 0x0f00) {
			err[i - 1] = ((~err[i - 1]) & 0x0fff);
		}
		
	}
	EncodeLast[EncodeBuffLen - 1] = EncodeNow;
	EncodeNow = (u16)(__HAL_TIM_GET_COUNTER(&htim2));
	err[EncodeBuffLen - 1] = fabs(EncodeNow - EncodeLast[EncodeBuffLen - 1]);


	sum = Search(err, EncodeBuffLen);

	
	return sum;
	
}
float GetV(float EncodeCount, u32 timer)
{
	//return (float)(EncodeCount * 360 * 50 / timer);
	return EncodeCount;
	
}
void MotorAforwardRotate(void)
{
	HAL_GPIO_WritePin(MotorA_IN1_GPIO_Port, MotorA_IN1_Pin, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(MotorA_IN2_GPIO_Port, MotorA_IN2_Pin, GPIO_PIN_RESET);
	
}
void MotorAbackwardRotate(void)
{
	HAL_GPIO_WritePin(MotorA_IN2_GPIO_Port, MotorA_IN2_Pin, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(MotorA_IN1_GPIO_Port, MotorA_IN1_Pin, GPIO_PIN_RESET);
	
}
void MotorBforwardRotate(void)
{
	HAL_GPIO_WritePin(MotorB_IN1_GPIO_Port, MotorB_IN1_Pin, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(MotorB_IN2_GPIO_Port, MotorB_IN2_Pin, GPIO_PIN_RESET);
	
}
void MotorBbackwardRotate(void)
{
	HAL_GPIO_WritePin(MotorB_IN2_GPIO_Port, MotorB_IN2_Pin, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(MotorB_IN1_GPIO_Port, MotorB_IN1_Pin, GPIO_PIN_RESET);
	
}

void MotorAStop(void)
{
	TIM_SetTIM1Compare1(0);
	HAL_GPIO_WritePin(MotorA_IN1_GPIO_Port, MotorA_IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MotorA_IN2_GPIO_Port, MotorA_IN2_Pin, GPIO_PIN_RESET);
	
}
void MotorBStop(void)
{
	TIM_SetTIM1Compare2(0);
	HAL_GPIO_WritePin(MotorB_IN1_GPIO_Port, MotorB_IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MotorB_IN2_GPIO_Port, MotorB_IN2_Pin, GPIO_PIN_RESET);
	
}
void MotorAVSet(u8 v)
{
	TIM_SetTIM1Compare1(v);		
}
void MotorBVSet(u8 v)
{
	TIM_SetTIM1Compare2(v);		
}

void MotorA_Ctr(u8 state) {
	if (state == 0) {
		MotorAStop();
		V_Targe = 0;
	}
	if (state == 1) {
		MotorAforwardRotate();
	}
	if (state == 2) {
		MotorAbackwardRotate();
	}
}
