//////////////////////////////////////////////////////////////////////////////////	 

//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
#include "main.h"
//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//#define u8 unsigned char
//#define u32 unsigned int	
 
//-----------------�˿ڶ���---------------- 
#define OLED_CLK_PIN  GPIO_PIN_5
#define OLED_CLK_Port GPIOA
#define OLED_DIN_PIN  GPIO_PIN_7
#define OLED_DIN_Port GPIOA
#define OLED_RES_PIN GPIO_PIN_6
#define OLED_RES_Port GPIOA
#define OLED_DC_PIN GPIO_PIN_4
#define OLED_DC_Port GPIOA
#define OLED_CS_PIN GPIO_PIN_3
#define OLED_CS_Port GPIOA
//-----------------OLED�˿ڶ���----------------  					   


#define OLED_SCLK_Clr() HAL_GPIO_WritePin(OLED_CLK_Port, OLED_CLK_PIN, GPIO_PIN_RESET)//CLK
#define OLED_SCLK_Set() HAL_GPIO_WritePin(OLED_CLK_Port, OLED_CLK_PIN, GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(OLED_DIN_Port, OLED_DIN_PIN, GPIO_PIN_RESET)//DIN
#define OLED_SDIN_Set() HAL_GPIO_WritePin(OLED_DIN_Port, OLED_DIN_PIN, GPIO_PIN_SET)

#define OLED_RST_Clr() HAL_GPIO_WritePin(OLED_RES_Port, OLED_RES_PIN, GPIO_PIN_RESET)//RES
#define OLED_RST_Set() HAL_GPIO_WritePin(OLED_RES_Port, OLED_RES_PIN, GPIO_PIN_SET)

#define OLED_DC_Clr() HAL_GPIO_WritePin(OLED_DC_Port, OLED_DC_PIN, GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(OLED_DC_Port, OLED_DC_PIN, GPIO_PIN_SET)
 		     
#define OLED_CS_Clr()  HAL_GPIO_WritePin(OLED_CS_Port, OLED_CS_PIN, GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(OLED_CS_Port, OLED_CS_PIN, GPIO_PIN_RESET)

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_WR_Byte2(u8 dat,u8 cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowChar2(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 mod);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no,u8 mod);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void welcoms(void);
#endif  
	 



