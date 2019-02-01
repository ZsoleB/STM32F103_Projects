/*
 * WWDT_Driver.h
 *
 *  Created on: Aug 27, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_WDG_DRIVER_WWDT_DRIVER_H_
#define DRIVERS_WDG_DRIVER_WWDT_DRIVER_H_

#include <NVIC_DRIVER/NVIC_Driver.h>
#include "stm32f10x.h"
#include "StdTypes.h"

#define WWDT_DRIVER_ACTIVATION 									(0x01<<0x07)
#define WWDT_DRIVER_PRESCALER_TIME_BASE_DIV1 					(0x00<<0x07)
#define WWDT_DRIVER_PRESCALER_TIME_BASE_DIV2 					(0x01<<0x07)
#define WWDT_DRIVER_PRESCALER_TIME_BASE_DIV4 					(0x02<<0x07)
#define WWDT_DRIVER_PRESCALER_TIME_BASE_DIV8 					(0x03<<0x07)
#define WWDT_DRIVER_COUNTER_MAX_VALUE 							0x3F
#define WWDT_DRIVER_COUNTER_MIN_VALUE 							0x21
#define WWDT_DRIVER_T6_BIT_SET 									(0x01<<0x06)
#define WWDT_DRIVER_T6_BIT_CLEAR 								(~(0x01<<0x06))
#define WWDT_DRIVER_INTERRUPT_ENABLE 							(0x01<<0x09)

void WWDT_Driver_Init();
void WWDT_Driver_Refresh_WWDT_Counter();
void WWDT_Driver_Set_Interrupt();
void WWDT_Driver_Clear_Interrupt_Flag();

#endif /* DRIVERS_WDG_DRIVER_WWDT_DRIVER_H_ */
