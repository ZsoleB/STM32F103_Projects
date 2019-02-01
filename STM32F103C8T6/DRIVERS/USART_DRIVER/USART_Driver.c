/*
 * USART_Driver.c
 *
 *  Created on: 9 apr. 2018
 *      Author: Zsole
 */

#include "USART_Driver_Cfg.h"

void USART_Driver_Init()
{
	uint16 index = 0x00;

	#if (USART_DRIVER_USART1_SELECT != NOK)
		RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
	#endif

	#if (USART_DRIVER_USART2_SELECT != NOK)
		RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
	#endif

	#if (USART_DRIVER_USART3_SELECT != NOK)
		RCC->APB1ENR|=RCC_APB1ENR_USART3EN;
	#endif

	for(index = 0x00; index<USART_DRIVER_INSTANCE_NUM; index++)
	{
		USART_SETUP[index].USART_Instance->CR1 |=(USART_SETUP[index].USART_Word_length)|
														  (USART_SETUP[index].USART_Parity_control_enable)|
					                                      (USART_SETUP[index].USART_Transmitter_enable)|
														  (USART_SETUP[index].USART_Receiver_enable);

		if (USART_SETUP[index].USART_Parity_control_enable == USART_DRIVER_PARITY_CONTROLL_ENABLE)
		{
			USART_SETUP[index].USART_Instance->CR1 |=(USART_SETUP[index].USART_Parity_selection);
		}

		USART_SETUP[index].USART_Instance->CR2 |=(USART_SETUP[index].USART_Stop_bit_select);

		USART_SETUP[index].USART_Instance->CR3 |=(USART_SETUP[index].USART_Half_duplex_selection);

		USART_Driver_Set_Baudrate(index);
	}
}

void  USART_Driver_Set_Baudrate(uint8 USART_setup_nr)
{
	uint16_t MANTISA = 0;
	uint8_t  FRACTION = 0;
	uint32_t tmp = 0;

	uint32_t result = 0;

	if(USART_SETUP[USART_setup_nr].USART_Instance == USART1)
	{
		tmp = (((25*(USART_DRIVER_WORKING_FREQUENCY_2))/(USART_SETUP[USART_setup_nr].USART_Baudrate))/4);
	}
	else if((USART_SETUP[USART_setup_nr].USART_Instance == USART2)||(USART_SETUP[USART_setup_nr].USART_Instance == USART3))
	{
		tmp = (((25*(USART_DRIVER_WORKING_FREQUENCY_1))/(USART_SETUP[USART_setup_nr].USART_Baudrate))/4);
	}

	//to double precision
	MANTISA = ((tmp/100)<<4);
	//truchate the fraction, move the integer left to left space for the new fraction
	tmp = tmp - ((MANTISA>>4)*100);
	//to get the fraction shift back the last value and multiply back,
	// then save the difference got by subtracting from the old one
	FRACTION = ((((tmp*16)+50)/100)&((uint8_t)0x0F));
	//\100 with the multiplication at the begining the value had been modified, it had to be turned back
	//+50 is used for rounding up
	//Multiply with the available maximum value of the fraction part of the BRR
	result = MANTISA|FRACTION;

	USART_SETUP[USART_setup_nr].USART_Instance->BRR = result;
}

uint8 USART_Driver_Receive_Char(uint8 USART_setup_nr)
{
	uint8 Payload=0x00;
	while((USART_Driver_GetStatus(USART_setup_nr,USART_Driver_RXNE))==FAILED);
	Payload = USART_SETUP[USART_setup_nr].USART_Instance->DR;
	return Payload;
}

void USART_Driver_Send_Char(uint8 USART_setup_nr,uint8 data)
{
	USART_SETUP[USART_setup_nr].USART_Instance->DR = data;
	while((USART_Driver_GetStatus(USART_setup_nr,USART_Driver_TXE))==FAILED);
}

void USART_Driver_Send_Str(uint8 USART_setup_nr,char* Msg)
{
	uint8 index = 0x00;
	while(Msg[index])
	{
		USART_Driver_Send_Char(USART_setup_nr,Msg[index]);
		index++;
	}
}

void USART_Driver_Start(uint8 USART_setup_nr)
{
	USART_SETUP[USART_setup_nr].USART_Instance->CR1 |= USART_DRIVER_START;
}

void USART_Driver_Stop(uint8 USART_setup_nr)
{
	USART_SETUP[USART_setup_nr].USART_Instance->CR1 &= USART_DRIVER_STOP;
}

uint8 USART_Driver_GetStatus(uint8 USART_setup_nr,uint8 Status_Bit)
{
	if((USART_SETUP[USART_setup_nr].USART_Instance->SR & Status_Bit)!=FALSE)
	{
		return SUCCES;
	}
	else
	{
		return FAILED;
	}
}
