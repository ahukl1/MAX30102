	
#include "main.h"
extern SPI_HandleTypeDef hspi1;
#define u8 unsigned char
/*****************************************************************************
 * @name       :u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
 * @date       :2018-08-27 
 * @function   :Write a byte of data using STM32's hardware SPI
 * @parameters :SPIx: SPI type,x for 1,2,3
                Byte:Data to be written
 * @retvalue   :Data received by the bus
******************************************************************************/
unsigned char SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
{
    HAL_SPI_Transmit(&hspi1,&Byte,1,1000);	
}

