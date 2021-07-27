#ifndef oled
#define oled
#include "main.h"
extern SPI_HandleTypeDef hspi1;
#include "font.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdlib.h"	
#include "stdio.h"	
#include "string.h"
#define WriteCmd OLED_WrCmd
#define WriteDat OLED_WrData
static const char flow[8][200];
void OLED_WrCmd(uint8_t command);
void OLED_WrData(uint8_t data);
void OLED_Init();
void OLED_Clear(void);
void OLED_Start(void);
void OLED_SetPos(uint8_t x, uint8_t y);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowChar(int x,int y,char txt[]);
void OLED_ShowNum(int y,int x,int num);
void OLED_ShowNums(int y,int x,int num,int len);
void OLED_Close_page(void);
void OLED_page2(void);
void OLED_ShowWord(int x,int y,int f);
#endif