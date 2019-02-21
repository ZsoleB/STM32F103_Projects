/*
 * GPIO_Driver_Cfg.c
 *
 *  Created on: Aug 21, 2018
 *      Author: zsolt.balo
 */

#include "GPIO_Driver_Cfg.h"

GPIO_Driver_Setup_Type GPIO_CONF_SETUP[GPIO_DRIVER_INSTANCE_NUM] =
{
	{
		GPIOA,
		0x03,
		{0x01,0x03,0x07},
		{GPIO_DRIVER_INPUT_MODE,GPIO_DRIVER_OUTPUT_MODE_50MHZ,GPIO_DRIVER_INPUT_MODE},
		{GPIO_DRIVER_FLOATING_INPUT,GPIO_DRIVER_GP_OUTPUT_PP,GPIO_DRIVER_FLOATING_INPUT}
	},
};

GPIO_Driver_Setup_Type* GPIO_SETUP = GPIO_CONF_SETUP;

void GPIO_Driver_Lambda_function()
{

}
