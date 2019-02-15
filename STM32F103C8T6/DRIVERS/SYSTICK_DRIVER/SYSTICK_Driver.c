/*
 * SYSTICK_Driver.c
 *
 *  Created on: May 3, 2018
 *      Author: zsolt.balo
 */

/*
 * The processor has a 24-bit system timer, SysTick, that counts down from the reload value to
 * zero, reloads (wraps to) the value in the LOAD register on the next clock edge, then counts
 * down on subsequent clocks.
 *
 * When the processor is halted for debugging the counter does not decrement.
 *
 * The SysTick counter runs on the processor clock. If this clock signal is stopped for low
 * power mode, the SysTick counter stops.
 *
 * Ensure software uses aligned word accesses to access the SysTick registers
 */

#include "NVIC_Driver_Cfg.h"
#include "SYSTICK_Driver_Cfg.h"

static volatile uint32 Tick_Counter=0x00;

void SysTick_Handler()
{
	if(Tick_Counter!=0x00)
	{
		Tick_Counter--;
	}
}

void SYSTICK_Driver_Init()
{
	/*Set the processor clock as the clock source */
	SysTick->CTRL|=(0x01<<0x02);
	#if(SYSTICK_DRIVER_ENABLE_INTERRUPT == OK)
		/*Set the timer interrupt and its priority and sub-priority*/
		NVIC_Driver_PriorityGroupConfig(NVIC_DRIVER_PRIORITY_GRUP_4);
		NVIC_Driver_Set_SYSTICK_Interrupt(0x0F,0x00);
	#endif
	/*Init the Systick current value register*/
	SysTick->VAL = 0x00;
	/*Set the load register with the configured value*/
	SysTick->LOAD = ((SYSTICK_DRIVER_LOAD & 0xFFFFFFUL)-1);

	SYSTICK_Driver_Start();
}

void SYSTICK_Driver_Start()
{
	/*Enable the systick timer*/
	SysTick->CTRL|=0x01;
}

void SYSTICK_Driver_Stop()
{
	/*Disable the systick timer*/
	SysTick->CTRL &=(~(0x01));
}

uint32 SYSTICK_Driver_GetClockValue()
{
	/*Get the current counter value*/
	uint32 Systick_Cnt_value = 0x00;
	Systick_Cnt_value = SysTick->VAL;
	return Systick_Cnt_value;
}

uint8 SYSTICK_Driver_GetCountFlag()
{
	uint8 result = 0x00;
	result = (SysTick->CTRL & (0x01<<0x10))?0x01:0x00;
	return result;
}

#if (SYSTICK_DRIVER_LOAD == ((SYSTICK_DRIVER_WORKING_FREQUENCY)/1000))

void SYSTICK_Driver_Delay_ms(uint32 DelayInterval)
{
	Tick_Counter = DelayInterval;
	while(Tick_Counter!=0x00){}
}

#elif (SYSTICK_DRIVER_LOAD ==  ((SYSTICK_DRIVER_WORKING_FREQUENCY)/1000000))

void SYSTICK_Driver_Delay_us(uint32 DelayInterval)
{
	Tick_Counter = DelayInterval;
	while(Tick_Counter!=0x00){}
}

#else

void SYSTICK_Driver_Delay(uint32 DelayInterval)
{
	Tick_Counter = DelayInterval;
	while(Tick_Counter!=0x00){}
}

#endif

