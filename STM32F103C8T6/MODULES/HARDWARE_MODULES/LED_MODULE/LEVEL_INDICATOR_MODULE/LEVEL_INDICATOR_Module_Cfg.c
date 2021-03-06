/*
 * LEVEL_INDICATOR_Module_Cfg.c
 *
 *  Created on: Sep 10, 2018
 *      Author: zsolt.balo
 */

#include "LEVEL_INDICATOR_Module_Cfg.h"

static LEVEL_INDICATOR_Module_Setup_Type LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_INSTANCE_NUM];

LEVEL_INDICATOR_Module_Setup_Type* LEVEL_INDICATOR_SETUP = LEVEL_INDICATOR_CONF_SETUP;

void LEVEL_INDICATOR_Module_Init_Cfg()
{
	#if(LEVEL_INDICATOR_MODULE_INTERFACE == LEVEL_INDICATOR_MODULE_GPIO_INTERFACE)

		LED_Module_Init_Cfg();

		LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_0].LEVEL_0_Indicator = LED_MODULE_0;
		LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_0].LEVEL_1_Indicator = LED_MODULE_1;
		LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_0].LEVEL_2_Indicator = LED_MODULE_2;
		LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_0].LEVEL_3_Indicator = LED_MODULE_3;
		LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_0].LEVEL_4_Indicator = LED_MODULE_4;
		LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_0].LEVEL_5_Indicator = LED_MODULE_5;
		LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_0].LEVEL_6_Indicator = LED_MODULE_6;
		LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_0].LEVEL_7_Indicator = LED_MODULE_7;
		LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_0].LEVEL_8_Indicator = LED_MODULE_8;
		LEVEL_INDICATOR_CONF_SETUP[LEVEL_INDICATOR_MODULE_0].LEVEL_9_Indicator = LED_MODULE_9;

	#endif
}
