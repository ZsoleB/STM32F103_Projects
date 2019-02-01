/*
 * JOYSTICK_Module.h
 *
 *  Created on: Sep 11, 2018
 *      Author: zsolt.balo
 */

#ifndef MODULES_HARDWARE_MODULES_BUTTON_MODULE_JOYSTICK_MODULE_JOYSTICK_MODULE_H_
#define MODULES_HARDWARE_MODULES_BUTTON_MODULE_JOYSTICK_MODULE_JOYSTICK_MODULE_H_

#include "BUTTON_Module_Cfg.h"

typedef struct
{
	uint8 JOYSTICK_Button;
	uint8 JOYSTICK_X;
	uint8 JOYSTICK_Y;
	uint8 JOYSTICK_X_Value;
	uint8 JOYSTICK_Y_Value;
}JOYSTICK_Module_Setup_Type;

extern JOYSTICK_Module_Setup_Type* JOYSTICK_SETUP;

void JOYSTICK_Module_Init_Cfg();
uint8 JOYSTICK_Module_Pressed(uint8 Joystick_nr);
uint8 JOYSTICK_Get_X_Value(uint8 Joystick_nr);
uint8 JOYSTICK_Get_Y_Value(uint8 Joystick_nr);
void JOYSTICK_Dirrection_Measurement(uint8 Joystick_nr);

#endif /* MODULES_HARDWARE_MODULES_BUTTON_MODULE_JOYSTICK_MODULE_JOYSTICK_MODULE_H_ */
