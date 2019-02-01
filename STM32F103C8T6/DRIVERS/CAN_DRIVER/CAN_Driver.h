/*
 * CAN_Driver.h
 *
 *  Created on: Apr 19, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_CAN_DRIVER_CAN_DRIVER_H_
#define DRIVERS_CAN_DRIVER_CAN_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"

/*11bit ID*/
#define CAN_DRIVER_ID_STANDARD 											0x00
/*29bit ID*/
#define CAN_DRIVER_ID_EXTENDED 											0x01
#define CAN_DRIVER_DATA_FRAME 											0x00
#define CAN_DRIVER_REMOTE_FRAME 										0x01

/*

	When more than one transmit mailbox is pending, the transmission order is given by the
identifier of the message stored in the mailbox. The message with the lowest identifier value
has the highest priority according to the arbitration of the CAN protocol. If the identifier
values are equal, the lower mailbox number will be scheduled first.

*/
#define CAN_DRIVER_TRANSMIT_PRIORITY_BY_ID 								0x00
/*

	The transmit mailboxes can be configured as a transmit FIFO by setting the TXFP bit in the
CAN_MCR register. In this mode the priority order is given by the transmit request order.
This mode is very useful for segmented transmission.

 */

#define CAN_DRIVER_TRANSMIT_PRIORITY_BY_TX_REQ_ORDER 					0x01

#define CAN_DRIVER_AUTOMATIC_TRANSMISSION_MODE							0x00
/*

	In this mode, each transmission is started only once. If the first attempt fails, due to an
arbitration loss or an error, the hardware will not automatically restart the message
transmission.

*/
#define CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE						0x01
/*

	In mask mode the identifier registers are associated with mask registers specifying which
bits of the identifier are handled as “must match” or as “don’t care”. Can be used when frame
groups are used not single frames.

 */
#define CAN_DRIVER_FILTER_MASK_MODE										0x00
/*

	In identifier list mode, the mask registers are used as identifier registers. Thus instead of
defining an identifier and a mask, two identifiers are specified, doubling the number of single
identifiers. All bits of the incoming identifier must match the bits specified in the filter
registers.

 */
#define CAN_DRIVER_FILTER_ID_LIST_MODE											0x01
#define CAN_DRIVER_FILTER_SCALE_16_BIT											0x00
#define CAN_DRIVER_FILTER_SCALE_32_BIT											0x01


typedef void(*CAN_Driver_Set_State)(CAN_TypeDef *CANx);

typedef enum
{
	CAN_DRIVER_OPERATING_MODE_INIT   = 0,
	CAN_DRIVER_OPERATING_MODE_NORMAL = 1,
	CAN_DRIVER_OPERATING_MODE_SLEEP  = 2,
}CAN_Driver_Operating_Modes;

typedef struct
{
	uint32 ID;			  /*ID of the CAN message*/
	uint8  Payload[8]; 	  /*Payload to be transmitted*/
	uint8 Length;         /*Length of the payload*/
	uint8 Payload_Type;	  /*Data Frame or Remote Frame*/
	uint8 Format;		  /*Extended or Standard (11bit or 29bit ID)*/
}CAN_Driver_Message;

typedef struct
{
	uint8 CAN_Driver_Tx0_Ready;
	uint8 CAN_Driver_Tx1_Ready;
	uint8 CAN_Driver_Tx2_Ready;
}CAN_Driver_Tx_Status;

typedef struct
{
	uint8 CAN_Driver_Rx0_Ready;
	uint8 CAN_Driver_Rx1_Ready;
	uint8 CAN_Driver_Rx2_Ready;
}CAN_Driver_Rx_Status;

void CAN_Driver_DebugFreeze(CAN_TypeDef *CANx);
void CAN_Driver_Enter_NormalMode(CAN_TypeDef *CANx);
void CAN_Driver_Enter_SleepMode(CAN_TypeDef *CANx);
void CAN_Driver_Init(CAN_TypeDef *CANx);
void CAN_Driver_InitTxPayload(CAN_Driver_Message *CAN_MSG);
void CAN_Driver_Enter_InitMode(CAN_TypeDef *CANx);
void CAN_Driver_ModeChange(CAN_TypeDef *CANx,CAN_Driver_Operating_Modes Mode);
void CAN_Driver_ReceiveMessage(CAN_TypeDef *CANx,CAN_Driver_Message *msg);
void CAN_Driver_Reset(CAN_TypeDef *CANx);
void CAN_Driver_SendMessage(CAN_TypeDef *CANx,CAN_Driver_Message *msg);
void CAN_Driver_SetFilter(CAN_TypeDef *CANx,uint32 ID);
void CAN_Driver_SetTestMode(CAN_TypeDef *CANx);
void CAN_Driver_Start(CAN_TypeDef *CANx);
void CAN_Driver_Wait_for_Ready (CAN_TypeDef *CANx);

#endif /* DRIVERS_CAN_DRIVER_CAN_DRIVER_H_ */
