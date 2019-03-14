/*
 * RTC_Driver.c
 *
 *  Created on: Oct 26, 2018
 *      Author: zsolt.balo
 */

#include "RTC_Driver_Cfg.h"

void RTC_Driver_Init()
{
	/*Set the clock for PWR*/
	RCC->APB1ENR|= RCC_APB1ENR_PWREN;

	RCC->APB1ENR|= RCC_APB1ENR_BKPEN;

	/*Enable access to backup domain registers*/
	PWR->CR |= RTC_DRIVER_DISABLE_BACKUP_WRITE_PROTECTION;

	/*RTC interrupt setup*/
	#if(RTC_DRIVER_INTERRUPT_ENABLE == OK)
		RTC_Driver_Interrupt_Callback = RTC_Driver_Callback_Function;
		NVIC_Driver_PriorityGroupConfig(RTC_DRIVER_SELECTED_PRIORITY_GRUP);
		NVIC_Driver_Set_RTC_Interrupt(RTC_DRIVER_SELECTED_PREEMPTION_PRIORITY,RTC_DRIVER_SELECTED_SUB_PRIORITY);
	#endif

	/*Reset Backup domain register*/
	RCC->BDCR |= RTC_DRIVER_RESET_BAKUP_DOMAIN;
	RCC->BDCR &= ~(RTC_DRIVER_RESET_BAKUP_DOMAIN);

#if((RTC_DRIVER_USE_LSE == OK)&&(RTC_DRIVER_USE_HSE == NOK))

	/*Enable the LSE clock*/
	RCC->BDCR |= RTC_DRIVER_LSE_CLK_ON;

	/*Wait until the LSE clock is ready*/
	while ((RCC->BDCR & (uint32_t)RTC_DRIVER_LSE_CLOCK_READY) != 0x02)
	{}

#elif((RTC_DRIVER_USE_LSE == NOK)&&(RTC_DRIVER_USE_HSE == OK))
	/*Nothing to do*/
#else

#error "Please choose, one time source for RTC !"
#endif

	/*Enable the RTC*/
	RCC->BDCR |= RTC_DRIVER_ENABLE;

	/*Select the RTC clock source*/
	RCC->BDCR |= RTC_DRIVER_CLK_SOURCE;

	/*	Configuration procedure:*/

	/*1. Poll RTCOFF, wait until its value goes to ‘1’*/
	while((RTC->CRL & 0x20) == NOK){}

	/*2. Set the CNF bit to enter configuration mode*/
	RTC->CRL |= (0x01<<0x04);
	while((RTC->CRL & 0x20) == NOK){}

	/*Clear registers Synchronized Flag*/
    RTC->CRL &= ~RTC_DRIVER_REGISTERS_SYNCHRONIZED_FLAG;

    /*Wait for the RSF bit in RTC_CRL to be set by hardware*/
    while((RTC->CRL & RTC_DRIVER_REGISTERS_SYNCHRONIZED_FLAG) == NOK){}

	/*3. Write to one or more RTC registers*/
#if(RTC_DRIVER_CLK_SOURCE == RTC_DRIVER_HSE_CLK)
	RTC->PRLL |= (0xF423);
	while((RTC->CRL & 0x20) == NOK){}
#elif(RTC_DRIVER_CLK_SOURCE == RTC_DRIVER_LSE_CLK)
	RTC->PRLL |= (0x7FFF);
	while((RTC->CRL & 0x20) == NOK){}
#else
#warning "LSI is not implemented"
#error "Please choose a corect RTC_DRIVER_CLK_SOURCE value !"
#endif

	/*4. Clear the CNF bit to exit configuration mode*/
	RTC->CRL &= (~(0x01<<0x04));

	/*5. Poll RTCOFF, wait until its value goes to ‘1’ to check the end of the write operation.*/
	while((RTC->CRL & 0x20) == NOK){}

#if(RTC_DRIVER_CLK_SOURCE != RTC_DRIVER_HSE_CLK)
	/*Disable access to backup domain registers*/
	PWR->CR &= RTC_DRIVER_ENABLE_BACKUP_WRITE_PROTECTION;
#endif

}

uint8 RTC_Driver_Read_SecondStatus()
{
	/*RTC_Driver_Synchronize();*/
	if((RTC->CRL & 0x01)==0x01)
	{
		RTC->CRL &= (~(0x01));
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}


void RTC_Driver_Synchronize()
{
	while((RTC->CRL & RTC_DRIVER_SYNCHRONIZED)!=0x08){}
}

#if(RTC_DRIVER_INTERRUPT_ENABLE == OK)
	void RTC_IRQHandler()
	{
		RTC->CRL &= (~(0x01));
		RTC_Driver_Interrupt_Callback();
	}
#endif
