/*
 * SPI_Driver.c
 *
 *  Created on: May 7, 2018
 *      Author: zsolt.balo
 */

#include "SPI_Driver_Cfg.h"

	uint16 payload=0x00;
	uint16 status=0x00;

void SPI_Driver_Init()
{
	uint16 index = 0x00;

	#if(SPI_DRIVER_SPI1 == OK)
		RCC->APB2ENR|=RCC_APB2ENR_SPI1EN;
	#endif

	#if(SPI_DRIVER_SPI2 == OK)
		RCC->APB1ENR|=RCC_APB1ENR_SPI2EN;
	#endif

	for(index=0x00;index<SPI_DRIVER_INSTANCE_NUM;index++)
	{

		SPI_SETUP[index].SPI_Instance->CR1 |=(SPI_SETUP[index].SPI_Driver_bidirectional_data_mode_enable)
										   |(SPI_SETUP[index].SPI_Driver_output_enable_in_bidirectional_mode);

		if (SPI_SETUP[index].SPI_Driver_crc_calculation_enable == OK)
		{
			SPI_SETUP[index].SPI_Instance->CR1|=(SPI_DRIVER_CRC_CALCULATION_ENABLE);
		}

		SPI_SETUP[index].SPI_Instance->CR1|=(SPI_SETUP[index].SPI_Driver_data_frame_format)
										  |(SPI_SETUP[index].SPI_Driver_receive_only_or_full_duplex);

		if (SPI_SETUP[index].SPI_Driver_software_slave_management == OK)
		{
			SPI_SETUP[index].SPI_Instance->CR1|=SPI_DRIVER_SOFTWARE_SLAVE_MANAGEMENT_CONFIG;
		}

		if (SPI_SETUP[index].SPI_Driver_inetrnal_slave_select == OK)
		{
			SPI_SETUP[index].SPI_Instance->CR1|=SPI_DRIVER_INTERNAL_SLAVE_SELECT_CONFIG;
		}

		SPI_SETUP[index].SPI_Instance->CR1|=(SPI_SETUP[index].SPI_Driver_frame_direction)
										   |(SPI_SETUP[index].SPI_Driver_baud_rate_control)
										   |(SPI_SETUP[index].SPI_Driver_master_slave_selection)
										   |(SPI_SETUP[index].SPI_Driver_clock_polarity)
				 						   |(SPI_SETUP[index].SPI_Driver_clock_phase);

		if (SPI_SETUP[index].SPI_Driver_ss_output_enable == OK)
		{
			SPI_SETUP[index].SPI_Instance->CR2|=SPI_DRIVER_SS_OUTPUT_ENABLE_CONFIG;
		}
		SPI_Driver_Start(index);
	}
}

void SPI_Driver_Start(uint8 SPI_setup_nr)
{
	SPI_SETUP[SPI_setup_nr].SPI_Instance->CR1|=(SPI_DRIVER_PERIPHERAL_ENABLE);
}

void SPI_Driver_Stop(uint8 SPI_setup_nr)
{
	SPI_SETUP[SPI_setup_nr].SPI_Instance->CR1 &=(SPI_DRIVER_PERIPHERAL_DISABLE);
}

uint8 SPI_Driver_Get_Status(uint8 SPI_setup_nr,uint16 StatusCode)
{
	if((SPI_SETUP[SPI_setup_nr].SPI_Instance->SR & StatusCode)!=FALSE)
	{
		return SUCCES;
	}
	else
	{
		return FAILED;
	}
}

uint16 SPI_Driver_Send_Data(uint8 SPI_setup_nr,uint16 data)
{
	while(SPI_Driver_Get_Status(SPI_setup_nr,SPI_DRIVER_TRANSMIT_BUFFER_EMPTY)!=SUCCES){}
		SPI_SETUP[SPI_setup_nr].SPI_Instance->DR = data;
	while(SPI_Driver_Get_Status(SPI_setup_nr,SPI_DRIVER_BUSY_FLAG)!=FAILED){}

	return SPI_SETUP[SPI_setup_nr].SPI_Instance->DR;
}

uint16 SPI_Driver_Transcieve_Data(uint8 SPI_setup_nr,uint16 data)
{
	uint16_t payload=0x00;
	SPI_Driver_Set_Slave_Select_Low(SPI_setup_nr);
	payload = SPI_Driver_Send_Data(SPI_setup_nr,data);
	SPI_Driver_Set_Slave_Select_High(SPI_setup_nr);
	return payload;
}

void SPI_Driver_Set_Slave_Select_Low(uint8 SPI_setup_nr)
{
	GPIO_Driver_ClearPin(SPI_SETUP[SPI_setup_nr].SPI_Driver_slave_select_port,SPI_SETUP[SPI_setup_nr].SPI_Driver_slave_select_pin);
}

void SPI_Driver_Set_Slave_Select_High(uint8 SPI_setup_nr)
{
	GPIO_Driver_SetPin(SPI_SETUP[SPI_setup_nr].SPI_Driver_slave_select_port,SPI_SETUP[SPI_setup_nr].SPI_Driver_slave_select_pin);
}
