/*
 * WWDT_Driver.c
 *
 *  Created on: Aug 27, 2018
 *      Author: zsolt.balo
 */

#include "WWDT_Driver_cfg.h"
/*
 The WWDT period calculation formula is the following:

	t_WWDG = t_PCLK1 × 4096 x 2^WDGTB[1:0] x (T[5:0] + 1) (ms)

 Reset occurs when:
	*if the watchdog is activated
	*when the downcounter value becomes less than 0x40
	*if the downcounter is reloaded outside the window

 Early wakeup interrupt (EWI) is triggered (if enabled and the watchdog activated) when
 the downcounter is equal to 0x40.

 The application program must write in the WWDG_CR register at regular intervals during
 normal operation to prevent an MCU reset. This operation must occur only when the counter
 value is lower than the window register value. The value to be stored in the WWDG_CR
 register must be between 0xFF and 0xC0.

 */

/*
#if (WWDT_DRIVER_INTERRUPT_ENABLED == OK)

void WWDG_IRQHandler()
{
	WWDT_Driver_Refresh_WWDT_Counter();
	WWDT_Driver_Clear_Interrupt_Flag();
	GPIO_Driver_Lambda_function();
}==> Modify accordingly

#endif
*/

void WWDT_Driver_Init()
{
	/*Enable WWDT Peripheral clock*/
	RCC->APB1ENR |= RCC_APB1ENR_WWDGEN;

	#if (WWDT_DRIVER_INTERRUPT_ENABLED == OK)
		WWDG->CFR|= WWDT_DRIVER_INTERRUPT_ENABLE;
	#endif

	/*Set WWDT Timebase of the prescaler*/
	WWDG->CFR|=WWDT_DRIVER_PRESCALER_TIME_BASE;

	/*Set WWDT Window value */
	WWDG->CFR|=WWDT_DRIVER_WINDOW_VALUE;

	/*Enable WWDT */
	/*When the watchdog is enabled, the T6 bit must be set to prevent generating an immediate reset.*/
	/*Set WWDT Counter value */
	WWDG->CR |= WWDT_DRIVER_ACTIVATION|WWDT_DRIVER_T6_BIT_SET|WWDT_DRIVER_COUNTER_VALUE;

}

void WWDT_Driver_Refresh_WWDT_Counter()
{
	WWDG->CR |= WWDT_DRIVER_T6_BIT_SET|WWDT_DRIVER_COUNTER_VALUE;
}

void WWDT_Driver_SW_Reset()
{
	/*Set the T6 bit to 0, forcing the WWDT to reset the MC */
	WWDG->CR &= WWDT_DRIVER_T6_BIT_CLEAR;
}

void WWDT_Driver_Clear_Interrupt_Flag()
{
	/*Set the T6 bit to 0, forcing the WWDT to reset the MC */
	WWDG->SR = 0x00;
}
