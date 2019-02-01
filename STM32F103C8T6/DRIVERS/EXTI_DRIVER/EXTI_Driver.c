/*
 * EXTI_Driver.c
 *
 *  Created on: Feb 6, 2018
 *      Author: zsolt.balo
 */

#include "EXTI_Driver_Cfg.h"


void EXTI_Driver_Init(uint8 InterruptPinNumber,uint8 InterruptPortNumber)
{

	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

	if (InterruptPinNumber < 0x04)
	{
		AFIO->EXTICR[0] |=(InterruptPortNumber<<(4*InterruptPinNumber));
		EXTI->IMR |= ((0x01)<<InterruptPinNumber);
	}

	else if ((InterruptPinNumber < 0x08)&&(InterruptPinNumber >= 0x04))
	{
		AFIO->EXTICR[1] |= (InterruptPortNumber<<(4*(InterruptPinNumber-0x04)));
		EXTI->IMR |= ((0x01)<<InterruptPinNumber);
	}

	if ((InterruptPinNumber < 0x0C) && (InterruptPinNumber >= 0x08))
	{
		AFIO->EXTICR[2] |= (InterruptPortNumber<<(4*(InterruptPinNumber-0x08)));
		EXTI->IMR |= ((0x01)<<InterruptPinNumber);
	}

	if (InterruptPinNumber >= 0x0C)
	{
		AFIO->EXTICR[3] |= (InterruptPortNumber<<(4*(InterruptPinNumber-0x0C)));
		EXTI->IMR |= ((0x01)<<InterruptPinNumber);
	}
}

void EXTI_Driver_Rising_Trigger_Select(uint8 InterruptNumber)
{
	EXTI->RTSR|=((0x01)<<InterruptNumber);
}

void EXTI_Driver_Rising_Trigger_Clear(uint8 InterruptNumber)
{
	EXTI->RTSR &=~(((0x01)<<InterruptNumber));
}

void EXTI_Driver_Falling_Trigger_Select(uint8 InterruptNumber)
{
	EXTI->FTSR|=((0x01)<<InterruptNumber);
}

void EXTI_Driver_Falling_Trigger_Clear(uint8 InterruptNumber)
{
	EXTI->FTSR &= ~(((0x01)<<InterruptNumber));
}
void EXTI_Driver_Generate_SWInterrupt(uint8 InterruptNumber)
{
	/*This bit is cleared by clearing the corresponding bit of EXTI_PR (by writing a 1 into the bit).*/
	if((EXTI->EMR & (0x01<<InterruptNumber))!=0x00)
	{
		EXTI->SWIER|=((0x01)<<InterruptNumber);
	}
}

void EXTI_Driver_Clear_PendingInterrupt(uint8 InterruptNumber)
{
	EXTI->PR|=((0x01)<<InterruptNumber);
}
