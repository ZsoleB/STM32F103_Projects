/*
 * FLASH_Driver.c
 *
 *  Created on: Jan 21, 2019
 *      Author: zsolt.balo
 */

#include "FLASH_Driver_Cfg.h"

/*Lock the Flash memory, to protect it from unwanted modifications*/
void FLASH_Driver_Lock()
{
	/*Write 1 to the Lock bit to block the access to the flash memory*/
	FLASH->CR|=FLASH_DRIVER_LOCK;
}

/*Unlock the flash memory in order to perform operations on it */
void FLASH_Driver_UnLock()
{
	/*Write the first key to the key register*/
	FLASH->KEYR = FLASH_DRIVER_KEY1;
	/*Write the second key to the key register*/
	FLASH->KEYR = FLASH_DRIVER_KEY2;
}

/*Program a byte length payload to the given address, in the selected sector  */
void FLASH_Driver_Program(uint32 Address,uint16 Payload)
{
	/*Erase the page before writing*/
	FLASH_Driver_Erease_Page(Address);

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Set the program operation*/
	FLASH->CR |= FLASH_DRIVER_PROGRAM_OP;

	/*Perform program operation to the desired address*/
	*(volatile uint16*)Address = Payload;

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Clear the program operation*/
	FLASH->CR &= (~FLASH_DRIVER_PROGRAM_OP);
}

/*Erase the selected sector */
void FLASH_Driver_Erease_Page(uint32 PageNumber)
{
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Set the sector erase operation*/
	FLASH->CR |= FLASH_DRIVER_PAGE_ERASE_OP;
	/*Set new page*/
	FLASH->AR = PageNumber;
	/*Start the sector erase operation*/
	FLASH->CR |= FLASH_DRIVER_START_OP;

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/* If the erase operation is completed, disable the SER Bit */
	FLASH->CR &= (~FLASH_DRIVER_PAGE_ERASE_OP);
	/*Clear the address selection*/
	FLASH->AR = 0x00;
}

/*Erase all the Flash memory */
void FLASH_Driver_Mass_Erease()
{
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Set the mass erase operation*/
	FLASH->CR |= FLASH_DRIVER_MASS_ERASE_OP;

	/*Start the mass erase operation*/
	FLASH->CR |= FLASH_DRIVER_START_OP;

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/* If the erase operation is completed, disable the MER Bit */
	FLASH->CR &= (~FLASH_DRIVER_MASS_ERASE_OP);
}

/*Read from the flash driver, using the given address */
uint64 FLASH_Driver_Read(uint32 Address)
{
	uint64 Result = 0x00;

	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	Result = (*(volatile uint64*)Address);

	return Result;
}
