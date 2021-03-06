/*
 * NOKIA_5110_LCD_Driver.c
 *
 *  Created on: May 7, 2018
 *      Author: zsolt.balo
 */

#include "NOKIA_5110_LCD_Driver_Cfg.h"

static const uint8_t  NOKIA_5110_LCD_Characters [][NOKIA_5110_FONT_X_SIZE] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00 },   /* space */
    { 0x00, 0x00, 0x2f, 0x00, 0x00 },   /* ! */
    { 0x00, 0x07, 0x00, 0x07, 0x00 },   /* " */
    { 0x14, 0x7f, 0x14, 0x7f, 0x14 },   /* # */
    { 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   /* $ */
    { 0xc4, 0xc8, 0x10, 0x26, 0x46 },   /* % */
    { 0x36, 0x49, 0x55, 0x22, 0x50 },   /* & */
    { 0x00, 0x05, 0x03, 0x00, 0x00 },   /* ' */
    { 0x00, 0x1c, 0x22, 0x41, 0x00 },   /* ( */
    { 0x00, 0x41, 0x22, 0x1c, 0x00 },   /* ) */
    { 0x14, 0x08, 0x3E, 0x08, 0x14 },   /* * */
    { 0x08, 0x08, 0x3E, 0x08, 0x08 },   /* + */
    { 0x00, 0x00, 0x50, 0x30, 0x00 },   /* , */
    { 0x10, 0x10, 0x10, 0x10, 0x10 },   /* - */
    { 0x00, 0x60, 0x60, 0x00, 0x00 },   /* . */
    { 0x20, 0x10, 0x08, 0x04, 0x02 },   /* / */
    { 0x3E, 0x51, 0x49, 0x45, 0x3E },   /* 0 */
    { 0x00, 0x42, 0x7F, 0x40, 0x00 },   /* 1 */
    { 0x42, 0x61, 0x51, 0x49, 0x46 },   /* 2 */
    { 0x21, 0x41, 0x45, 0x4B, 0x31 },   /* 3 */
    { 0x18, 0x14, 0x12, 0x7F, 0x10 },   /* 4 */
    { 0x27, 0x45, 0x45, 0x45, 0x39 },   /* 5 */
    { 0x3C, 0x4A, 0x49, 0x49, 0x30 },   /* 6 */
    { 0x01, 0x71, 0x09, 0x05, 0x03 },   /* 7 */
    { 0x36, 0x49, 0x49, 0x49, 0x36 },   /* 8 */
    { 0x06, 0x49, 0x49, 0x29, 0x1E },   /* 9 */
    { 0x00, 0x36, 0x36, 0x00, 0x00 },   /* : */
    { 0x00, 0x56, 0x36, 0x00, 0x00 },   /* ; */
    { 0x08, 0x14, 0x22, 0x41, 0x00 },   /* < */
    { 0x14, 0x14, 0x14, 0x14, 0x14 },   /* = */
    { 0x00, 0x41, 0x22, 0x14, 0x08 },   /* > */
    { 0x02, 0x01, 0x51, 0x09, 0x06 },   /* ? */
    { 0x32, 0x49, 0x59, 0x51, 0x3E },   /* @ */
    { 0x7E, 0x11, 0x11, 0x11, 0x7E },   /* A */
    { 0x7F, 0x49, 0x49, 0x49, 0x36 },   /* B */
    { 0x3E, 0x41, 0x41, 0x41, 0x22 },   /* C */
    { 0x7F, 0x41, 0x41, 0x22, 0x1C },   /* D */
    { 0x7F, 0x49, 0x49, 0x49, 0x41 },   /* E */
    { 0x7F, 0x09, 0x09, 0x09, 0x01 },   /* F */
    { 0x3E, 0x41, 0x49, 0x49, 0x7A },   /* G */
    { 0x7F, 0x08, 0x08, 0x08, 0x7F },   /* H */
    { 0x00, 0x41, 0x7F, 0x41, 0x00 },   /* I */
    { 0x20, 0x40, 0x41, 0x3F, 0x01 },   /* J */
    { 0x7F, 0x08, 0x14, 0x22, 0x41 },   /* K */
    { 0x7F, 0x40, 0x40, 0x40, 0x40 },   /* L */
    { 0x7F, 0x02, 0x0C, 0x02, 0x7F },   /* M */
    { 0x7F, 0x04, 0x08, 0x10, 0x7F },   /* N */
    { 0x3E, 0x41, 0x41, 0x41, 0x3E },   /* O */
    { 0x7F, 0x09, 0x09, 0x09, 0x06 },   /* P */
    { 0x3E, 0x41, 0x51, 0x21, 0x5E },   /* Q */
    { 0x7F, 0x09, 0x19, 0x29, 0x46 },   /* R */
    { 0x46, 0x49, 0x49, 0x49, 0x31 },   /* S */
    { 0x01, 0x01, 0x7F, 0x01, 0x01 },   /* T */
    { 0x3F, 0x40, 0x40, 0x40, 0x3F },   /* U */
    { 0x1F, 0x20, 0x40, 0x20, 0x1F },   /* V */
    { 0x3F, 0x40, 0x38, 0x40, 0x3F },   /* W */
    { 0x63, 0x14, 0x08, 0x14, 0x63 },   /* X */
    { 0x07, 0x08, 0x70, 0x08, 0x07 },   /* Y */
    { 0x61, 0x51, 0x49, 0x45, 0x43 },   /* Z */
    { 0x00, 0x7F, 0x41, 0x41, 0x00 },   /* [ */
    { 0x55, 0x2A, 0x55, 0x2A, 0x55 },   /* \ */
    { 0x00, 0x41, 0x41, 0x7F, 0x00 },   /* ] */
    { 0x04, 0x02, 0x01, 0x02, 0x04 },   /* ^ */
    { 0x40, 0x40, 0x40, 0x40, 0x40 },   /* _ */
    { 0x00, 0x01, 0x02, 0x04, 0x00 },   /* ' */
    { 0x20, 0x54, 0x54, 0x54, 0x78 },   /* a */
    { 0x7F, 0x48, 0x44, 0x44, 0x38 },   /* b */
    { 0x38, 0x44, 0x44, 0x44, 0x20 },   /* c */
    { 0x38, 0x44, 0x44, 0x48, 0x7F },   /* d */
    { 0x38, 0x54, 0x54, 0x54, 0x18 },   /* e */
    { 0x08, 0x7E, 0x09, 0x01, 0x02 },   /* f */
    { 0x0C, 0x52, 0x52, 0x52, 0x3E },   /* g */
    { 0x7F, 0x08, 0x04, 0x04, 0x78 },   /* h */
    { 0x00, 0x44, 0x7D, 0x40, 0x00 },   /* i */
    { 0x20, 0x40, 0x44, 0x3D, 0x00 },   /* j */
    { 0x7F, 0x10, 0x28, 0x44, 0x00 },   /* k */
    { 0x00, 0x41, 0x7F, 0x40, 0x00 },   /* l */
    { 0x7C, 0x04, 0x18, 0x04, 0x78 },   /* m */
    { 0x7C, 0x08, 0x04, 0x04, 0x78 },   /* n */
    { 0x38, 0x44, 0x44, 0x44, 0x38 },   /* o */
    { 0x7C, 0x14, 0x14, 0x14, 0x08 },   /* p */
    { 0x08, 0x14, 0x14, 0x18, 0x7C },   /* q */
    { 0x7C, 0x08, 0x04, 0x04, 0x08 },   /* r */
    { 0x48, 0x54, 0x54, 0x54, 0x20 },   /* s */
    { 0x04, 0x3F, 0x44, 0x40, 0x20 },   /* t */
    { 0x3C, 0x40, 0x40, 0x20, 0x7C },   /* u */
    { 0x1C, 0x20, 0x40, 0x20, 0x1C },   /* v */
    { 0x3C, 0x40, 0x30, 0x40, 0x3C },   /* w */
    { 0x44, 0x28, 0x10, 0x28, 0x44 },   /* x */
    { 0x0C, 0x50, 0x50, 0x50, 0x3C },   /* y */
    { 0x44, 0x64, 0x54, 0x4C, 0x44 },   /* z */
    { 0x00, 0x08, 0x36, 0x41, 0x00 },   /* { */
    { 0x00, 0x00, 0x7F, 0x00, 0x00 },   /* | */
    { 0x00, 0x41, 0x36, 0x08, 0x00 },   /* } */
};

