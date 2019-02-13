/*
 * ADC_Driver_Cfg.h
 *
 *  Created on: Jan 23, 2018
 *      Author: zsolt.balo
 */

#ifndef ADC_DRIVER_CFG_H_
#define ADC_DRIVER_CFG_H_

#include "ADC_Driver.h"
#include "StdTypes.h"

#define ADC_DRIVER_ADC1 					OK
#define ADC_DRIVER_ADC2 					NOK
#define ADC_DRIVER_ANALOG_WATCHDOG 			NOK
#define ADC_DRIVER_PRESCALE 				ADC_DRIVER_PRESCALE_BY_2
#define ADC_DRIVER_INSTANCE_NUM 			((uint32)0x01)

typedef enum
{
	ADC_DRIVER_1
}ADC_Driver_Instances;

typedef enum
{
	ADC_DRIVER_1_CHANNEL_1,
	ADC_DRIVER_1_CHANNEL_2,
}ADC_Driver_Channel_Instances;

#endif /* ADC_DRIVER_CFG_H_ */
