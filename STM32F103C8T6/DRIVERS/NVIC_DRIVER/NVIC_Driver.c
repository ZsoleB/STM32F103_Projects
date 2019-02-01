/*
 * NVIC_Driver.c
 *
 *  Created on: Apr 20, 2018
 *      Author: zsolt.balo
 */

#include "NVIC_Driver_Cfg.h"

void NVIC_Driver_SetInterrupt(IRQn_Type IRQChannel, uint8 Preemption_Priority,uint8 Sub_Priority)
{
	uint8 PriorityGroup						 = 0x00;
	uint8 Configured_Group_priority_position = 0x00;
	uint8 Configured_Sub_priority_position 	 = 0x0F;
	uint8 Configured_Group_priority 		 = 0x00;
	uint8 Configured_Sub_priority 			 = 0x0F;
	uint8 Priority_Config 			 		 = 0x00;

	/*Select the configured priority group*/
	PriorityGroup = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;

	/* In the following steps, the value of the shift positions will be calculated to
	 * configure the respective priority configurations, following the example bellow
	 *
	 * ex: If prio.config. is 4(100), that means
	 * we will have 3 group priorities and 1 sub priority
	 *
	 * the maximum available value is 7
	 * Group prio. bits =  4 - (max.value-conf.prior.) <== these have to be shifted to left (XXXn.0000)
	 * Sub prio. bits = 0x0F >> (max.value-conf.prior.)  <== these have to be shifted to right  (nnnY.0000)
	 * */

	Configured_Sub_priority_position = Configured_Sub_priority_position >> (PriorityGroup);
	Configured_Group_priority_position = 0x04 - PriorityGroup;

	Configured_Group_priority = Preemption_Priority << Configured_Group_priority_position;
	Configured_Sub_priority   = Sub_Priority & Configured_Sub_priority_position;
	/*The lower 4 bits are not used*/
	Priority_Config = ((Configured_Group_priority|Configured_Sub_priority)<<4);
	if(IRQChannel<0)
	{
		/* set Priority for Cortex-M  System Interrupts */
		SCB->SHP[((uint32_t)(IRQChannel) & 0xF)-4] = Priority_Config;
	}
	else
	{
		NVIC->IP[IRQChannel] = Priority_Config;
	}


	/*Set the given interrupt. To select the correct register from the available 4, the channel number has
	 * to be shifted to the left by 5 (division by 32, because each register can hold 32 values)
	 * to write the channel to the given position (IRQ = 7 goes to position 7)*/
    NVIC->ISER[IRQChannel >> 0x05] =
      (uint32_t)0x01 << (IRQChannel & (uint8_t)0x1F);
    /*The final &-ing is used to assure that the channel number isn't bigger the 31
     * The bigger values will be subtracted this way, to the correct position number
     * */
}

void NVIC_Driver_ClearInterrupt(uint8 IRQChannel)
{
	NVIC->ICER[IRQChannel >> 0x05] =
	      (uint32_t)0x01 << (IRQChannel & (uint8_t)0x1F);
}

void NVIC_Driver_PriorityGroupConfig(uint8 Prioritygroup)
{
	uint32 Old_register_value = 0x00;
	uint32 New_register_value = 0x00;

	Old_register_value = SCB->AIRCR;
	Old_register_value &= ~(NVIC_DRIVER_AIRCR_VECTORKEY_CLEAR_MASK|NVIC_DRIVER_PRIORITY_GROUP_MASK);

	New_register_value = (Old_register_value)|(NVIC_DRIVER_AIRCR_VECTORKEY_MASK)|(Prioritygroup<<8);

	SCB->AIRCR = New_register_value;
}

#if (NVIC_DRIVER_TIMER_INTERRUPT_ENABLE	== OK)

	#include "TCNT_Driver_Cfg.h"

	void NVIC_Driver_SetTimer_Update_Interrupt(uint8 Preemption_priority,uint8 Sub_priority)
	{
		#if ((TCNT_DRIVER_TIMER_4)==OK)
			TIM4->DIER |=(TCNT_DRIVER_UPDATE_GENERATION);
			NVIC_Driver_SetInterrupt(TIM4_IRQn,Preemption_priority,Sub_priority);
		#endif

		#if ((TCNT_DRIVER_TIMER_3)==OK)
			TIM3->DIER |=(TCNT_DRIVER_UPDATE_GENERATION);
			NVIC_Driver_SetInterrupt(TIM3_IRQn,Preemption_priority,Sub_priority);
		#endif

		#if ((TCNT_DRIVER_TIMER_2)==OK)
			TIM2->DIER |=(TCNT_DRIVER_UPDATE_GENERATION);
			NVIC_Driver_SetInterrupt(TIM2_IRQn,Preemption_priority,Sub_priority);
		#endif

		#if ((TCNT_DRIVER_TIMER_1)==OK)
			TIM1->DIER |=(TCNT_DRIVER_UPDATE_GENERATION);
			NVIC_Driver_SetInterrupt(TIM1_CC_IRQn,Preemption_priority,Sub_priority);
		#endif
	}

