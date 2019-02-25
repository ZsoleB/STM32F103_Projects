/*
 * SYSTEM_Driver.c
 *
 *  Created on: Oct 1, 2018
 *      Author: zsolt.balo
 */

#include "SYSTEM_Driver_Cfg.h"

void SYSTEM_Driver_Software_Reset()
{
	uint32 Old_register_value = 0x00;
	uint32 New_register_value = 0x00;

	Old_register_value = SCB->AIRCR;
	Old_register_value &= ~(SYSTEM_DRIVER_AIRCR_VECTORKEY_CLEAR_MASK);

	New_register_value = (Old_register_value) | (SYSTEM_DRIVER_AIRCR_VECTORKEY_MASK) | (0x01 << 0x02);

	/* Ensure completion of memory access, with Data Synchronization Barrier asm instruction */
	__DSB();

	/* Request the software reset*/
	SCB->AIRCR = New_register_value;

	/* Ensure completion of memory access*/
	__DSB();
}

void SYSTEM_Driver_Set_System_Clock()
{
	volatile uint32 StartUpCounter = 0, HSEStatus = 0;

	/* Enable HSE */
	RCC->CR |= SYSTEM_DRIVER_HSE_ON;

	do
	{
		HSEStatus = RCC->CR & SYSTEM_DRIVER_HSE_CLOCK_READY;
		StartUpCounter++;
	} while ((HSEStatus == 0) && (StartUpCounter != 0x500));

	if ((RCC->CR & SYSTEM_DRIVER_HSE_CLOCK_READY) != NOK)
	{
		HSEStatus = (uint32) 0x01;
	}
	else
	{
		HSEStatus = (uint32) 0x00;
	}

	if (HSEStatus == (uint32) 0x01)
	{
		/* Enable HSI */
		RCC->CR |= SYSTEM_DRIVER_HSI_ON;
		/* Wait till HSI is ready */
		while ((RCC->CR & SYSTEM_DRIVER_HSI_CLOCK_READY) == 0)
		{
		}

		/* Select HSI as system clock source */
		RCC->CFGR &= (uint32) ((uint32) ~(0x03));
		RCC->CFGR |= (uint32) SYSTEM_DRIVER_SWITCH_TO_HSI;

		/* Clear AHB,APB1 and APB2 prescalers*/
		RCC->CFGR &= (uint32) (~((0x0F) << 0x04));
		RCC->CFGR &= (uint32) (~((0x07) << 0x08));
		RCC->CFGR &= (uint32) (~((0x07) << 0x0B));

		/* Disable PLL */
		RCC->CR &= SYSTEM_DRIVER_PLL_OFF;

		/* HCLK = SYSCLK */
		RCC->CFGR |= (uint32) SYSTEM_DRIVER_HCLK_DIV;

		/* PCLK1 = HCLK */
		RCC->CFGR |= (uint32) SYSTEM_DRIVER_PCLK1_DIV;

		/* PCLK2 = HCLK */
		RCC->CFGR |= (uint32) SYSTEM_DRIVER_PCLK2_DIV;

		/*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
		RCC->CFGR &= (uint32) ((uint32) (~((uint32) ((0x0F << 0x12) | (0x01 << 0x10)))));
		RCC->CFGR |= (uint32) (SYSTEM_DRIVER_PLL_SOURCE | SYSTEM_DRIVER_PLL_MULTIPLIER);

		/* Enable PLL */
		RCC->CR |= SYSTEM_DRIVER_PLL_ON;

		/* Wait till PLL is ready */
		while ((RCC->CR & SYSTEM_DRIVER_PLL_CLOCK_READY) == 0)
		{
		}

#if(SYSTEM_DRIVER_CLK_SOURCE == SYSTEM_DRIVER_SWITCH_TO_HSI)

		/* Select configured clock source */
		RCC->CFGR &= (~(0x03));
		RCC->CFGR |= SYSTEM_DRIVER_CLK_SOURCE;

		/* Wait till HSI is used as system clock source */
		while ((RCC->CFGR & 0x0C) != 0x00)
		{
		}

#elif(SYSTEM_DRIVER_CLK_SOURCE == SYSTEM_DRIVER_SWITCH_TO_HSE)

		/* Select configured clock source */
		RCC->CFGR &= (~(0x03));
		RCC->CFGR |= SYSTEM_DRIVER_CLK_SOURCE;

		/* Wait till HSE is used as system clock source */
		while ((RCC->CFGR & 0x0C) != 0x04)
		{
		}

#elif(SYSTEM_DRIVER_CLK_SOURCE == SYSTEM_DRIVER_SWITCH_TO_PLL)

		/* Select configured clock source */
		RCC->CFGR &= (~(0x03));
		RCC->CFGR |= SYSTEM_DRIVER_CLK_SOURCE;

		/* Wait till PLL is used as system clock source */
		while ((RCC->CFGR & 0x0C) != 0x08)
		{
		}
#endif
	}
}

