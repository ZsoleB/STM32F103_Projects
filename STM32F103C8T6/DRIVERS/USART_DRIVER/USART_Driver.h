/*
 * USART_Driver.h
 *
 *  Created on: 9 apr. 2018
 *      Author: Zsole
 */

#ifndef DRIVERS_USART_DRIVER_USART_DRIVER_H_
#define DRIVERS_USART_DRIVER_USART_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"

/*Clear to send flag*/
#define USART_Driver_CTS									0x200
/*LIN break direction flag*/
#define USART_Driver_LBD									0x100
/*Transmit data register empty flag*/
#define USART_Driver_TXE									0x080
/*Transmission complete flag*/
#define USART_Driver_TC										0x040
/*Read data register not empty*/
#define USART_Driver_RXNE									0x020
/*Idle line detected flag*/
#define USART_Driver_IDLE									0x010
/*Overrun error flag*/
#define USART_Driver_ORE									0x008
/*Noise detected flag*/
#define USART_Driver_NF										0x004
/*Framing error flag*/
#define USART_Driver_FE										0x002
/*Parity error flag*/
#define USART_Driver_PE 									0x001

#define USART_DRIVER_8_DATA_BITS							((uint32)(0x00<<0x0C))
#define USART_DRIVER_9_DATA_BITS							((uint32)(0x01<<0x0C))

#define USART_DRIVER_PARITY_CONTROLL_ENABLE					((uint32)(0x01<<0x0A))
#define USART_DRIVER_PARITY_CONTROLL_DISABLE				((uint32)(0x00<<0x0A))
#define USART_DRIVER_EVEN_PARITY							((uint32)(0x00<<0x09))
#define USART_DRIVER_ODD_PARITY								((uint32)(0x01<<0x09))

#define USART_DRIVER_1_STOP_BIT							 	((uint32)(0x00<<0x0C))

/*UART4 and UART 5 doesn't implement these options*/
#if(((USART_DRIVER_USART5_SELECT == NOK) && (USART_DRIVER_USART4_SELECT == NOK))==OK)
#define USART_DRIVER_0_5_STOP_BIT							((uint32)(0x01<<0x0C))
#endif

#define USART_DRIVER_2_STOP_BIT								((uint32)(0x10<<0x0C))

/*UART4 and UART 5 doesn't implement these options*/
#if(((USART_DRIVER_USART5_SELECT == NOK) && (USART_DRIVER_USART4_SELECT == NOK))==OK)
#define USART_DRIVER_1_5_STOP_BIT							((uint32)(0x11<<0x0C))
#endif

#define USART_DRIVER_HALF_DUPLEX_ENABLE						((uint32)(0x01<<0x03))
#define USART_DRIVER_HALF_DUPLEX_DISABLE					((uint32)(0x00<<0x03))
#define USART_DRIVER_TX_ENABLE								((uint32)(0x01<<0x03))
#define USART_DRIVER_TX_DISABLE								((uint32)(0x00<<0x03))
#define USART_DRIVER_RX_ENABLE								((uint32)(0x01<<0x02))
#define USART_DRIVER_RX_DISABLE								((uint32)(0x00<<0x02))

#define USART_DRIVER_START									((uint32)(0x01<<0x0D))
#define USART_DRIVER_STOP									(~((uint32)(0x01<<0x0D)))

typedef struct
{
	USART_TypeDef* USART_Instance;
	uint16 USART_Baudrate;
	uint16 USART_Word_length;
	uint16 USART_Parity_control_enable;
	uint16 USART_Parity_selection;
	uint16 USART_Transmitter_enable;
	uint16 USART_Receiver_enable;
	uint16 USART_Stop_bit_select;
	uint16 USART_Half_duplex_selection;
}USART_Driver_Setup_Type;

extern USART_Driver_Setup_Type* USART_SETUP;

void USART_Driver_Init();
void USART_Driver_Set_Baudrate(uint8 USART_setup_nr);
uint8 USART_Driver_Receive_Char(uint8 USART_setup_nr);
void USART_Driver_Send_Char(uint8 USART_setup_nr,uint8 data);
void USART_Driver_Send_Str(uint8 USART_setup_nr,char* Msg);
void USART_Driver_Start(uint8 USART_setup_nr);
void USART_Driver_Stop(uint8 USART_setup_nr);
uint8 USART_Driver_GetStatus(uint8 USART_setup_nr,uint8 Status_Bit);

#endif /* DRIVERS_USART_DRIVER_USART_DRIVER_H_ */
