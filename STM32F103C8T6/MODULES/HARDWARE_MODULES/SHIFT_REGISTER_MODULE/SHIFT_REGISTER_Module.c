/*
 * SHIFT_REGISTER_Module.c
 *
 *  Created on: Sep 18, 2018
 *      Author: zsolt.balo
 */

#include "SHIFT_REGISTER_Module_Cfg.h"

void SHIFT_REGISTER_Module_Update(uint8 shift_register_nr,uint16 payload)
{
	SPI_Driver_Transcieve_Data(SHIFT_REGISTER_SETUP[shift_register_nr].SPI_Instance,payload);
}

void SHIFT_REGISTER_Module_Clear(uint8 shift_register_nr)
{
	SPI_Driver_Transcieve_Data(SHIFT_REGISTER_SETUP[shift_register_nr].SPI_Instance,0x00);
}
