#ifndef _MPU6050_h_
#define _MPU6050_h_


//3?¨º??¡¥MPU6050
extern void MPU6050_Inital(void);




#define	SMPLRT_DIV		0x19	//¨ª¨®?Y¨°?2¨¦?¨´?¨º¡ê?¦Ì?D¨ª?¦Ì¡êo0x07(125Hz)
#define	CONFIG				0x1A	//¦Ì¨ª¨ª¡§??2¡§?¦Ì?¨º¡ê?¦Ì?D¨ª?¦Ì¡êo0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//¨ª¨®?Y¨°?¡Á??¨¬?¡ã2a¨¢?¡¤??¡ì¡ê?¦Ì?D¨ª?¦Ì¡êo0x18(2?¡Á??¨¬¡ê?2000deg/s)
#define	ACCEL_CONFIG	0x1C	//?¨®?¨´??¡Á??¨¬?¡é2a¨¢?¡¤??¡ì?¡ã??¨ª¡§??2¡§?¦Ì?¨º¡ê?¦Ì?D¨ª?¦Ì¡êo0x01(2?¡Á??¨¬¡ê?2G¡ê?5Hz)
#define	ACCEL_XOUT_H	0x3B	
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//¦Ì??¡ä1¨¹¨¤¨ª¡ê?¦Ì?D¨ª?¦Ì¡êo0x00(?y3¡ê??¨®?)
#define	WHO_AM_I			0x75	//IIC¦Ì??¡¤??¡ä??¡Â(??¨¨?¨ºy?¦Ì0x68¡ê????¨¢)
#define	SLAVEADRESS		0xD0	//IICD¡ä¨¨?¨º¡À¦Ì?¦Ì??¡¤¡Á??¨²¨ºy?Y¡ê?+1?a?¨¢¨¨?

#define REAL_ACC_K		50.0
#define REAL_GYRO_K		131.0

//??¨¨??-¨º?¨ºy?Y
//??¨¨??¨®?¨´?¨¨??¦Ì??¦Ì
extern uint16_t getAccX(void);
extern uint16_t getAccY(void);
extern uint16_t getAccZ(void);

//??¨¨?¨ª¨®?Y¨°?¦Ì??¦Ì
extern uint16_t getGyroX(void);
extern uint16_t getGyroY(void);
extern uint16_t getGyroZ(void);

//??¨¨??¨¤???¦Ì
//??¨¨??¨®?¨´?¨¨??¦Ì??¦Ì
extern uint16_t getAccXRelative(void);
extern uint16_t getAccYRelative(void);
extern uint16_t getAccZRelative(void);

//??¨¨?¨ª¨®?Y¨°?¦Ì??¦Ì
extern uint16_t getGyroXRleative(void);
extern uint16_t getGyroYRleative(void);
extern uint16_t getGyroZRleative(void);

//??¨¨????¨¨
extern uint16_t getTemperature(void);

#endif

