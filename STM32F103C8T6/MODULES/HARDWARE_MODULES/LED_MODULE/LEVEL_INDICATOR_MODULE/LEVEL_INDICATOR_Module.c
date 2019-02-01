/*
 * LEVEL_INDICATOR_Module.c
 *
 *  Created on: Sep 10, 2018
 *      Author: zsolt.balo
 */

#include "LEVEL_INDICATOR_Module_Cfg.h"


void LEVEL_INDICATOR_Module_Update_Display(uint8 Level_Indicator_Number,uint8 Level_value)
{
	LEVEL_INDICATOR_Module_Clear(Level_Indicator_Number);

	#if(LEVEL_INDICATOR_MODULE_INTERFACE == LEVEL_INDICATOR_MODULE_GPIO_INTERFACE)

		if(Level_value>0x00)
		{
			LED_Module_Set_On(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_0_Indicator);
		}
		if(Level_value>0x01)
		{
			LED_Module_Set_On(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_1_Indicator);
		}
		if(Level_value>0x02)
		{
			LED_Module_Set_On(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_2_Indicator);
		}
		if(Level_value>0x03)
		{
			LED_Module_Set_On(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_3_Indicator);
		}
		if(Level_value>0x04)
		{
			LED_Module_Set_On(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_4_Indicator);
		}
		if(Level_value>0x05)
		{
			LED_Module_Set_On(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_5_Indicator);
		}
		if(Level_value>0x06)
		{
			LED_Module_Set_On(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_6_Indicator);
		}
		if(Level_value>0x07)
		{
			LED_Module_Set_On(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_7_Indicator);
		}
		if(Level_value>0x08)
		{
			LED_Module_Set_On(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_8_Indicator);
		}
		if(Level_value>0x09)
		{
			LED_Module_Set_On(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_9_Indicator);
		}

	#endif
}

void LEVEL_INDICATOR_Module_Clear(uint8 Level_Indicator_Number)
{
	#if(LEVEL_INDICATOR_MODULE_INTERFACE == LEVEL_INDICATOR_MODULE_GPIO_INTERFACE)

	LED_Module_Set_Off(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_0_Indicator);
	LED_Module_Set_Off(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_1_Indicator);
	LED_Module_Set_Off(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_2_Indicator);
	LED_Module_Set_Off(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_3_Indicator);
	LED_Module_Set_Off(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_4_Indicator);
	LED_Module_Set_Off(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_5_Indicator);
	LED_Module_Set_Off(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_6_Indicator);
	LED_Module_Set_Off(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_7_Indicator);
	LED_Module_Set_Off(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_8_Indicator);
	LED_Module_Set_Off(LEVEL_INDICATOR_SETUP[Level_Indicator_Number].LEVEL_9_Indicator);

	#endif
}

#if(LEVEL_INDICATOR_MODULE_INTERFACE == LEVEL_INDICATOR_MODULE_GPIO_INTERFACE)

	void LEVEL_INDICATOR_Module_Set_Dimming(uint8 Level_Indicator_Number,uint8 DutyCycle)
	{
		LED_Module_Set_Dimming(Level_Indicator_Number,DutyCycle);
	}


#else

	void LEVEL_INDICATOR_Module_Set_Dimming(uint32 Level_Indicator_Number,uint8 DutyCycle)
	{
		/*When the Port Expnader Module is used the dimming is not available*/
	}
#endif