#if(SYSTEM_DRIVER_PVD_ENABLE==OK)

/*
 The device has an integrated POR/PDR circuitry that allows proper operation starting
 from/down to 2 V.

 The device remains in Reset mode when VDD/VDDA is below a specified threshold,
 VPOR/PDR, without the need for an external reset circuit.
 The PVD can be used to monitor the VDD/VDDA power supply by comparing it to a threshold
 selected by the PLS bits.
 */

void SYSTEM_Driver_PVD_Init()
{
	/*Enable the PWR module*/
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	SYSTEM_Driver_PVD_Disable();

	/*Select PVD threshold*/
	PWR->CR |= SYSTEM_DRIVER_PVD_THRESHOLD;

	SYSTEM_Driver_PVD_Enable();
}
void SYSTEM_Driver_PVD_Enable()
{
	/*Enable the Power voltage detector*/
	PWR->CR |= SYSTEM_DRIVER_PVD_ON;
}

void SYSTEM_Driver_PVD_Disable()
{
	/*Disable the Power voltage detector*/
	PWR->CR &= SYSTEM_DRIVER_PVD_OFF;
}

uint8 SYSTEM_Driver_PVD_Get_Power_Status()
{
	/*PVD output bit indicates the power consumption status (0 - above threshold, 1 - bellow threshold)*/

		uint8 ResultCode = FAILED;

		if ((PWR->CSR & SYSTEM_DRIVER_PVD_THRESHOLD_FLAG) != 0x00)
		{
			ResultCode = SUCCES;
		}
		else if((PWR->CSR & SYSTEM_DRIVER_PVD_THRESHOLD_FLAG) == 0x00)
		{
			ResultCode = FAILED;
		}
		else
		{
			/*Nothing to do*/
		}
		return ResultCode;
}

#endif

#if(SYSTEM_DRIVER_SLEEP_ENABLE == OK)
/*Sleep mode (CPU clock off, all peripherals including Cortex®-M3 core peripherals like
 NVIC, SysTick, etc. are kept running)*/
void SYSTEM_Driver_Enter_Sleep_Mode()
{
	/*Assure that the PWR module is enabled*/
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

#if (SYSTEM_DRIVER_SLEEP_MODE == SYSTEM_DRIVER_SLEEP_ON_EXIT)
	SCB->SCR |= (SYSTEM_DRIVER_SLEEP_ON_EXIT);
#elif (SYSTEM_DRIVER_SLEEP_MODE == SYSTEM_DRIVER_SLEEP_NOW)
	SCB->SCR |= (SYSTEM_DRIVER_SLEEP_NOW);
#else
	/*Nothing to do*/
#warning "The selected SYSTEM_DRIVER_SLEEP_MODE is not correct, choose one from the available ones !"
#endif

	/*Set the selected low-power mode, with the desired exit mode*/
#if (SYSTEM_DRIVER_SLEEP_ENTER == SYSTEM_DRIVER_USE_WFI)
	__WFI();
#elif (SYSTEM_DRIVER_SLEEP_ENTER == SYSTEM_DRIVER_USE_WFE)
	__WFE();
#else
	/*Nothing to do*/
#warning "The selected SYSTEM_DRIVER_SLEEP_ENTER is not correct, choose one from the available ones !"
#endif
	SCB->SCR &= (~SYSTEM_DRIVER_SLEEP_ON_EXIT);
}
#endif