void NOKIA_5110_Driver_Init()
{
	/*Init SPI interface*/
	/*SPI_Driver_Init(SPI1);
	SPI_Driver_Start(SPI1);
*/
	/*Restart Nokia 5110 Display*/
	NOKIA_5110_Driver_Reset();

	/* Send configuration commands to LCD */
	NOKIA_5110_Driver_SendCommand(0x21);/* LCD extended commands */
	NOKIA_5110_Driver_SendCommand(0xC0);/*Set Contrast*/
	NOKIA_5110_Driver_SendCommand(0x04);/*Temp Coef 2*/
	NOKIA_5110_Driver_SendCommand(0x14);/*Set bias to 4*/

	NOKIA_5110_Driver_SendCommand(0x20);/*use basic instruction set*/
	NOKIA_5110_Driver_SendCommand(0x0c);/*display normal mode*/

	NOKIA_5110_Driver_SetXYcoordinates(0x00,0x00);
	NOKIA_5110_Driver_SendCommand(0x0c);/*display normal mode*/

	NOKIA_5110_Driver_ClearScreen(); /* Clear LCD */
}

void NOKIA_5110_Driver_ClearScreen()
{
	uint32_t i, j;

	for (i = 0; i < NOKIA_5110_DRIVER_Y_RES/NOKIA_5110_FONT_Y_SIZE; i++)
	{
		NOKIA_5110_Driver_SetXYcoordinates(0, i);
	    for (j = 0; j < NOKIA_5110_DRIVER_X_RES; j++)
	    	NOKIA_5110_Driver_SendByte(0x00);
	 }
}

