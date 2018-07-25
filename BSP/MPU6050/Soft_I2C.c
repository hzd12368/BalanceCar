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
	uint8_t i=10; //i=10��ʱ1.5us//��������Ż��ٶ� ����������͵�5����д��
  while(i--);
}

/*******************************************************************
IIC_START
������������
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
����ֹͣ����
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
* ��������:IIC_SendNACK                                                                     
* ��    ��:�յ�����,����NACK                                                                                                                                       
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
* ��������:IIC_SendACK                                                                     
* ��    ��:�յ�����,����ACK                                                                                                                                        
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
* ��������:IIC_Wait_ACK                                                                     
* ��    ��:�ȴ����豸����ACK                                                                                                                                        
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
   SCL_L;//ʱ�����0        
   return 0;    
}  
/*******************************************************************************
 * ��������:IIC_SendByte                                                                     
 * ��    ��:����һ���ֽ�                                                                                                                                      
 *******************************************************************************/
void IIC_SendByte(uint8_t Data)
{
	uint8_t t;       
	SCL_L;//����ʱ�ӿ�ʼ���ݴ���  
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
 * ��������:IIC_ReceiveByte                                                                     
 * ��    ��:����һ���ֽ�                                                                                                                                       
 *******************************************************************************/
uint8_t IIC_RecvByte(void)
{
	 uint8_t i,Data = 0;
	 SDA_H;
	 SCL_L; 
	 Data=0;
	 for(i=0;i<8;i++)
	 {
		SCL_H;		//����ʱ��������[������],�ôӻ�׼�������� 
		IIC_Delay(); 
		Data<<=1;
		if(Read_SDA) //������״̬
		{
			Data|=0x01; 
		}   
		SCL_L;//׼�����ٴν�������  
		IIC_Delay();//�ȴ�����׼����         
	 }
	 return Data;
}
/******���ֽ�д��*******************************************/
void Single_Write_IIC(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)
{
    IIC_Start();                  //��ʼ�ź�
    IIC_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
		IIC_Wait_Ack();
    IIC_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ
		IIC_Wait_Ack();
    IIC_SendByte(REG_data);       //�ڲ��Ĵ�������
		IIC_Wait_Ack();
    IIC_Stop();                   //����ֹͣ�ź�
}

/********���ֽڶ�ȡ*****************************************/
uint8_t Single_Read_IIC(uint8_t SlaveAddress, uint8_t REG_Address)
{  
		uint8_t REG_data;
    IIC_Start();                          //��ʼ�ź�
    IIC_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
		IIC_Wait_Ack();
    IIC_SendByte(REG_Address);            //���ʹ洢��Ԫ��ַ��//��0��ʼ	
		IIC_Wait_Ack();
    IIC_Start();                          //��ʼ�ź�
    IIC_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
		IIC_Wait_Ack();
    REG_data = IIC_RecvByte();            //�����Ĵ�������
// 		IIC_Wait_Ack();
		IIC_SendNACK();   
		IIC_Stop();                           //ֹͣ�ź�
    return REG_data; 
}