#if(SYSTEM_DRIVER_STOP_ENABLE == OK)
/*Stop mode (all clocks are stopped)*/
void SYSTEM_Driver_Enter_Stop_Mode()
{
	/*Assure that the PWR module is enabled*/
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	/*Deep sleep mode stops most of the STM32 system and peripheral clocks.
	  At product level, this corresponds to either the Stop or the Standby mode.
	  In this case, its used for Stop mode.*/
	SCB->SCR|=SYSTEM_DRIVER_DEEP_SLEEP;

	/*To further reduce power consumption in Stop mode, the internal voltage regulator
	  can be put in low-power mode.*/
#if(SYSTEM_DRIVER_STOP_MODE_LP_ENABLE == OK)
	PWR->CR |= SYSTEM_DRIVER_STOP_MODE_LOW_POWER;
#elif (SYSTEM_DRIVER_STOP_MODE_LP_ENABLE == NOK)
	PWR->CR &= (~SYSTEM_DRIVER_STOP_MODE_LOW_POWER);
#else
	/*Nothing to do*/
#warning "The selected SYSTEM_DRIVER_STOP_MODE_LP_ENABLE is not correct, choose one from the available ones !"
#endif

	/*Set the selected low-power mode, with the desired exit mode*/
#if (SYSTEM_DRIVER_STOP_ENTER == SYSTEM_DRIVER_USE_WFI)
	__WFI();
#elif (SYSTEM_DRIVER_STOP_ENTER == SYSTEM_DRIVER_USE_WFE)
	__WFE();
#else
	/*Nothing to do*/
#warning "The selected SYSTEM_DRIVER_STOP_ENTER is not correct, choose one from the available ones !"
#endif
	SCB->SCR &=(~SYSTEM_DRIVER_DEEP_SLEEP);
}
#endif

#if(SYSTEM_DRIVER_STANDBY_ENABLE == OK)
/*Standby mode (1.8V domain powered-off)*/
void SYSTEM_Driver_Enter_Standby_Mode()
{
	/*Assure that the PWR module is enabled*/
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	/*Deep sleep mode stops most of the STM32 system and peripheral clocks.
	  At product level, this corresponds to either the Stop or the Standby mode.
	  In this case, its used for Stop mode.*/
	SCB->SCR |= SYSTEM_DRIVER_DEEP_SLEEP;

	/*Enter Standby mode when the CPU enters Deepsleep.
	 Shut down the voltage regulator. */
	PWR->CR |= SYSTEM_DRIVER_STANDY_BY_MODE_POWER_DOWN;

	/*Clear the wake up flag*/
	PWR->CR |= SYSTEM_DRIVER_WAKE_UP_FLAG_CLEAR;

	/*Set the wake-up pin, if required*/
#if(SYSTEM_DRIVER_WKUP_PIN_ENABLE == OK)
	PWR->CSR |= SYSTEM_DRIVER_WKUP_PIN;
#elif(SYSTEM_DRIVER_WKUP_PIN_ENABLE == NOK)
	PWR->CSR |= (~SYSTEM_DRIVER_WKUP_PIN);
#else
	/*Nothing to do*/
#warning "The selected SYSTEM_DRIVER_WKUP_PIN_ENABLE is not correct, choose one from the available ones !"
#endif

	/*Set the selected low-power mode, with the desired exit mode*/
#if (SYSTEM_DRIVER_STANDBY_ENTER == SYSTEM_DRIVER_USE_WFI)
	__WFI();
#elif (SYSTEM_DRIVER_STANDBY_ENTER == SYSTEM_DRIVER_USE_WFE)
	__WFE();
#else
	/*Nothing to do*/
#warning "The selected SYSTEM_DRIVER_STANDBY_ENTER is not correct, choose one from the available ones !"
#endif
}
#endif

uint8 SYSTEM_Driver_Enter_Standby_Mode_Check()
{
	uint8 State_variable = 0x00;

	/*Enable the PWR peripheral, so the Standby flag can be cleared*/
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	/*Check if the Standby flag has been set*/
	if((PWR->CSR & SYSTEM_DRIVER_STANDBY_FLAG)!=0x00)
	{
		State_variable = SYSTEM_DRIVER_STANDBY_FLAG_SET;
	}
	else if((PWR->CSR & SYSTEM_DRIVER_STANDBY_FLAG)==0x00)
	{
		State_variable = SYSTEM_DRIVER_STANDBY_FLAG_NOT_SET;
	}
	else
	{
		/*Nothing to do*/
	}

	/*Clear the Standby flag*/
	PWR->CR |= SYSTEM_DRIVER_STANDBY_FLAG_CLEAR;

	/*Disable the PWR peripheral because its not needed anymore*/
	RCC->APB1ENR &= (~RCC_APB1ENR_PWREN);

	return State_variable;
}

