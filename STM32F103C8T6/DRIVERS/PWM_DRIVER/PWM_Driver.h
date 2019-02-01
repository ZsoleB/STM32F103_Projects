/*
 * PWM_Driver.h
 *
 *  Created on: 29 ian. 2018
 *      Author: Zsole
 */

#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"

#define PWM_DRIVER_ACTIVE_HIGH 							((uint8)0x00)
#define PWM_DRIVER_ACTIVE_LOW							((uint8)0x01)

/*
 In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
else inactive. In downcounting, channel 1 is inactive (OC1REF=0) as long as
TIMx_CNT>TIMx_CCR1 else active (OC1REF=1).
*/
#define PWM_DRIVER_PWM_MODE_1 							((uint8)0x06)

/*
 In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1
else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else
inactive.
*/
#define PWM_DRIVER_PWM_MODE_2 							((uint8)0x07)

typedef enum
{
	PWM_Driver_Channel_1,
	PWM_Driver_Channel_2,
	PWM_Driver_Channel_3,
	PWM_Driver_Channel_4
}PWM_Driver_Channels;

typedef struct
{
	TIM_TypeDef* PWM_Timer;
	PWM_Driver_Channels PWM_Channel;
	uint8 PWM_Mode;
	uint8 PWM_Output_compare_preload_enable;
	uint8 PWM_polarity;
	uint8 PWM_Capture_compare_enable;
}PWM_Driver_Setup_Type;

extern PWM_Driver_Setup_Type* PWM_SETUP;

void PWM_Driver_Init();
void PWM_Driver_SetDutyCylce(uint8 PWM_setup_nr, uint8 DutyCycle);

#endif /* PWM_DRIVER_H_ */
