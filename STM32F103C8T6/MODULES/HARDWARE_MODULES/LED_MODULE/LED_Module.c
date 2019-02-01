/*
 * LED_Module.c
 *
 *  Created on: Sep 5, 2018
 *      Author: zsolt.balo
 */

#include "LED_Module_Cfg.h"

void LED_Module_Set_On(uint8 Led_Setup_nr)
{
	GPIO_Driver_SetPin(LED_SETUP[Led_Setup_nr].GPIO_Instance_Nr,LED_SETUP[Led_Setup_nr].GPIO_Pin_Nr);
}

void LED_Module_Set_Off(uint8 Led_Setup_nr)
{
	GPIO_Driver_ClearPin(LED_SETUP[Led_Setup_nr].GPIO_Instance_Nr,LED_SETUP[Led_Setup_nr].GPIO_Pin_Nr);
}

void LED_Module_Set_Dimming(uint8 Led_Setup_nr, uint8 DutyCycle)
{
	/*PWM_Driver_SetDutyCylce(TIM4,DutyCycle);*/
}
