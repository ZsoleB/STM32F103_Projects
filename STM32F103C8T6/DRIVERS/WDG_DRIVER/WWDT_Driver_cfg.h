/*
 * WWDT_Driver_cfg.h
 *
 *  Created on: Aug 27, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_WDG_DRIVER_WWDT_DRIVER_CFG_H_
#define DRIVERS_WDG_DRIVER_WWDT_DRIVER_CFG_H_

#include "WWDT_Driver.h"

#define WWDT_DRIVER_INTERRUPT_ENABLED 						OK
#define WWDT_DRIVER_PRESCALER_TIME_BASE 					WWDT_DRIVER_PRESCALER_TIME_BASE_DIV8
#define WWDT_DRIVER_WINDOW_VALUE 							0x7F
#define WWDT_DRIVER_COUNTER_VALUE 							0x3F

#if((WWDT_DRIVER_COUNTER_VALUE > WWDT_DRIVER_COUNTER_MAX_VALUE) || (WWDT_DRIVER_COUNTER_VALUE< WWDT_DRIVER_COUNTER_MIN_VALUE))
	#error "The WWDT_DRIVER_COUNTER_VALUE is out of range"
#endif

#endif /* DRIVERS_WDG_DRIVER_WWDT_DRIVER_CFG_H_ */