void NOKIA_5110_Driver_SendCommand(uint8 Command)
{
	/*GPIO_Driver_ClearPin(NOKIA_5110_DRIVER_LCD_PORT,NOKIA_5110_DRIVER_LCD_DC_PIN);*/
	/*SPI_Driver_Transcieve_Data(SPI1,Command);*/
}

void NOKIA_5110_Driver_SendByte(uint8 Data)
{
	/*GPIO_Driver_SetPin(NOKIA_5110_DRIVER_LCD_PORT,NOKIA_5110_DRIVER_LCD_DC_PIN);*/
	/*SPI_Driver_Transcieve_Data(SPI1,Data);*/
}

void NOKIA_5110_Driver_SendNum_1(uint8 num)
{
	 uint8_t i;

	  for ( i = 0; i < NOKIA_5110_FONT_X_SIZE; i++ ){
		  NOKIA_5110_Driver_SendByte(NOKIA_5110_LCD_Characters[num + 16][i]);
	  }
}

void NOKIA_5110_Driver_SendNum_n(uint16 num)
{
	if(!(num>9999))
	{
		/*Numbers of the order of thousands*/
		#if(NOKIA_5110_DRIVER_LCD_NUMBER_LEN_THOUSANDS)

			if((num/1000)!=0x00)
			{
				NOKIA_5110_Driver_SendNum_1((num/1000));
			}
			else
			{
				NOKIA_5110_Driver_SendNum_1(0x00);
			}

		#endif

		/*Numbers of the order of hundreds*/
		#if	(NOKIA_5110_DRIVER_LCD_NUMBER_LEN_HUNDREDS)
			if(((num/100)%10)!=0x00)
			{
				NOKIA_5110_Driver_SendNum_1(((num/100)%10));
			}
			else
			{
				NOKIA_5110_Driver_SendNum_1(0x00);
			}
		#endif

		/*Numbers of the order of tens*/
		#if (NOKIA_5110_DRIVER_LCD_NUMBER_LEN_TENS)
			if(((num/10)%10)!=0x00)
			{
				NOKIA_5110_Driver_SendNum_1(((num/10)%10));
			}
			else
			{
				NOKIA_5110_Driver_SendNum_1(0x00);
			}
		#endif

		/*One digit numbers*/
		if((num%10)!=0x00)
		{
			NOKIA_5110_Driver_SendNum_1((num%10));
		}
		else
		{
			NOKIA_5110_Driver_SendNum_1(0x00);
		}
	}
}

void NOKIA_5110_Driver_SendChar(uint8 ch)
{
	 uint8_t i;

	  for ( i = 0; i < NOKIA_5110_FONT_X_SIZE; i++ ){
		  NOKIA_5110_Driver_SendByte(NOKIA_5110_LCD_Characters[ch - 32][i]);
	  }
}

void NOKIA_5110_Driver_SendStr(char *Msg)
{
	uint8 index = 0x00;
	while(Msg[index])
	{
		NOKIA_5110_Driver_SendChar((uint8)Msg[index]);
		index++;
	}
}

void NOKIA_5110_Driver_SetXYcoordinates(uint8_t x, uint8_t y)
{
	if (y > NOKIA_5110_DRIVER_Y_RES/NOKIA_5110_FONT_Y_SIZE) return;
	    if (x > NOKIA_5110_DRIVER_X_RES) return;

	    NOKIA_5110_Driver_SendCommand(0x80 | x);   /* Set x position */
	    NOKIA_5110_Driver_SendCommand(0x40 | y);   /* Set y position */

}

void NOKIA_5110_Driver_Reset()
{
	/*GPIO_Driver_ClearPin(NOKIA_5110_DRIVER_LCD_PORT,NOKIA_5110_DRIVER_LCD_RST_PIN);*/
	SYSTICK_Driver_Delay_ms(10);
	/*GPIO_Driver_SetPin(NOKIA_5110_DRIVER_LCD_PORT,NOKIA_5110_DRIVER_LCD_RST_PIN);*/
}

void NOKIA_5110_Driver_On(){}
void NOKIA_5110_Driver_Off(){}
/*
 * Set contrast
 * SetXYcoordinates
 * */
