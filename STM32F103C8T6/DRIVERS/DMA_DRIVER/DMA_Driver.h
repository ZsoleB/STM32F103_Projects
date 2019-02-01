/*
 * DMA_Driver.h
 *
 *  Created on: Aug 14, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_DMA_DRIVER_DMA_DRIVER_H_
#define DRIVERS_DMA_DRIVER_DMA_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"

#define DMA1_DRIVER_CHANNEL_1									DMA1_Channel1
#define DMA1_DRIVER_CHANNEL_2									DMA1_Channel2
#define DMA1_DRIVER_CHANNEL_3									DMA1_Channel3
#define DMA1_DRIVER_CHANNEL_4									DMA1_Channel4
#define DMA1_DRIVER_CHANNEL_5									DMA1_Channel5
#define DMA1_DRIVER_CHANNEL_6									DMA1_Channel6
#define DMA1_DRIVER_CHANNEL_7									DMA1_Channel7
#define DMA_DRIVER_NORMAL_MODE									(0x00<<5)
#define DMA_DRIVER_CIRCULAR_MODE								(0x01<<5)
#define DMA_DRIVER_CHANNEL_PRIORITY_LOW							(0x00<<0x0C)
#define DMA_DRIVER_CHANNEL_PRIORITY_MEDIUM						(0x01<<0x0C)
#define DMA_DRIVER_CHANNEL_PRIORITY_HIGH						(0x02<<0x0C)
#define DMA_DRIVER_CHANNEL_PRIORITY_VERY_HIGH					(0x03<<0x0C)
#define DMA_DRIVER_MEMMORY_SIZE_8_BITS							(0x00<<0x0A)
#define DMA_DRIVER_MEMMORY_SIZE_16_BITS                         (0x01<<0x0A)
#define DMA_DRIVER_MEMMORY_SIZE_32_BITS                         (0x02<<0x0A)
#define DMA_DRIVER_MEMMORY_TO_MEMMORY_ENABLE                    (0x01<<0x0E)
#define DMA_DRIVER_MEMMORY_TO_MEMMORY_DISABLE                   (0x00<<0x0E)
#define DMA_DRIVER_PERIPHERAL_SIZE_8_BITS                       (0x00<<0x08)
#define DMA_DRIVER_PERIPHERAL_SIZE_16_BITS                      (0x01<<0x08)
#define DMA_DRIVER_PERIPHERAL_SIZE_32_BITS                      (0x02<<0x08)
#define DMA_DRIVER_DIRECTION_FROM_PERIPHERAL					(0x00<<4)
#define DMA_DRIVER_DIRECTION_FROM_MEMORY                        (0x01<<4)
#define DMA_DRIVER_MEMMORY_INCREMENT_ENABLE						(0x01<<0x07)
#define DMA_DRIVER_MEMMORY_INCREMENT_DISABLE					(0x00<<0x07)
#define DMA_DRIVER_PERIPHERAL_INCREMENT_ENABLE					(0x01<<0x06)
#define DMA_DRIVER_PERIPHERAL_INCREMENT_DISABLE					(0x00<<0x06)

typedef struct
{
	DMA_Channel_TypeDef* DMA_Channel;
	uint16 DMA_Channel_running_mode;
	uint16 DMA_Channel_memmory_to_memmory_mode;
	uint16 DMA_Channel_priority;
	uint16 DMA_Channel_memmory_size;
	uint16 DMA_Channel_peripheral_size;
	uint16 DMA_Channel_memmory_increment;
	uint16 DMA_Channel_peripheral_increment;
	uint16 DMA_Channel_direction;
	uint16 DMA_Channel_tx_count;
}DMA_Driver_Setup_Type;

extern DMA_Driver_Setup_Type* DMA_SETUP;

void DMA_Driver_Init();
void DMA_Driver_SetBuffers(uint8 DMA_Channel_number,uint32* Tx_Buffer,uint32* Rx_Buffer);
void DMA_Driver_Start(uint8 DMA_Channel_number);
void DMA_Driver_Stop(uint8 DMA_Channel_number);

#endif /* DRIVERS_DMA_DRIVER_DMA_DRIVER_H_ */
