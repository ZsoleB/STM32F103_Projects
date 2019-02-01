/*
 * SYSTICK_Driver.h
 *
 *  Created on: May 3, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_SYSTICK_DRIVER_SYSTICK_DRIVER_H_
#define DRIVERS_SYSTICK_DRIVER_SYSTICK_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"

void SYSTICK_Driver_Init();
void SYSTICK_Driver_Start();
void SYSTICK_Driver_Stop();
uint32 SYSTICK_Driver_GetClockValue();
uint8 SYSTICK_Driver_GetCountFlag();
void SYSTICK_Driver_Delay_us(uint32 DelayInterval);
void SYSTICK_Driver_Delay_ms(uint32 DelayInterval);
void SYSTICK_Driver_Delay(uint32 DelayInterval);

#endif /* DRIVERS_SYSTICK_DRIVER_SYSTICK_DRIVER_H_ */
