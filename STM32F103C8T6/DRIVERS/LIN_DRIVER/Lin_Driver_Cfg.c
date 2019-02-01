/*
 * Lin_Drive_Cfg.c
 *
 *  Created on: Oct 23, 2018
 *      Author: zsolt.balo
 */

#include "Lin_Driver_Cfg.h"

static LIN_Driver_Setup_Type LIN_CONF_SETUP[LIN_DRIVER_INSTANCE_NUM];
LIN_Driver_Setup_Type* LIN_SETUP = LIN_CONF_SETUP;

void LIN_Driver_Init_Cfg()
{
	LIN_CONF_SETUP[LIN_DRIVER_1].USART_Setup_Instance = USART_SETUP;
	LIN_CONF_SETUP[LIN_DRIVER_1].USART_Instance_number = USART_DRIVER_1;
}
