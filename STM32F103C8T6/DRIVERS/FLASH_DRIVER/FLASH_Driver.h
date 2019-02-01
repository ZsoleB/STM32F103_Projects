/*
 * FLASH_Driver.h
 *
 *  Created on: Jan 21, 2019
 *      Author: zsolt.balo
 */

#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"

#define FLASH_DRIVER_KEY1					 				((uint32)0x45670123)
#define FLASH_DRIVER_KEY2					 				((uint32)0xCDEF89AB)
#define FLASH_DRIVER_LOCK					 				((uint32)(0x01<<0x07))
#define FLASH_DRIVER_START_OP					 			((uint32)(0x01<<0x06))
#define FLASH_DRIVER_PAGE_ERASE_OP					 		((uint32)(0x01<<0x01))
#define FLASH_DRIVER_MASS_ERASE_OP					 		((uint32)(0x01<<0x02))
#define FLASH_DRIVER_PROGRAM_OP					 			((uint32)(0x01<<0x00))
#define FLASH_DRIVER_BUSY_FLAG					 			((uint32)(0x01<<0x00))
#define FLASH_DRIVER_END_OF_OPERATION_FLAG					((uint32)(0x01<<0x05))

void FLASH_Driver_Lock();
void FLASH_Driver_UnLock();
void FLASH_Driver_Program(uint32 Address,uint16 Payload);
void FLASH_Driver_Erease_Page(uint32 PageNumber);
void FLASH_Driver_Mass_Erease();
uint64 FLASH_Driver_Read(uint32 Address);

#endif /* FLASH_DRIVER_H_ */
