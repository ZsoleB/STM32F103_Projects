/*
 * DMA_Driver_Cfg.c
 *
 *  Created on: Aug 14, 2018
 *      Author: zsolt.balo
 *
 *	The DMA2 controller is available only in high-density and XL-density devices.
 *	ADC3, SPI/I2S3, UART4, SDIO, TIM5, TIM6, DAC, TIM7, TIM8 DMA requests
 *	are available only in high-density devices.
 *
 */

#include "DMA_Driver_Cfg.h"

void DMA_Driver_Init()
{
	uint16 index = 0x00;

	/*	Initialization of the selected DMA*/
	/*	Enable the DMA in the AHB bus*/
	RCC->AHBENR |= RCC_AHBPeriph_DMA1;

	for (index = 0x00; index < DMA_DRIVER_CHANNEL_INSTANCE_NUM; index++)
	{
		/*	Shut down the DMA before setup*/
		DMA_Driver_Stop(index);

		/* 	Wait for the EN bit to be cleared before starting any channel configuration*/
		while((DMA_SETUP[index].DMA_Channel->CCR & 0x01)!=0x00){}

		/*	DMA running Mode*/
		DMA_SETUP[index].DMA_Channel->CCR |=
				DMA_SETUP[index].DMA_Channel_running_mode;

		/*	DMA memory 2 memory mode functionality*/
		DMA_SETUP[index].DMA_Channel->CCR |=
				DMA_SETUP[index].DMA_Channel_memmory_to_memmory_mode;

		/*	DMA Channel priority*/
		DMA_SETUP[index].DMA_Channel->CCR |=
				DMA_SETUP[index].DMA_Channel_priority;

		/*	DMA Memory size*/
		DMA_SETUP[index].DMA_Channel->CCR |=
				DMA_SETUP[index].DMA_Channel_memmory_size;

		/*	DMA Peripheral size*/
		DMA_SETUP[index].DMA_Channel->CCR |=
				DMA_SETUP[index].DMA_Channel_peripheral_size;

		/*	DMA Memory increment mode*/
		DMA_SETUP[index].DMA_Channel->CCR |=
				DMA_SETUP[index].DMA_Channel_memmory_increment;

		/*	DMA Peripheral increment mode*/
		DMA_SETUP[index].DMA_Channel->CCR |=
				DMA_SETUP[index].DMA_Channel_peripheral_increment;

		/*	DMA direction*/
		DMA_SETUP[index].DMA_Channel->CCR |=
				DMA_SETUP[index].DMA_Channel_direction;

		/*	DMA Tx count*/
		DMA_SETUP[index].DMA_Channel->CNDTR = DMA_SETUP[index].DMA_Channel_tx_count;
	}
}
void DMA_Driver_SetBuffers(uint8 DMA_Channel_number, uint32* Tx_Buffer,
uint32* Rx_Buffer)
{
	if (DMA_SETUP[DMA_Channel_number].DMA_Channel_direction
			== DMA_DRIVER_DIRECTION_FROM_PERIPHERAL)
	{
		/*	DMA Peripheral address*/
		DMA1_Channel1->CPAR = (uint32_t) (Tx_Buffer);

		/*	DMA Memory address*/
		DMA1_Channel1->CMAR = (uint32_t) (Rx_Buffer);

	}
	else
	{
		/*	DMA Peripheral address*/
		DMA1_Channel1->CPAR = (uint32_t) (Rx_Buffer);

		/*	DMA Memory address*/
		DMA1_Channel1->CMAR = (uint32_t) (Tx_Buffer);
	}
}

void DMA_Driver_Start(uint8 DMA_Channel_number)
{
	/*	DMA Mode -> Enable*/
	DMA_SETUP[DMA_Channel_number].DMA_Channel->CCR |= (0x01);
}

void DMA_Driver_Stop(uint8 DMA_Channel_number)
{
	/*	Shut down the DMA 	*/
	DMA_SETUP[DMA_Channel_number].DMA_Channel->CCR &= (~(0x01));
}
