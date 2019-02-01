/*
 * BUTTON_Module_Cfg.c
 *
 *  Created on: Sep 11, 2018
 *      Author: zsolt.balo
 */

#include "BUTTON_Module_Cfg.h"

static BUTTON_Module_Setup_Type BUTTON_CONF_SETUP[BUTTON_MODULE_INSTANCE_NUM];

BUTTON_Module_Setup_Type* BUTTON_SETUP = BUTTON_CONF_SETUP;

void BUTTON_Module_Init_Cfg()
{
/*
	BUTTON_CONF_SETUP[BUTTON_MODULE_0].GPIO_Instance_nr = GPIO_DRIVER_PORTA;
	BUTTON_CONF_SETUP[BUTTON_MODULE_0].GPIO_Pin_Nr = GPIO_SETUP[GPIO_DRIVER_PORTA].GPIO_Pins[GPIO_DRIVER_PORTA_PIN3];
*/
}
