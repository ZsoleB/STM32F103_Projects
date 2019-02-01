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

void TCNT_Driver_Init(TIM_TypeDef* TIMx);
void TCNT_Driver_SetPeriod(TIM_TypeDef* TIMx,uint32 PeriodValue);
void TCNT_Driver_SetPrescale(TIM_TypeDef* TIMx,uint32 PrescaleValue);
void TCNT_Driver_ClearStatus(TIM_TypeDef* TIMx);
uint8 TCNT_Driver_GetStatus(TIM_TypeDef* TIMx,uint8 Event);
void TCNT_Driver_Start(TIM_TypeDef* TIMx);

#endif /* DRIVERS_TIM_DRIVER_TCNT_DRIVER_H_ */
