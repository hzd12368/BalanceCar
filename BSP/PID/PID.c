
#include "pid.h"

//static PID *Speed_Point = &Speed_PID; 
/*==================================================================================================== 
Initialize PID Structure PID?????
=====================================================================================================*/ 
void Speed_PIDInit(void) 
{ 
	Speed_PID.Target = Set_Point;
	Speed_PID.Uk		= 0;
	Speed_PID.Udk    = 0;
	Speed_PID.Uk_1   = PWM_Min;
	Speed_PID.ek_0 	= 0;	 //ek=0
	Speed_PID.ek_1 	= 0;	 //ek-1=0
	Speed_PID.ek_2 	= 0; 	 //ek-2=0
	Speed_PID.P 		= 50.0f;  //Proportional Const 
	Speed_PID.I 		= 0.35f; 	 //0.15
	Speed_PID.b      = 10; 
	Speed_PID.D 		= 1.80f; 	 //1.8,3.0
}
/*==================================================================================================== 

=====================================================================================================*/ 
 	float P_TMP = 1.2f; 		
	float I_TMP = 1.0f; 		
	float b_TMP = 0.0599999987; 
	float D_TMP = 0.0899999961f;
	float b1 = 0.02;
	float b2 = 1.8f;
int16_t Udk;
int16_t Uk;
int16_t Uk_1;
int ek_2;
int ek_1;
int ek_0;
int Speed_PIDAdjust(float Target,float Real)
{ 
	Speed_PID.P = P_TMP; 		
	Speed_PID.I = I_TMP; 		
	Speed_PID.b = b_TMP; 
	Speed_PID.D = D_TMP;
	Speed_PID.ek_0= Target - Real; 
	ek_0  = Speed_PID.ek_0;
	if(((Speed_PID.Uk_1>=PWM_Max)&&(Speed_PID.ek_0>=0))||((Speed_PID.Uk_1<=PWM_Min)&&(Speed_PID.ek_0<=0)))
	{//???????
	    Speed_PID.b=0;
	} 
	else 
	{	
		if(fabs(Speed_PID.ek_0)<1)
			Speed_PID.b=b1;
		else
			Speed_PID.b=b2;
	} //?????PID
	Speed_PID.Udk = Speed_PID.P*(Speed_PID.ek_0 - Speed_PID.ek_1) + Speed_PID.b*Speed_PID.I*Speed_PID.ek_0;
	Udk = Speed_PID.Udk;
//	Speed_PID.Udk=Speed_PID.P*(Speed_PID.ek_0-Speed_PID.ek_1)+Speed_PID.b*Speed_PID.I*Speed_PID.ek_0
//	+ Speed_PID.D*(Speed_PID.ek_0-2*Speed_PID.ek_1+Speed_PID.ek_2);
	Uk_1 = Speed_PID.Uk_1;
	Speed_PID.Uk_1 =Speed_PID.Udk+Speed_PID.Uk_1;
	
	Speed_PID.ek_2 =	Speed_PID.ek_1;
	ek_2 = Speed_PID.ek_2;
	
	Speed_PID.ek_1 = Speed_PID.ek_0;
	ek_1 = Speed_PID.ek_1;
	
	Speed_PID.Uk=Speed_PID.Uk_1;
	Uk = Speed_PID.Uk;
	
    if(Speed_PID.Uk >= PWM_Max)
	{
		return PWM_Max/10;
	}
	else if(Speed_PID.Uk < PWM_Min)
	{
		return PWM_Min/10;
	} 
	return(Speed_PID.Uk/10); 
}


