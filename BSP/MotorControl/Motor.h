//#ifndef _MotorControl
//#define _MotorControl
#include "tim.h"
#define EncodeBuffLen 10
extern uint16_t EncodeLast[EncodeBuffLen];
extern uint16_t EncodeNow;
extern uint8_t V_Targe;
uint16_t GetEncodeCount(void);
float GetV(float EncodeCount, uint32_t timer);
void MotorAforwardRotate(void);
void MotorAbackwardRotate(void);
void MotorBforwardRotate(void);
void MotorBbackwardRotate(void);
void MotorAStop(void);
void MotorBStop(void);
void MotorAVSet(uint8_t v);
void MotorBVSet(uint8_t v);
void MotorA_Ctr(uint8_t state);
void MotorB_Ctr(uint8_t state);
