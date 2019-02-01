/*
 * TCNT_Driver.h
 *
 *  Created on: Apr 19, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_TIM_DRIVER_TCNT_DRIVER_H_
#define DRIVERS_TIM_DRIVER_TCNT_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"

#define TCNT_DRIVER_CAPTURE_COMPARE_4_OVERCAPTURE_FLAG 					((uint8)(1<<12))
#define TCNT_DRIVER_CAPTURE_COMPARE_3_OVERCAPTURE_FLAG 					((uint8)(1<<11))
#define TCNT_DRIVER_CAPTURE_COMPARE_2_OVERCAPTURE_FLAG 					((uint8)(1<<10))
#define TCNT_DRIVER_CAPTURE_COMPARE_1_OVERCAPTURE_FLAG 					((uint8)(1<<9))
#define TCNT_DRIVER_TRIGGER_INTERRUPT_FLAG             					((uint8)(1<<6))
#define TCNT_DRIVER_CAPTURE_COMPARE_4_INTERRUPT FLAG   					((uint8)(1<<4))
#define TCNT_DRIVER_CAPTURE_COMPARE_3_INTERRUPT FLAG   					((uint8)(1<<3))
#define TCNT_DRIVER_CAPTURE_COMPARE_2_INTERRUPT FLAG   					((uint8)(1<<2))
#define TCNT_DRIVER_CAPTURE_COMPARE_1_INTERRUPT FLAG   					((uint8)(1<<1))
#define TCNT_DRIVER_UPDATE_GENERATION              						((uint8)(1<<0))
#define TCNT_DRIVER_UPDATE_INTERRUPT_FLAG              					((uint8)(1<<0))
#define TCNT_DRIVER_UP_COUNTER											((uint8)(0x00<<4))
#define TCNT_DRIVER_DOWN_COUNTER										((uint8)(0x01<<4))
#define TCNT_DRIVER_COUNTER_ENABLE										((uint8)(0x01))
#define TCNT_DRIVER_COUNTER_DISABLE										((uint8)(0x00))

typedef void (*TCNT_Driver_callback_type)();

typedef struct
{
	TIM_TypeDef* Timer;
	uint8 TimerDirection;
	uint32 TimerPrescaler;
	uint32 TimerPeriod;

}TCNT_Driver_Setup_Type;

extern TCNT_Driver_Setup_Type* TCNT_SETUP;

void TCNT_Driver_Init();
void TCNT_Driver_SetPeriod(uint8 TCNT_setup_nr,uint32 PeriodValue);
void TCNT_Driver_SetPrescale(uint8 TCNT_setup_nr,uint32 PrescaleValue);
void TCNT_Setup_Callbacks();
void TCNT_Driver_ClearStatus(uint8 TCNT_setup_nr);
uint8 TCNT_Driver_GetStatus(uint8 TCNT_setup_nr,uint8 Event);
void TCNT_Driver_Start(uint8 TCNT_setup_nr);

#endif /* DRIVERS_TIM_DRIVER_TCNT_DRIVER_H_ */
