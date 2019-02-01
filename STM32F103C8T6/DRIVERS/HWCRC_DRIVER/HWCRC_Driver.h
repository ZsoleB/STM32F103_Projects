/*
 * HWCRC_Driver.h
 *
 *  Created on: May 7, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_HWCRC_DRIVER_HWCRC_DRIVER_H_
#define DRIVERS_HWCRC_DRIVER_HWCRC_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"

uint32 HWCRC_Driver_Calculate_CRC(uint32 data);
void HWCRC_Driver_Init();
void HWCRC_Driver_Reset();

#endif /* DRIVERS_HWCRC_DRIVER_HWCRC_DRIVER_H_ */
