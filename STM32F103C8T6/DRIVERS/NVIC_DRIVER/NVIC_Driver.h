/*
 * NVIC_Driver.h
 *
 *  Created on: Apr 20, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_NVIC_DRIVER_NVIC_DRIVER_H_
#define DRIVERS_NVIC_DRIVER_NVIC_DRIVER_H_


#include "stm32f10x.h"
#include "StdTypes.h"

#define NVIC_DRIVER_AIRCR_VECTORKEY_CLEAR_MASK				((uint32)0xFFFF0000)
#define NVIC_DRIVER_AIRCR_VECTORKEY_MASK					((uint32)0x05FA0000)
#define NVIC_DRIVER_PRIORITY_GROUP_MASK						0x700

/*
 * The priority group configuration, can be interpreted the following way
 *
 * x- Group priority
 * y- Sub priority
 *
 * These are used by the NVIC, in the IPRx registers.
 * Only the 4 most significant bits are used, thats why, they are presented in the form of:
 * xxxx.0000
 * */

/*xxxx.0000*/
#define NVIC_DRIVER_PRIORITY_GRUP_4						((uint8)0x03)
/*xxxy.0000*/
#define NVIC_DRIVER_PRIORITY_GRUP_3						((uint8)0x04)
/*xxyy.0000*/
#define NVIC_DRIVER_PRIORITY_GRUP_2						((uint8)0x05)
/*xyyy.0000*/
#define NVIC_DRIVER_PRIORITY_GRUP_1						((uint8)0x06)
/*yyyy.0000*/
#define NVIC_DRIVER_PRIORITY_GRUP_0						((uint8)0x07)

void NVIC_Driver_SetInterrupt(IRQn_Type IRQChannel,uint8 Preemption_Priority,uint8 Sub_Priority);
void NVIC_Driver_ClearInterrupt(uint8 IRQChannel);
void NVIC_Driver_PriorityGroupConfig(uint8 Prioritygroup);

/*Driver Specific functions*/

void NVIC_Driver_SetTimer_Update_Interrupt(uint8 Preemption_priority,uint8 Sub_priority);
void NVIC_Driver_Set_EXTI_Interrupt(uint8 Preemption_priority,uint8 Sub_priority);
void NVIC_Driver_Set_SYSTICK_Interrupt(uint8 Preemption_priority,uint8 Sub_priority);
void NVIC_Driver_Set_RTC_Interrupt(uint8 Preemption_priority,uint8 Sub_priority);
void NVIC_Driver_Set_WWDT_Interrupt(uint8 Preemption_priority,uint8 Sub_priority);

#endif /* DRIVERS_NVIC_DRIVER_NVIC_DRIVER_H_ */
