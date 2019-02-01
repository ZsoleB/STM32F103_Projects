/*
 * TWI_Driver_Cfg.c
 *
 *  Created on: Jan 17, 2019
 *      Author: zsolt.balo
 */

#include "TWI_Driver_Cfg.h"

TWI_Driver_Setup_Type TWI_CONF_SETUP[TWI_DRIVER_INSTANCE_NUM]=
{
	{
			I2C1,
			NOK,
			NOK,
			0x0F,
			0x00,
			OK,
			NOK,
			NOK,
			TWI_DRIVER_STANDARD_SPEED_100KHz,
			TWI_DRIVER_FAST_SPEED_DUTY_CYCLE_2,
			100000,
			NOK
	}
};

TWI_Driver_Setup_Type* TWI_SETUP = TWI_CONF_SETUP;
