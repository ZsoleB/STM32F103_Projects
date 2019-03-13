/*
 * RTC_Driver_Cfg.c
 *
 *  Created on: Nov 7, 2018
 *      Author: zsolt.balo
 */

#include "RTC_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"

volatile static uint8 counter = 0x00;

void RTC_Driver_Callback_Function()
{
	static uint8 state = 0x00;

	if ((state % 2) == 0x00)
	{
		GPIO_Driver_SetPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN1);
	}
	else
	{
		GPIO_Driver_ClearPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN1);
	}
	state++;
}


