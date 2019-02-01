/*
 * NOKIA_5110_LCD_Driver.h
 *
 *  Created on: May 7, 2018
 *      Author: zsolt.balo
 */

#ifndef NOKIA_5110_LCD_DRIVER_H_
#define NOKIA_5110_LCD_DRIVER_H_

#include "GPIO_Driver.h"
#include "SPI_Driver.h"
#include "SYSTICK_Driver.h"

#define NOKIA_5110_DRIVER_X_RES                  	84
#define NOKIA_5110_DRIVER_Y_RES                  	48

#define NOKIA_5110_FONT_X_SIZE                    	5
#define NOKIA_5110_FONT_Y_SIZE                    	8

/*#define NOKIA_5110_DRIVER_LCD_PORT					GPIOA*/
/*Reset the Nokia 5110 Module*/
#define NOKIA_5110_DRIVER_LCD_RST_PIN				0x02
/*Nokia 5110 Data/Command selector*/
#define NOKIA_5110_DRIVER_LCD_DC_PIN				0x04

void NOKIA_5110_Driver_Init();
void NOKIA_5110_Driver_ClearScreen();
void NOKIA_5110_Driver_On();
void NOKIA_5110_Driver_Off();
void NOKIA_5110_Driver_SendCommand(uint8 Command);
void NOKIA_5110_Driver_SendByte(uint8 Command);
void NOKIA_5110_Driver_SendStr(char *Msg);
void NOKIA_5110_Driver_SendChar(uint8 ch);
void NOKIA_5110_Driver_SendNum_1(uint8 num);
void NOKIA_5110_Driver_SendNum_n(uint16 num);
void NOKIA_5110_Driver_SetXYcoordinates(uint8_t x, uint8_t y);
void NOKIA_5110_Driver_Reset();

#endif /* NOKIA_5110_LCD_DRIVER_H_ */
