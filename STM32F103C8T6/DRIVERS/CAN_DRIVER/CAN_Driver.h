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

#define CAN_DRIVER_DEBUG_FREEZE											(0x01<<0x10)
#define CAN_DRIVER_DEBUG_SILENT_MODE									(0x01<<0x1F)
#define CAN_DRIVER_DEBUG_LOOP_BACK_MODE									(0x01<<0x1E)
/*Force a master reset of the bxCAN -> Sleep mode activated after reset (FMP bits and
 CAN_MCR register are initialized to the reset values). This bit is automatically reset to 0.
 */
#define CAN_DRIVER_RESET												(0x01<<0x0F)
#define CAN_DRIVER_INIT_REQUEST											(0x01<<0x00)
#define CAN_DRIVER_SLEEP_MODE_REQUEST									(0x01<<0x01)
#define CAN_DRIVER_INIT_ACKNOWLEDGE										(0x01<<0x00)
#define CAN_DRIVER_SLEEP_ACKNOWLEDGE									(0x01<<0x01)
#define CAN_DRIVER_TRANSMIT_MAILBOX0_EMPTY								(0x01<<0x1A)
#define CAN_DRIVER_TRANSMIT_MAILBOX1_EMPTY								(0x01<<0x1B)
#define CAN_DRIVER_TRANSMIT_MAILBOX2_EMPTY								(0x01<<0x1C)
#define CAN_DRIVER_RX_FIFO_LOCKED_MODE									(0x01<<0x03)
#define CAN_DRIVER_TIME_TRIGGERED_COMMUNICATION_MODE					(0x01<<0x07)
#define CAN_DRIVER_AUTOMATIC_BUS_OFF									(0x01<<0x06)
#define CAN_DRIVER_AUTOMATIC_WAKE_UP									(0x01<<0x05)
/*Clear the TSEG1,TSEG2,SJW=4,CAN time quanta*/
#define CAN_DRIVER_BIT_TIMING_CLEAR_MASK								(~((0x03 << 24) | (0x07 << 20) | (0x0F << 16) | (0x3FF)))
#define CAN_DRIVER_FILTER_BANK_INITIALIZATION_MODE						(0x01<<0x00)
#define CAN_DRIVER_FILTER_BANK_ACTIVE_MODE								(~(0x01<<0x00))
#define CAN_DRIVER_RELEASE_FIFO_MAILBOX									(0x01<<0x05)

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
#define CAN_DRIVER_TRANSMIT_PRIORITY_BY_ID 								(0x00<<0x02)
/*

 The transmit mailboxes can be configured as a transmit FIFO by setting the TXFP bit in the
 CAN_MCR register. In this mode the priority order is given by the transmit request order.
 This mode is very useful for segmented transmission.

 */

#define CAN_DRIVER_TRANSMIT_PRIORITY_BY_TX_REQ_ORDER 					(0x01<<0x02)

#define CAN_DRIVER_AUTOMATIC_TRANSMISSION_MODE							(0x00<<0x04)
/*

 In this mode, each transmission is started only once. If the first attempt fails, due to an
 arbitration loss or an error, the hardware will not automatically restart the message
 transmission.

 */
#define CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE						(0x01<<0x04)
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

typedef void (*CAN_Driver_Set_State)();

typedef enum
{
	CAN_DRIVER_OPERATING_MODE_INIT = 0,
	CAN_DRIVER_OPERATING_MODE_NORMAL = 1,
	CAN_DRIVER_OPERATING_MODE_SLEEP = 2,
} CAN_Driver_Operating_Modes;

typedef enum
{
	CAN_Driver_FIFO_0, CAN_Driver_FIFO_1
} CAN_Driver_FIFO_Number;

typedef enum
{
	CAN_Driver_MailBox_0, CAN_Driver_MailBox_1, CAN_Driver_MailBox_2
} CAN_Driver_MailBox_Number;

typedef struct
{
	uint32 ID; /*ID of the CAN message*/
	uint8 Payload[8]; /*Payload to be transmitted*/
	uint8 Length; /*Length of the payload*/
	uint8 Payload_Type; /*Data Frame or Remote Frame*/
	uint8 Format; /*Extended or Standard (11bit or 29bit ID)*/
} CAN_Driver_Message;

typedef struct
{
	uint8 CAN_Driver_Tx0_Ready;
	uint8 CAN_Driver_Tx1_Ready;
	uint8 CAN_Driver_Tx2_Ready;
} CAN_Driver_Tx_Status;

typedef struct
{
	uint8 CAN_Driver_Rx0_Ready;
	uint8 CAN_Driver_Rx1_Ready;
	uint8 CAN_Driver_Rx2_Ready;
} CAN_Driver_Rx_Status;

void CAN_Driver_Clear_Request_Completed_Flag(uint8 MailBox_Number);
uint8 CAN_Driver_Check_Message_Pending(uint8 FIFO_Number);
void CAN_Driver_DebugFreeze(uint8 option);
void CAN_Driver_Enter_NormalMode();
void CAN_Driver_Enter_SleepMode();
void CAN_Driver_Init();
void CAN_Driver_InitBuffer(CAN_Driver_Message *CAN_MSG);
void CAN_Driver_Enter_InitMode();
void CAN_Driver_ModeChange(CAN_Driver_Operating_Modes Mode);
void CAN_Driver_ReceiveMessage(CAN_Driver_Message *msg, uint8 MailBox_Number, uint8 FIFO_Number);
void CAN_Driver_Reset();
void CAN_Driver_Release_Rx_MailBox(uint8 FIFO_Number);
void CAN_Driver_SendMessage(CAN_Driver_Message *msg,uint8 MailBox_Number);
void CAN_Driver_SetFilter(uint32 ID);
void CAN_Driver_SetTestMode();
void CAN_Driver_SetBuffer(CAN_Driver_Message* arg, uint8 len, uint8* message);
void CAN_Driver_Start();
void CAN_Driver_Wait_for_Ready();

#endif /* DRIVERS_CAN_DRIVER_CAN_DRIVER_H_ */
