/*
 * JOYSTICK_Module.c
 *
 *  Created on: Sep 11, 2018
 *      Author: zsolt.balo
 */

#include "JOYSTICK_Module_Cfg.h"

uint8 JOYSTICK_Module_Pressed(uint8 Joystick_nr)
{
	uint8 Button_Status = 0x00;
	Button_Status = BUTTON_Module_Read_Value(JOYSTICK_SETUP[Joystick_nr].JOYSTICK_Button);
	return Button_Status;
}

void JOYSTICK_Dirrection_Measurement(uint8 Joystick_nr)
{
		ADC_Driver_StartSampling(JOYSTICK_SETUP[Joystick_nr].JOYSTICK_X);
		while(ADC_Driver_GetStatus(JOYSTICK_SETUP[Joystick_nr].JOYSTICK_X,ADC_DRIVER_REGULAR_CHANNEL_END_OF_CONVERSION_FLAG)!=SUCCES){}
		JOYSTICK_SETUP[Joystick_nr].JOYSTICK_X_Value = (uint8)(ADC_Driver_GetSample(JOYSTICK_SETUP[Joystick_nr].JOYSTICK_X)>>4);
		ADC_Driver_ClearStatus(JOYSTICK_SETUP[Joystick_nr].JOYSTICK_X);

		ADC_Driver_StartSampling(JOYSTICK_SETUP[Joystick_nr].JOYSTICK_Y);
		while(ADC_Driver_GetStatus(JOYSTICK_SETUP[Joystick_nr].JOYSTICK_Y,ADC_DRIVER_REGULAR_CHANNEL_END_OF_CONVERSION_FLAG)!=SUCCES){}
		JOYSTICK_SETUP[Joystick_nr].JOYSTICK_Y_Value = (uint8)(ADC_Driver_GetSample(JOYSTICK_SETUP[Joystick_nr].JOYSTICK_Y)>>4);
		ADC_Driver_ClearStatus(JOYSTICK_SETUP[Joystick_nr].JOYSTICK_Y);
}

uint8 JOYSTICK_Get_X_Value(uint8 Joystick_nr)
{
	JOYSTICK_Dirrection_Measurement(Joystick_nr);
	return JOYSTICK_SETUP[Joystick_nr].JOYSTICK_X_Value;
}

uint8 JOYSTICK_Get_Y_Value(uint8 Joystick_nr)
{
	JOYSTICK_Dirrection_Measurement(Joystick_nr);
	return JOYSTICK_SETUP[Joystick_nr].JOYSTICK_Y_Value;
}
