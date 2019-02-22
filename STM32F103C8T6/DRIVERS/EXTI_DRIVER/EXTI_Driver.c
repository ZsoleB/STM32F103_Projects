/*
 * EXTI_Driver.c
 *
 *  Created on: Feb 6, 2018
 *      Author: zsolt.balo
 */

#include "EXTI_Driver_Cfg.h"

void EXTI_Driver_Init(uint8 InterruptPinNumber, uint8 InterruptPortNumber, uint8 Action_Section)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

	if (InterruptPinNumber < 0x04)
	{
		AFIO->EXTICR[0] |= (InterruptPortNumber << (4 * InterruptPinNumber));
		if (Action_Section == EXTI_DRIVER_INTERRUPT_ACTION)
		{
			EXTI->IMR |= ((0x01) << InterruptPinNumber);
		}

		else if (Action_Section == EXTI_DRIVER_EVENT_ACTION)
		{
			EXTI->EMR |= ((0x01) << InterruptPinNumber);
		}
		else
		{
			/*Nothing to do*/
		}
	}

	else if ((InterruptPinNumber < 0x08) && (InterruptPinNumber >= 0x04))
	{
		AFIO->EXTICR[1] |= (InterruptPortNumber << (4 * (InterruptPinNumber - 0x04)));
		if (Action_Section == EXTI_DRIVER_INTERRUPT_ACTION)
		{
			EXTI->IMR |= ((0x01) << InterruptPinNumber);
		}

		else if (Action_Section == EXTI_DRIVER_EVENT_ACTION)
		{
			EXTI->EMR |= ((0x01) << InterruptPinNumber);
		}
		else
		{
			/*Nothing to do*/
		}
	}

	if ((InterruptPinNumber < 0x0C) && (InterruptPinNumber >= 0x08))
	{
		AFIO->EXTICR[2] |= (InterruptPortNumber << (4 * (InterruptPinNumber - 0x08)));
		if (Action_Section == EXTI_DRIVER_INTERRUPT_ACTION)
		{
			EXTI->IMR |= ((0x01) << InterruptPinNumber);
		}

		else if (Action_Section == EXTI_DRIVER_EVENT_ACTION)
		{
			EXTI->EMR |= ((0x01) << InterruptPinNumber);
		}
		else
		{
			/*Nothing to do*/
		}
	}

	if (InterruptPinNumber >= 0x0C)
	{
		AFIO->EXTICR[3] |= (InterruptPortNumber << (4 * (InterruptPinNumber - 0x0C)));
		if (Action_Section == EXTI_DRIVER_INTERRUPT_ACTION)
		{
			EXTI->IMR |= ((0x01) << InterruptPinNumber);
		}

		else if (Action_Section == EXTI_DRIVER_EVENT_ACTION)
		{
			EXTI->EMR |= ((0x01) << InterruptPinNumber);
		}
		else
		{
			/*Nothing to do*/
		}
	}

#if(EXTI_DRIVER_INTERRUPT_MODE == OK)
	NVIC_Driver_PriorityGroupConfig(NVIC_DRIVER_PRIORITY_GRUP_3);
	NVIC_Driver_Set_EXTI_Interrupt(((uint8) 0x01), ((uint8) 0x01));
#elif(EXTI_DRIVER_EVENT_MODE == OK)
	/*Nothing to do*/
#else
	"The selected EXTI_DRIVER_MODE is not correct, choose one from the available ones !"
#endif
}

void EXTI_Driver_Rising_Trigger_Select(uint8 InterruptNumber)
{
	EXTI->RTSR |= ((0x01) << InterruptNumber);
}

void EXTI_Driver_Rising_Trigger_Clear(uint8 InterruptNumber)
{
	EXTI->RTSR &= ~(((0x01) << InterruptNumber));
}

void EXTI_Driver_Falling_Trigger_Select(uint8 InterruptNumber)
{
	EXTI->FTSR |= ((0x01) << InterruptNumber);
}

void EXTI_Driver_Falling_Trigger_Clear(uint8 InterruptNumber)
{
	EXTI->FTSR &= ~(((0x01) << InterruptNumber));
}
void EXTI_Driver_Generate_SWInterrupt(uint8 InterruptNumber)
{
	/*If the interrupt is enabled on this line in the EXTI_IMR, writing a '1' to this bit when it is set to
	 '0' sets the corresponding pending bit in EXTI_PR resulting in an interrupt request
	 generation.*/
	if ((EXTI->IMR & (0x01 << InterruptNumber)) != 0x00)
	{
		EXTI->SWIER |= ((0x01) << InterruptNumber);
	}
}

void EXTI_Driver_Clear_PendingInterrupt(uint8 InterruptNumber)
{
	EXTI->PR |= ((0x01) << InterruptNumber);
}
