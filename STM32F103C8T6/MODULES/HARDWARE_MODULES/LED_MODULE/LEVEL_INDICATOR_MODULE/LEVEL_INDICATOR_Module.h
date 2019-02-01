/*
 * LEVEL_INDICATOR_Module.h
 *
 *  Created on: Sep 10, 2018
 *      Author: zsolt.balo
 */

#ifndef MODULES_HARDWARE_MODULES_LED_MODULE_LEVEL_INDICATOR_MODULE_LEVEL_INDICATOR_MODULE_H_
#define MODULES_HARDWARE_MODULES_LED_MODULE_LEVEL_INDICATOR_MODULE_LEVEL_INDICATOR_MODULE_H_

#include "LED_Module_Cfg.h"

#define LEVEL_INDICATOR_MODULE_GPIO_INTERFACE 								0x00
#define LEVEL_INDICATOR_MODULE_PORT_EXPANDER_INTERFACE 						0x01

typedef struct
{
	uint8 LEVEL_0_Indicator;
	uint8 LEVEL_1_Indicator;
	uint8 LEVEL_2_Indicator;
	uint8 LEVEL_3_Indicator;
	uint8 LEVEL_4_Indicator;
	uint8 LEVEL_5_Indicator;
	uint8 LEVEL_6_Indicator;
	uint8 LEVEL_7_Indicator;
	uint8 LEVEL_8_Indicator;
	uint8 LEVEL_9_Indicator;
}LEVEL_INDICATOR_Module_Setup_Type;

extern LEVEL_INDICATOR_Module_Setup_Type* LEVEL_INDICATOR_SETUP;

void LEVEL_INDICATOR_Module_Init_Cfg();
void LEVEL_INDICATOR_Module_Update_Display(uint8 Level_Indicator_Number,uint8 Level_value);
void LEVEL_INDICATOR_Module_Clear(uint8 Level_Indicator_Number);
void LEVEL_INDICATOR_Module_Set_Dimming(uint8 Level_Indicator_Number,uint8 DutyCycle);

#endif /* MODULES_HARDWARE_MODULES_LED_MODULE_LEVEL_INDICATOR_MODULE_LEVEL_INDICATOR_MODULE_H_ */
