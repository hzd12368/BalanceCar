#include "Soft_I2C.h"
#include "stm32f1xx.h"
#include "MPU6050.h"

void DelayMs(uint16_t ms);

void MPU6050_Inital(void)
{
	DelayMs( 100 );
	//½â³ýÐÝÃß
	Single_Write_IIC( SLAVEADRESS , PWR_MGMT_1 , 0x00 );
	Single_Write_IIC( SLAVEADRESS , SMPLRT_DIV , 0x07 );
	Single_Write_IIC( SLAVEADRESS , CONFIG , 0x06 );
	Single_Write_IIC( SLAVEADRESS , GYRO_CONFIG , 0x18 );
	Single_Write_IIC( SLAVEADRESS , ACCEL_CONFIG , 0x01 );
	DelayMs( 100 );
}


uint16_t getAccX(void)
{
	uint16_t AccX = 0;
	uint16_t AccXH = 0, AccXL = 0;

	AccXH = Single_Read_IIC( SLAVEADRESS , ACCEL_XOUT_H );
	AccXL = Single_Read_IIC( SLAVEADRESS , ACCEL_XOUT_L );

	AccX = (AccXH<<8)|AccXL;

	return AccX;
}

uint16_t getAccY(void)
{
	uint16_t AccY = 0;
	uint8_t AccYH = 0, AccYL = 0;

	AccYH = Single_Read_IIC( SLAVEADRESS , ACCEL_YOUT_H );
	AccYL = Single_Read_IIC( SLAVEADRESS , ACCEL_YOUT_L );

	AccY = (AccYH<<8)|AccYL;

	return AccY;
}

uint16_t getAccZ(void)
{
	uint16_t AccZ = 0;
	uint8_t AccZH = 0, AccZL = 0;

	AccZH = Single_Read_IIC( SLAVEADRESS , ACCEL_ZOUT_H );
	AccZL = Single_Read_IIC( SLAVEADRESS , ACCEL_ZOUT_L );

	AccZ = (AccZH<<8)|AccZL;

	return AccZ;
}

uint16_t getGyroX(void)
{
	uint16_t GyroX = 0;
	uint8_t GyroXH = 0, GyroXL = 0; 
	
	GyroXH = Single_Read_IIC( SLAVEADRESS , GYRO_XOUT_H );
	GyroXL = Single_Read_IIC( SLAVEADRESS , GYRO_XOUT_H );
	
	GyroX = (GyroXH<<8)|GyroXL;
	
	return GyroX;	
}

uint16_t getGyroY(void)
{
	uint16_t GyroY = 0;
	uint8_t GyroYH = 0, GyroYL = 0; 
	
	GyroYH = Single_Read_IIC( SLAVEADRESS , GYRO_YOUT_H );
	GyroYL = Single_Read_IIC( SLAVEADRESS , GYRO_YOUT_H );
	
	GyroY = (GyroYH<<8)|GyroYL;
	
	return GyroY;	
}

uint16_t getGyroZ(void)
{
  uint16_t GyroZ = 0;
	uint8_t GyroZH = 0 , GyroZL = 0; 
	
	GyroZH = Single_Read_IIC( SLAVEADRESS , GYRO_ZOUT_H );
	GyroZL = Single_Read_IIC( SLAVEADRESS , GYRO_ZOUT_H );
	
	GyroZ = (GyroZH<<8)|GyroZL;
	
	return GyroZ;	
}


uint16_t getAccXRelative(void)
{
	uint16_t AccXRelative = 0;	
	
	AccXRelative = getAccX() / REAL_ACC_K;

	return AccXRelative;
}


uint16_t getAccYRelative(void)
{
	uint16_t AccYRelative = 0;	
	
	AccYRelative = getAccY() / REAL_ACC_K;

	return AccYRelative;
}


uint16_t getAccZRelative(void)
{
	uint16_t AccZRelative = 0;	
	
	AccZRelative = getAccZ() / REAL_ACC_K;

	return AccZRelative;
}


uint16_t getGyroXRleative(void)
{
	uint16_t GyroXRleative = 0;

	GyroXRleative = getGyroX() / REAL_GYRO_K;

	return GyroXRleative;
}


uint16_t getGyroYRleative(void)
{
	uint16_t GyroYRleative = 0;

	GyroYRleative = getGyroY() / REAL_GYRO_K;

	return GyroYRleative;
}


uint16_t getGyroZRleative(void)
{
	uint16_t GyroZRleative = 0;

	GyroZRleative = getGyroZ() / REAL_GYRO_K;

	return GyroZRleative;
}


uint16_t getTemperature(void)
{
 	uint16_t temperature = 0;
	uint8_t temperatureH = 0 , temperatureL = 0;

	temperatureH = Single_Read_IIC( SLAVEADRESS , TEMP_OUT_H );
	temperatureL = Single_Read_IIC( SLAVEADRESS , TEMP_OUT_L );

	temperature = (temperatureH<<8)|temperatureL;

	return temperature;
}


void DelayMs(uint16_t ms)
{
 uint16_t iq0;
 uint16_t iq1;
 for(iq0 = ms; iq0 > 0; iq0--)
 {
  for(iq1 = 11998; iq1 > 0; iq1--); // ( (6*iq1+9)*iq0+15 ) / 72000000 
 }
}
