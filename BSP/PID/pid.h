#ifndef _PID_H
#define _PID_H

#include "math.h"
#include "usart.h"
extern void Speed_PIDInit(void);
extern int Speed_PIDAdjust(float Target,float Real);
extern int Position_controll(float P_Target,float P_Real);
#define Set_Point	25.0	
#define PWM_Max		2000
#define PWM_Min   0  
typedef struct PID 
{ 
	float Target;    
	int16_t Uk;			
	int16_t Udk;		
	int16_t Uk_1; 		
	float P; 		
	float I; 		
	float b; 
	float D; 		
	int16_t ek_0;		
	int16_t ek_1; 		
	int16_t ek_2; 		
}PID;
static PID Speed_PID; 
#endif
