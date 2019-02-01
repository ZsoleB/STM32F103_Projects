/*
 * HWENCODER_Driver.h
 *
 *  Created on: 19 feb. 2018
 *      Author: Zsole
 */

#ifndef HWENCODER_DRIVER_H_
#define HWENCODER_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"
#include "TCNT_Driver.h"

#define HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1						(0x01)
#define HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_2						(0x02)
#define HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1_AND_2				(0x03)
#define HWENCODER_DRIVER_INVERTED_POLARITY_FALLING_EDGE				(0x02)
#define HWENCODER_DRIVER_NONINVERTED_POLARITY_RISING_EDGE			(0x00)
#define HWENCODER_DRIVER_NONINVERTED_POLARITY_BOTH_EDGE				(0x0A)


void HWENCODER_Driver_Init(TIM_TypeDef* TIMx);
uint32 HWENCODER_Driver_Get_Count_Value(TIM_TypeDef* TIMx);

#endif /* HWENCODER_DRIVER_H_ */
