#ifndef _I2C_H_
#define _I2C_H_
#include "stm32f1xx.h"

#define IIC_SCL GPIO_PIN_15
#define IIC_SCL_GPIO_Port GPIOB
#define IIC_SDA GPIO_PIN_14
#define IIC_SDA_GPIO_Port GPIOB

#define SCL_H   HAL_GPIO_WritePin(IIC_SCL_GPIO_Port, IIC_SCL, GPIO_PIN_SET)
#define SCL_L   HAL_GPIO_WritePin(IIC_SCL_GPIO_Port, IIC_SCL, GPIO_PIN_RESET)

#define SDA_H  HAL_GPIO_WritePin(IIC_SDA_GPIO_Port, IIC_SDA, GPIO_PIN_SET)
#define SDA_L	HAL_GPIO_WritePin(IIC_SDA_GPIO_Port, IIC_SDA, GPIO_PIN_RESET)

#define Read_SDA	HAL_GPIO_ReadPin(IIC_SDA_GPIO_Port, IIC_SDA)
#define Read_SCL	HAL_GPIO_ReadPin(IIC_SCL_GPIO_Port, IIC_SCL)

enum IIC_REPLAY_ENUM
{
	IIC_NACK = 0,
	IIC_ACK = 1
};

enum IIC_BUS_STATE_ENUM
{
	IIC_BUS_READY = 0,
	IIC_BUS_BUSY = 1,
	IIC_BUS_ERROR = 2
};
extern void IIC_GPIO_Config(void);
extern void IIC_SendByte(uint8_t Data);
extern uint8_t IIC_RecvByte(void);
extern uint8_t Single_Read_IIC(uint8_t SlaveAddress, uint8_t REG_Address);
extern void Single_Write_IIC(uint8_t SlaveAddress, uint8_t REG_Address, uint8_t REG_data);
#endif
