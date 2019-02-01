/*
 * PWM_Driver.h
 *
 *  Created on: 29 ian. 2018
 *      Author: Zsole
 */

#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_

#include "stm32f10x.h"
#include "TCNT_Driver_Cfg.h"
#include "StdTypes.h"

#define PWM_DRIVER_ACTIVE_HIGH 							((uint8)0x00)
#define PWM_DRIVER_ACTIVE_LOW							((uint8)0x01)
#define PWM_DRIVER_CC_1 								((uint8)0x01)
#define PWM_DRIVER_CC_2 								((uint8)0x02)
#define PWM_DRIVER_CC_3 								((uint8)0x03)
#define PWM_DRIVER_CC_4 								((uint8)0x04)

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

void PWM_Driver_Init(TIM_TypeDef *TIMx);
void PWM_Driver_SetDutyCylce(TIM_TypeDef *TIMx, uint32 DutyCycle);
void PWM_Driver_SetPeriod(TIM_TypeDef *TIMx,uint32 Period);

#endif /* PWM_DRIVER_H_ */
