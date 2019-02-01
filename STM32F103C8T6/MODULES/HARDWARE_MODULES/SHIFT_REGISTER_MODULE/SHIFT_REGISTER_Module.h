/*
 * SHIFT_REGISTER_Module.h
 *
 *  Created on: Sep 18, 2018
 *      Author: zsolt.balo
 */

#ifndef MODULES_HARDWARE_MODULES_SHIFT_REGISTER_MODULE_SHIFT_REGISTER_MODULE_H_
#define MODULES_HARDWARE_MODULES_SHIFT_REGISTER_MODULE_SHIFT_REGISTER_MODULE_H_

#include "SPI_Driver_Cfg.h"

typedef struct
{
	uint8 SPI_Instance;
}SHIFT_REGISTER_Module_Setup_Type;

extern SHIFT_REGISTER_Module_Setup_Type* SHIFT_REGISTER_SETUP;

void SHIFT_REGISTER_Module_Init_Cfg();
void SHIFT_REGISTER_Module_Update(uint8 shift_register_nr,uint16 payload);
void SHIFT_REGISTER_Module_Clear(uint8 shift_register_nr);

#endif /* MODULES_HARDWARE_MODULES_SHIFT_REGISTER_MODULE_SHIFT_REGISTER_MODULE_H_ */
