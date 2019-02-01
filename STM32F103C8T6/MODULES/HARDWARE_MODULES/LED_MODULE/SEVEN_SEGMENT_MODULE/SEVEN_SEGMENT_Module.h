/*
 * 7SEGMENT_Module.h
 *
 *  Created on: Sep 11, 2018
 *      Author: zsolt.balo
 */

#ifndef MODULES_HARDWARE_MODULES_LED_MODULE_SEVEN_SEGMENT_MODULE_SEVEN_SEGMENT_MODULE_H_
#define MODULES_HARDWARE_MODULES_LED_MODULE_SEVEN_SEGMENT_MODULE_SEVEN_SEGMENT_MODULE_H_

#include "LED_Module_Cfg.h"
#include "SHIFT_REGISTER_Module_Cfg.h"

#define SEVEN_SEGMENT_MODULE_GPIO_INTERFACE 					0x00
#define SEVEN_SEGMENT_MODULE_SHIFT_REGISTER_INTERFACE 			0x01

#define SEVEN_SEGMENT_LED_A									(0x01<<0x00)
#define SEVEN_SEGMENT_LED_B									(0x01<<0x01)
#define SEVEN_SEGMENT_LED_C									(0x01<<0x02)
#define SEVEN_SEGMENT_LED_D									(0x01<<0x03)
#define SEVEN_SEGMENT_LED_E									(0x01<<0x04)
#define SEVEN_SEGMENT_LED_F									(0x01<<0x05)
#define SEVEN_SEGMENT_LED_G									(0x01<<0x06)
#define SEVEN_SEGMENT_LED_POINT								(0x01<<0x07)

typedef enum
{
	SEVEN_SEGMENT_0,
	SEVEN_SEGMENT_1,
	SEVEN_SEGMENT_2,
	SEVEN_SEGMENT_3,
	SEVEN_SEGMENT_4,
	SEVEN_SEGMENT_5,
	SEVEN_SEGMENT_6,
	SEVEN_SEGMENT_7,
	SEVEN_SEGMENT_8,
	SEVEN_SEGMENT_9,
	SEVEN_SEGMENT_A,
	SEVEN_SEGMENT_B,
	SEVEN_SEGMENT_C,
	SEVEN_SEGMENT_E,
	SEVEN_SEGMENT_F,
	SEVEN_SEGMENT_G,
	SEVEN_SEGMENT_H,
	SEVEN_SEGMENT_I,
	SEVEN_SEGMENT_J,
	SEVEN_SEGMENT_L,
	SEVEN_SEGMENT_O,
	SEVEN_SEGMENT_P,
	SEVEN_SEGMENT_S,
	SEVEN_SEGMENT_U,
	SEVEN_SEGMENT_Z,
}SEVEN_SEGMENT_Module_Characters;

typedef struct
{
	uint8 LEVEL_A_Indicator;
	uint8 LEVEL_B_Indicator;
	uint8 LEVEL_C_Indicator;
	uint8 LEVEL_D_Indicator;
	uint8 LEVEL_E_Indicator;
	uint8 LEVEL_F_Indicator;
	uint8 LEVEL_G_Indicator;
	uint8 LEVEL_POINT_Indicator;

}SEVEN_SEGMENT_Module_Setup_Type;

extern SEVEN_SEGMENT_Module_Setup_Type* SEVEN_SEGMENT_SETUP;

typedef struct
{
	uint8 SHIFT_REGISTER_INSTANCE;

}SEVEN_SEGMENT_Module_Shift_Register_Instance;

extern SEVEN_SEGMENT_Module_Shift_Register_Instance* SEVEN_SEGMENT_SR_SETUP;

void SEVEN_SEGMENT_Module_Init_Cfg();
void SEVEN_SEGMENT_Module_Update_Display(uint8 Seven_Segment_setup_Nr,uint8 Characther);
void SEVEN_SEGMENT_Module_Clear(uint8 Seven_Segment_setup_Nr);
void SEVEN_SEGMENT_Module_Set_Dimming(uint8 Seven_Segment_setup_Nr,uint8 DutyCycle);


#endif /* MODULES_HARDWARE_MODULES_LED_MODULE_SEVEN_SEGMENT_MODULE_SEVEN_SEGMENT_MODULE_H_ */
