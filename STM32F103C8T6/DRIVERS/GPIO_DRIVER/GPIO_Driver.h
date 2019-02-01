/*
 * GPIO_Driver.h
 *
 *  Created on: Jan 10, 2018
 *      Author: zsolt.balo
 */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "stm32f10x.h"
#include "StdTypes.h"

#define GPIO_DRIVER_INPUT_MODE 								((uint32)0x0000)
#define GPIO_DRIVER_OUTPUT_MODE_10MHZ 						((uint32)0x0001)
#define GPIO_DRIVER_OUTPUT_MODE_2MHZ 						((uint32)0x0002)
#define GPIO_DRIVER_OUTPUT_MODE_50MHZ 						((uint32)0x0003)
#define GPIO_DRIVER_ANALOG_INPUT 							((uint32)0x0000)
#define GPIO_DRIVER_FLOATING_INPUT 							((uint32)0x0001)
#define GPIO_DRIVER_PU_PD_INPUT 							((uint32)0x0002)
#define GPIO_DRIVER_GP_OUTPUT_PP 							((uint32)0x0000)
#define GPIO_DRIVER_GP_OUTPUT_OD 							((uint32)0x0001)
#define GPIO_DRIVER_AF_OUTPUT_PP 							((uint32)0x0002)
#define GPIO_DRIVER_AF_OUTPUT_OD 							((uint32)0x0003)

typedef struct
{
	GPIO_TypeDef* GPIO_Port;
	uint16 GPIO_Pin_nr;
	uint16 GPIO_Pins[16];
	uint16 GPIO_Pin_Mode[16];
	uint16 GPIO_Pin_Cfg[16];
}GPIO_Driver_Setup_Type;

extern GPIO_Driver_Setup_Type* GPIO_SETUP;

void GPIO_Driver_Init();
void GPIO_Driver_SetPin(uint8 GPIO_setup_nr,uint16 Pin);
void GPIO_Driver_ClearPin(uint8 GPIO_setup_nr,uint16 Pin);
uint16 GPIO_Driver_ReadInputData(uint8 GPIO_setup_nr);
uint16 GPIO_Driver_ReadOutputData(uint8 GPIO_setup_nr);
uint8 GPIO_Driver_ReadInputDataBit(uint8 GPIO_setup_nr,uint16 Bit_number);
void GPIO_Driver_Lambda_function();

#endif /* GPIO_DRIVER_H_ */

