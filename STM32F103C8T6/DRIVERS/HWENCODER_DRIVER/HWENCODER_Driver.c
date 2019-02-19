/*
 * HWENCODER_Driver.c
 *
 *  Created on: 19 feb. 2018
 *      Author: Zsole
 */
#include "HWENCODER_Driver_Cfg.h"

void HWENCODER_Driver_Init()
{
	uint16 index = 0x00;

	for(index=0x00;index<HWENCODER_DRIVER_INSTANCE_NUM;index++)
	{
		if (HWENCODER_SETUP[index].HWENCODER_Driver_selected_timer_input == HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1)
		{

			HWENCODER_SETUP[index].Timer_Source->SMCR |= HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1;
		}
		else if (HWENCODER_SETUP[index].HWENCODER_Driver_selected_timer_input == HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_2)
		{

			HWENCODER_SETUP[index].Timer_Source->SMCR |= HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_2;
		}

		else if (HWENCODER_SETUP[index].HWENCODER_Driver_selected_timer_input == HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1_AND_2)
		{

			HWENCODER_SETUP[index].Timer_Source->SMCR |= HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1_AND_2;
		}

		else
		{
			/*Nothing to do*/
		}


		if (HWENCODER_SETUP[index].HWENCODER_Driver_Channel_pair == HWENCODER_DRIVER_CHANNEL_1_AND_2)
		{
			HWENCODER_SETUP[index].Timer_Source->CCMR1 |= HWENCODER_SETUP[index].HWENCODER_Driver_Capture_Compare_selection_primary
					| HWENCODER_SETUP[index].HWENCODER_Driver_Capture_Compare_selection_secondary;
		}
		else if (HWENCODER_SETUP[index].HWENCODER_Driver_Channel_pair == HWENCODER_DRIVER_CHANNEL_3_AND_4)
		{
			HWENCODER_SETUP[index].Timer_Source->CCMR2 |= HWENCODER_SETUP[index].HWENCODER_Driver_Capture_Compare_selection_primary
					| HWENCODER_SETUP[index].HWENCODER_Driver_Capture_Compare_selection_secondary;
		}
		else
		{
			/*Nothing to do*/
		}
		HWENCODER_SETUP[index].Timer_Source->CCER |= HWENCODER_SETUP[index].HWENCODER_Driver_Capture_Compare_outputs;
		HWENCODER_SETUP[index].Timer_Source->CNT = (MAX16 - 1);
	}
}
uint32 HWENCODER_Driver_Get_Count_Value(uint8 HWENCODER_setup_nr)
{
	return (uint32) (HWENCODER_SETUP[HWENCODER_setup_nr].Timer_Source->CNT);
}


