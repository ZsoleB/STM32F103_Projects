/*
 * PWM_Driver.c
 *
 *  Created on: 29 ian. 2018
 *      Author: Zsole
 */
#include "PWM_Driver_Cfg.h"

void PWM_Driver_Init()
{
	uint16 index = 0x00;

	for(index=0x00;index<PWM_DRIVER_INSTANCE_NUM;index++)
	{
		switch(PWM_SETUP[index].PWM_Channel)
			{
				case PWM_Driver_Channel_1:
					PWM_SETUP[index].PWM_Timer->CCMR1 |=(((PWM_SETUP[index].PWM_Output_compare_preload_enable)<<0x03)
													  |  ((PWM_SETUP[index].PWM_Mode)<<0x04));
					PWM_SETUP[index].PWM_Timer->CCER  |=(((PWM_SETUP[index].PWM_polarity)<<0x01)
												   	  |  (PWM_SETUP[index].PWM_Capture_compare_enable));

					break;

				case PWM_Driver_Channel_2:
					PWM_SETUP[index].PWM_Timer->CCMR1  |=(((PWM_SETUP[index].PWM_Output_compare_preload_enable)<<0x0B)
													   |  ((PWM_SETUP[index].PWM_Mode)<<0x0C));
					PWM_SETUP[index].PWM_Timer->CCER   |=(((PWM_SETUP[index].PWM_polarity)<<0x05)
												   	   |  (PWM_SETUP[index].PWM_Capture_compare_enable<<0x04));
					break;

				case PWM_Driver_Channel_3:
					PWM_SETUP[index].PWM_Timer->CCMR2  |=(((PWM_SETUP[index].PWM_Output_compare_preload_enable)<<0x03)
													   |  ((PWM_SETUP[index].PWM_Mode)<<0x04));
					PWM_SETUP[index].PWM_Timer->CCER   |=(((PWM_SETUP[index].PWM_polarity)<<0x09)
												   	   |  (PWM_SETUP[index].PWM_Capture_compare_enable<<0x08));
					break;

				case PWM_Driver_Channel_4:
					PWM_SETUP[index].PWM_Timer->CCMR2   |=(((PWM_SETUP[index].PWM_Output_compare_preload_enable)<<0x0B)
														|  ((PWM_SETUP[index].PWM_Mode)<<0x0C));
					PWM_SETUP[index].PWM_Timer->CCER	|=(((PWM_SETUP[index].PWM_polarity)<<0x0D)
												   	   	|  (PWM_SETUP[index].PWM_Capture_compare_enable<<0x0C));
					break;
			};
	}
}

void PWM_Driver_SetDutyCylce(uint8 PWM_setup_nr, uint8 DutyCycle)
{
	DutyCycle = (uint16)DutyCycle;
	if(DutyCycle<0)
	{
		DutyCycle = 0;
	}
	else if(DutyCycle>100)
	{
		DutyCycle = 100;
	}

	switch(PWM_SETUP[PWM_setup_nr].PWM_Channel)
	{
		case PWM_Driver_Channel_1:
			PWM_SETUP[PWM_setup_nr].PWM_Timer->CCR1 = ((uint16)(((PWM_SETUP[PWM_setup_nr].PWM_Timer->ARR)*DutyCycle)/100));
			break;

		case PWM_Driver_Channel_2:
			PWM_SETUP[PWM_setup_nr].PWM_Timer->CCR2 = ((uint16)(((PWM_SETUP[PWM_setup_nr].PWM_Timer->ARR)*DutyCycle)/100));
			break;

		case PWM_Driver_Channel_3:
			PWM_SETUP[PWM_setup_nr].PWM_Timer->CCR3 = ((uint16)(((PWM_SETUP[PWM_setup_nr].PWM_Timer->ARR)*DutyCycle)/100));
			break;

		case PWM_Driver_Channel_4:
			PWM_SETUP[PWM_setup_nr].PWM_Timer->CCR4 = ((uint16)(((PWM_SETUP[PWM_setup_nr].PWM_Timer->ARR)*DutyCycle)/100));
			break;
	};
}
