#include "stm32f1xx.h"
//#include "hw_config.h"
#include "Soft_I2C.h"
#include "gpio.h"
#include "main.h"
void IIC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin = IIC_SCL | IIC_SDA;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	SCL_H;
	SDA_H;
}

void IIC_Delay(void)
{
	uint8_t i=10; //i=10延时1.5us//这里可以优化速度 ，经测试最低到5还能写入
  while(i--);
}

/*******************************************************************
IIC_START
发送启动数据
*******************************************************************/
uint8_t IIC_Start(void)
{
	SDA_H;
	IIC_Delay();

	SCL_H;
	IIC_Delay();

	if(Read_SDA == RESET)
	{
		return IIC_BUS_BUSY;
	}

	SDA_L;
	IIC_Delay();

	SCL_L;
	IIC_Delay();

	if(Read_SCL == SET)
	{
		return IIC_BUS_ERROR;
	}

	return IIC_BUS_READY;
}

/*******************************************************************
IIC_STOP
发送停止数据
*******************************************************************/
void IIC_Stop(void)
{
	SDA_L;
	IIC_Delay();

	SCL_H;
	IIC_Delay();

	SDA_H;
	IIC_Delay();
}

/*******************************************************************************
* 函数名称:IIC_SendNACK                                                                     
* 描    述:收到数据,发送NACK                                                                                                                                       
 *******************************************************************************/
void IIC_SendNACK(void)
{
	SCL_L;
	IIC_Delay();
	SDA_H;
	IIC_Delay();
	SCL_H;
	IIC_Delay();
	SCL_L; 
	IIC_Delay(); 
}

/*******************************************************************************
* 函数名称:IIC_SendACK                                                                     
* 描    述:收到数据,发送ACK                                                                                                                                        
*******************************************************************************/
void IIC_SendACK(void)
{
	SCL_L;
	IIC_Delay();
	SDA_L;
	IIC_Delay();
	SCL_H;
	IIC_Delay();
	SCL_L; 
	IIC_Delay();
}
/*******************************************************************************
* 函数名称:IIC_Wait_ACK                                                                     
* 描    述:等待从设备返回ACK                                                                                                                                        
*******************************************************************************/
uint8_t IIC_Wait_Ack(void)  
{  
  uint8_t ucErrTime=0;    
  SDA_H;
	IIC_Delay();       
  SCL_H;
	IIC_Delay();     
  while(Read_SDA)  
   {  
     ucErrTime++;  
     if(ucErrTime>250)  
      {  
        IIC_Stop();  
        return 1;  
      }  
   }  
   SCL_L;//时钟输出0        
   return 0;    
}  
/*******************************************************************************
 * 函数名称:IIC_SendByte                                                                     
 * 描    述:发送一个字节                                                                                                                                      
 *******************************************************************************/
void IIC_SendByte(uint8_t Data)
{
	uint8_t t;       
	SCL_L;//拉低时钟开始数据传输  
  for(t=0;t<8;t++)  
   {                
     if(Data&0x80)
			{
				SDA_H;
			}
		 else
			{
				SDA_L;
			}  
     Data<<=1;      
     IIC_Delay();    
     SCL_H;  
     IIC_Delay();   
     SCL_L;    
     IIC_Delay();  
   }
}
/*******************************************************************************
 * 函数名称:IIC_ReceiveByte                                                                     
 * 描    述:接收一个字节                                                                                                                                       
 *******************************************************************************/
uint8_t IIC_RecvByte(void)
{
	 uint8_t i,Data = 0;
	 SDA_H;
	 SCL_L; 
	 Data=0;
	 for(i=0;i<8;i++)
	 {
		SCL_H;		//产生时钟上升沿[正脉冲],让从机准备好数据 
		IIC_Delay(); 
		Data<<=1;
		if(Read_SDA) //读引脚状态
		{
			Data|=0x01; 
		}   
		SCL_L;//准备好再次接收数据  
		IIC_Delay();//等待数据准备好         
	 }
	 return Data;
}
/******单字节写入*******************************************/
void Single_Write_IIC(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)
{
    IIC_Start();                  //起始信号
    IIC_SendByte(SlaveAddress);   //发送设备地址+写信号
		IIC_Wait_Ack();
    IIC_SendByte(REG_Address);    //内部寄存器地址
		IIC_Wait_Ack();
    IIC_SendByte(REG_data);       //内部寄存器数据
		IIC_Wait_Ack();
    IIC_Stop();                   //发送停止信号
}

/********单字节读取*****************************************/
uint8_t Single_Read_IIC(uint8_t SlaveAddress, uint8_t REG_Address)
{  
		uint8_t REG_data;
    IIC_Start();                          //起始信号
    IIC_SendByte(SlaveAddress);           //发送设备地址+写信号
		IIC_Wait_Ack();
    IIC_SendByte(REG_Address);            //发送存储单元地址，//从0开始	
		IIC_Wait_Ack();
    IIC_Start();                          //起始信号
    IIC_SendByte(SlaveAddress+1);         //发送设备地址+读信号
		IIC_Wait_Ack();
    REG_data = IIC_RecvByte();            //读出寄存器数据
// 		IIC_Wait_Ack();
		IIC_SendNACK();   
		IIC_Stop();                           //停止信号
    return REG_data; 
}

