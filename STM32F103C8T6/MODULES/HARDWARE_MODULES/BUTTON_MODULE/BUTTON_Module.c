/*
 * BUTTON_Module.c
 *
 *  Created on: Sep 11, 2018
 *      Author: zsolt.balo
 */
#include "BUTTON_Module_Cfg.h"

uint8 BUTTON_Module_Read_Value(uint8 Button_Setup_nr)
{
	uint8 Input_value = 0x00;
	static uint16 Counter = 0x00;

	Input_value = GPIO_Driver_ReadInputDataBit(BUTTON_SETUP[Button_Setup_nr].GPIO_Instance_nr,BUTTON_SETUP[Button_Setup_nr].GPIO_Pin_Nr);
	if(Input_value == 0x00)
	{
		do{
			Counter++;
		}while(Counter<300);

		Input_value = GPIO_Driver_ReadInputDataBit(BUTTON_SETUP[Button_Setup_nr].GPIO_Instance_nr,BUTTON_SETUP[Button_Setup_nr].GPIO_Pin_Nr);

		if(Input_value == 0x00)
		{
			Counter = 0x00;
			return 0x00;
		}
	}
	return 0x01;
}
