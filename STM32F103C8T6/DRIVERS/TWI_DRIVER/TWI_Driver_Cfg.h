/*
 * TWI_Driver_Cfg.h
 *
 *  Created on: Jul 17, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_TWI_DRIVER_TWI_DRIVER_CFG_H_
#define DRIVERS_TWI_DRIVER_TWI_DRIVER_CFG_H_

#include "TWI_Driver.h"

#define TWI_DRIVER_TWI1								OK
#define TWI_DRIVER_TWI2								NOK
#define TWI_DRIVER_FUNCTIONALITY 					TWI_DRIVER_POLLING_FUNCTIONALITY
#define TWI_DRIVER_INSTANCE_NUM						(0x01)

typedef enum
{
	TWI_DRIVER_1,
}USART_Driver_Instances;

#endif /* DRIVERS_TWI_DRIVER_TWI_DRIVER_CFG_H_ */
