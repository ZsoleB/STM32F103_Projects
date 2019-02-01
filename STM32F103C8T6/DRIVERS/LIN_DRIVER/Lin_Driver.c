/*
 * Lin_Driver.c
 *
 *  Created on: Oct 23, 2018
 *      Author: zsolt.balo
 */

#include "Lin_Driver_Cfg.h"

void LIN_Driver_Init()
{
	uint8 index = 0x00;

	LIN_Driver_Init_Cfg();
	USART_Driver_Init();

	for(index=0x00;index<LIN_DRIVER_INSTANCE_NUM;index++)
	{
		LIN_SETUP[index].USART_Setup_Instance[LIN_SETUP[index].USART_Instance_number].USART_Instance->CR2|= (LIN_DRIVER_ENABLE);
		LIN_SETUP[index].USART_Setup_Instance[LIN_SETUP[index].USART_Instance_number].USART_Instance->CR2|= (LIN_DRIVER_LIN_BREAK_DETECTION_LENGTH);
	}
}

void LIN_Driver_Start(uint8 LIN_setup_nr)
{
	USART_Driver_Start(LIN_SETUP[LIN_setup_nr].USART_Instance_number);
}

void LIN_Driver_SendBreak(uint8 LIN_setup_nr)
{
	LIN_SETUP[LIN_setup_nr].USART_Setup_Instance[LIN_SETUP[LIN_setup_nr].USART_Instance_number].USART_Instance->CR1|= (LIN_DRIVER_SEND_BREAK);
}

void LIN_Driver_SendID(uint8 LIN_setup_nr,uint8 LIN_id)
{
	LIN_Driver_PID_Field_Type PID={0x00,0x00};
	uint8 Final_PID = 0x00;

	PID.Lin_frame_id 	  = LIN_id;
	PID.Lin_frame_parity = LIN_Driver_PID_Calculator(PID.Lin_frame_id);
	Final_PID = (uint8_t)(((PID.Lin_frame_parity)<<6)|(PID.Lin_frame_id));

	LIN_Driver_SendBreak(LIN_setup_nr);
	SYSTICK_Driver_Delay_ms(4);
	USART_Driver_Send_Char(LIN_SETUP[LIN_setup_nr].USART_Instance_number,LIN_DRIVER_SYNC_FIELD);
	SYSTICK_Driver_Delay_ms(4);
	USART_Driver_Send_Char(LIN_SETUP[LIN_setup_nr].USART_Instance_number,Final_PID);
	SYSTICK_Driver_Delay_ms(4);
}

void LIN_Driver_SendData(uint8 LIN_setup_nr,uint8 LIN_data)
{
	USART_Driver_Send_Char(LIN_SETUP[LIN_setup_nr].USART_Instance_number,LIN_data);
}

uint8_t LIN_Driver_PID_Calculator(uint8_t data)
{
	uint8_t parity_bit_even = 0x00;
	uint8_t parity_bit_odd = 0x00;
	uint8_t result = 0x00;

	parity_bit_even = ((data ^ (data>>1))^((data>>2)^(data>>4)));
	parity_bit_odd = (~(((data>>1) ^ (data>>3))^((data>>4)^(data>>5))));
	result = (parity_bit_odd<<1)|(parity_bit_even);

	return result;
}
