/*
 * TCNT_Driver_Cfg.c
 *
 *  Created on: Dec 24, 2018
 *      Author: zsole
 */

#include "TCNT_Driver_Cfg.h"

TCNT_Driver_Setup_Type TCNT_CONF_SETUP[TCNT_DRIVER_INSTANCE_NUM]=
{
	{
		TIM4,
		TCNT_DRIVER_UP_COUNTER,
		0x00,
		MAX16
	}
};

TCNT_Driver_Setup_Type* TCNT_SETUP = TCNT_CONF_SETUP;

#if(TCNT_DRIVER_INTERRUPT_ENABLE == OK)

void TCNT_Setup_Callbacks()
{
	TCNT_Driver_Interrupt_Callbacks[TCNT_DRIVER_TIM2_CALLBACK] = TCNT_Driver_Callback_Function;
}


void TCNT_Driver_Callback_Function()
{
	static uint8 status = 0x00;

	if(status == 0x00)
	{
		GPIOC->BSRR |= (1<<0x0D);
	}
	else
	{
		GPIOC->BSRR |= ((1<<0x0D)<<16);
	}
	status = !status;
}

#endif
