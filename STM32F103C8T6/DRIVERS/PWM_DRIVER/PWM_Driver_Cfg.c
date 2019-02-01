/*
 * PWM_Driver_Cfg.c
 *
 *  Created on: Dec 25, 2018
 *      Author: zsole
 */

#include "PWM_Driver_Cfg.h"

PWM_Driver_Setup_Type PWM_CONF_SETUP[PWM_DRIVER_INSTANCE_NUM]=
{
	{
		TIM2,
		PWM_Driver_Channel_2,
		PWM_DRIVER_PWM_MODE_1,
		OK,
		PWM_DRIVER_ACTIVE_HIGH,
		OK
	}
};

PWM_Driver_Setup_Type* PWM_SETUP = PWM_CONF_SETUP;
