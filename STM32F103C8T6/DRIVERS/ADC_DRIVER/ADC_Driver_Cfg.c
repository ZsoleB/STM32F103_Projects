/*
 * ADC_Driver_Cfg.c
 *
 *  Created on: Sep 12, 2018
 *      Author: zsolt.balo
 */

#include "ADC_Driver_Cfg.h"

ADC_Driver_Setup_Type ADC_CONF_SETUP[ADC_DRIVER_INSTANCE_NUM]=
{
	{
		ADC1,
		OK,
		NOK,
		OK,
		ADC_ALIGNMENT_RIGHT,
		ADC_DRIVER_SEQUENCE_1_CONVERSION,
		0x01,
		{ADC_DRIVER_CHANNEL_1},
		{ADC_DRIVER_CHANNEL_SAMPLING_TIME_55_5_CYCLES},
		{ADC_DRIVER_SEQUENCE_POSITION_1}
	}
};

ADC_Driver_Setup_Type* ADC_SETUP = ADC_CONF_SETUP;