#endif

#if (NVIC_DRIVER_EXTI_INTERRUPT_ENABLE	== OK)
	void NVIC_Driver_Set_EXTI_Interrupt(uint8 Preemption_priority,uint8 Sub_priority)
	{

	#ifdef NVIC_DRIVER_EXTI_0_FLAG
				NVIC_Driver_SetInterrupt(EXTI0_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_1_FLAG
				NVIC_Driver_SetInterrupt(EXTI1_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_2_FLAG
			NVIC_Driver_SetInterrupt(EXTI2_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_3_FLAG
					NVIC_Driver_SetInterrupt(EXTI3_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_4_FLAG
			NVIC_Driver_SetInterrupt(EXTI4_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_5_FLAG
			NVIC_Driver_SetInterrupt(EXTI9_5_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_6_FLAG
			NVIC_Driver_SetInterrupt(EXTI9_5_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_7_FLAG
			NVIC_Driver_SetInterrupt(EXTI9_5_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_8_FLAG
			NVIC_Driver_SetInterrupt(EXTI9_5_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_9_FLAG
			NVIC_Driver_SetInterrupt(EXTI9_5_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_10_FLAG
			NVIC_Driver_SetInterrupt(EXTI15_10_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_11_FLAG
			NVIC_Driver_SetInterrupt(EXTI15_10_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_12_FLAG
			NVIC_Driver_SetInterrupt(EXTI15_10_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_13_FLAG
			NVIC_Driver_SetInterrupt(EXTI15_10_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_14_FLAG
			NVIC_Driver_SetInterrupt(EXTI15_10_IRQn,Preemption_priority,Sub_priority);
	#endif

	#ifdef NVIC_DRIVER_EXTI_15_FLAG
			NVIC_Driver_SetInterrupt(EXTI15_10_IRQn,Preemption_priority,Sub_priority);
	#endif
	}
#endif

#if (NVIC_DRIVER_SYSTICK_INTERRUPT_ENABLE == OK)
	void NVIC_Driver_Set_SYSTICK_Interrupt(uint8 Preemption_priority,uint8 Sub_priority)
	{
		/*Enable the Systick interrupt */
		SysTick->CTRL|=(0x01<<0x01);
		NVIC_Driver_SetInterrupt(SysTick_IRQn,Preemption_priority,Sub_priority);
	}
#endif

#if(NVIC_DRIVER_RTC_INTERRUPT_ENABLE == OK)
	void NVIC_Driver_Set_RTC_Interrupt(uint8 Preemption_priority,uint8 Sub_priority)
	{
		#if(NVIC_RTC_OVERFLOW_INTERRUPT_FLAG == OK)
			/*Enable overflow interrupt*/
			RTC->CRH |= RTC_DRIVER_OVERFLOW_INTERRUPT_ENABLE;
			NVIC_Driver_SetInterrupt(RTC_IRQn,Preemption_priority,Sub_priority);
		#endif

		#if(NVIC_RTC_ALARM_INTERRUPT_FLAG == OK)
			/*Enable alarm interrupt*/
			RTC->CRH |= RTC_DRIVER_ALARM_INTERRUPT_ENABLE;
			NVIC_Driver_SetInterrupt(RTC_IRQn,Preemption_priority,Sub_priority);
		#endif

		#if(NVIC_RTC_SECOND_INTERRUPT_FLAG == OK)
			/*Enable second interrupt*/
			RTC->CRH |= RTC_DRIVER_SECOND_INTERRUPT_ENABLE;
			NVIC_Driver_SetInterrupt(RTC_IRQn,Preemption_priority,Sub_priority);
		#endif
	}
#endif

#if (NVIC_DRIVER_WWDT_INTERRUPT_ENABLE == OK)

	#include "WWDT_Driver_cfg.h"

	void NVIC_Driver_Set_WWDT_Interrupt(uint8 Preemption_priority,uint8 Sub_priority)
	{
		/*Enable the WWDT interrupt */
		WWDG->CFR|= WWDT_DRIVER_INTERRUPT_ENABLE;
		NVIC_Driver_SetInterrupt(WWDG_IRQn,Preemption_priority,Sub_priority);
	}
#endif
