/*
 * LED_Module.h
 *
 *  Created on: Sep 5, 2018
 *      Author: zsolt.balo
 */

#ifndef MODULES_HARDWARE_MODULES_LED_MODULE_LED_MODULE_H_
#define MODULES_HARDWARE_MODULES_LED_MODULE_LED_MODULE_H_

#include "GPIO_Driver_Cfg.h"
#include "PWM_Driver_Cfg.h"

typedef struct
{
	uint8  GPIO_Instance_Nr;
	uint8 GPIO_Pin_Nr;
}LED_Module_Setup_Type;

extern LED_Module_Setup_Type* LED_SETUP;

void LED_Module_Init_Cfg();
void LED_Module_Set_On(uint8 Led_Setup_nr);
void LED_Module_Set_Off(uint8 Led_Setup_nr);
void LED_Module_Set_Dimming(uint8 Led_Setup_nr, uint8 DutyCycle);


#endif /* MODULES_HARDWARE_MODULES_LED_MODULE_LED_MODULE_H_ */
