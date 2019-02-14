/*
 * EXTI_Driver.h
 *
 *  Created on: Feb 6, 2018
 *      Author: zsolt.balo
 */

#ifndef EXTI_DRIVER_H_
#define EXTI_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"
#include "NVIC_Driver.h"

/*Pin will register in the interrupt mask register.
 When the correct conditions are met, the PR will be set and the
 ISR will be called. The PR must be cleared by writing 1 to it.*/
#define EXTI_DRIVER_INTERRUPT_ACTION							0x00

/*Pin will register in the interrupt mask register.
 When the correct conditions are met, an event will be sent but,
 the PR will not be set and the ISR will not be called.*/
#define EXTI_DRIVER_EVENT_ACTION								0x01

#define EXTI_DRIVER_INTERRUPT_PIN_0						        0x00
#define EXTI_DRIVER_INTERRUPT_PIN_1 					        0x01
#define EXTI_DRIVER_INTERRUPT_PIN_2 					        0x02
#define EXTI_DRIVER_INTERRUPT_PIN_3                             0x03
#define EXTI_DRIVER_INTERRUPT_PIN_4 					        0x04
#define EXTI_DRIVER_INTERRUPT_PIN_5                             0x05
#define EXTI_DRIVER_INTERRUPT_PIN_6                             0x06
#define EXTI_DRIVER_INTERRUPT_PIN_7                             0x07
#define EXTI_DRIVER_INTERRUPT_PIN_8                             0x08
#define EXTI_DRIVER_INTERRUPT_PIN_9                             0x09
#define EXTI_DRIVER_INTERRUPT_PIN_10                            0x0A
#define EXTI_DRIVER_INTERRUPT_PIN_11                            0x0B
#define EXTI_DRIVER_INTERRUPT_PIN_12                            0x0C
#define EXTI_DRIVER_INTERRUPT_PIN_13                            0x0D
#define EXTI_DRIVER_INTERRUPT_PIN_14                            0x0E
#define EXTI_DRIVER_INTERRUPT_PIN_15                            0x0F
#define EXTI_DRIVER_INTERRUPT_PORT_A					((uint8)0x00)
#define EXTI_DRIVER_INTERRUPT_PORT_B 					((uint8)0x01)
#define EXTI_DRIVER_INTERRUPT_PORT_C 					((uint8)0x02)
#define EXTI_DRIVER_INTERRUPT_PORT_D                    ((uint8)0x03)
#define EXTI_DRIVER_INTERRUPT_PORT_E 					((uint8)0x04)
#define EXTI_DRIVER_INTERRUPT_PORT_F                    ((uint8)0x05)
#define EXTI_DRIVER_INTERRUPT_PORT_G                    ((uint8)0x06)

void EXTI_Driver_Init(uint8 InterruptPinNumber,uint8 InterruptPortNumber,uint8 Action_Section);
void EXTI_Driver_Generate_SWInterrupt(uint8 InterruptNumber);
void EXTI_Driver_Clear_PendingInterrupt(uint8 InterruptNumber);
void EXTI_Driver_Rising_Trigger_Select(uint8 InterruptNumber);
void EXTI_Driver_Rising_Trigger_Clear(uint8 InterruptNumber);
void EXTI_Driver_Falling_Trigger_Select(uint8 InterruptNumber);
void EXTI_Driver_Falling_Trigger_Clear(uint8 InterruptNumber);

#endif /* EXTI_DRIVER_H_ */
