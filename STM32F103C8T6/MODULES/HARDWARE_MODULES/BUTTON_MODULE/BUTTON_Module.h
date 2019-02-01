/*
 * BUTTON_Module.h
 *
 *  Created on: Sep 11, 2018
 *      Author: zsolt.balo
 */

#ifndef MODULES_HARDWARE_MODULES_BUTTON_MODULE_BUTTON_MODULE_H_
#define MODULES_HARDWARE_MODULES_BUTTON_MODULE_BUTTON_MODULE_H_

#include "GPIO_Driver_Cfg.h"
#include "ADC_Driver_Cfg.h"

typedef struct
{
	uint16 GPIO_Instance_nr;
	uint16 GPIO_Pin_Nr;
}BUTTON_Module_Setup_Type;

extern BUTTON_Module_Setup_Type* BUTTON_SETUP;

void BUTTON_Module_Init_Cfg();
uint8 BUTTON_Module_Read_Value(uint8 Button_Setup_nr);

#endif /* MODULES_HARDWARE_MODULES_BUTTON_MODULE_BUTTON_MODULE_H_ */
