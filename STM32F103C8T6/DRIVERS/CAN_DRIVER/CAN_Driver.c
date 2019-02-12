/*
 * CAN_Driver.c
 *
 *  Created on: Apr 19, 2018
 *      Author: zsolt.balo
 *
 *
 * Bit Timing for can
 ____________________________________________________________________________________________________
 |            |                                          |                                            |
 |Sync_Segment|       BIT segment1                       |           BIT segment2                     |
 |    	   	 |       			                        |                 			                 |
 ----------------------------------------------------------------------------------------------------
 1xtq				TBS1										TBS2
 ^									                      		 ^
 |                                            |
 Sample point                               Transmit Point

 1
 BaudRate = ------------------
 NominalBitTime

 NominalBitTime = 1 x tq + tBS1 + tBS2

 with:

 tBS1 = tq x (TS1[3:0] + 1),
 tBS2 = tq x (TS2[2:0] + 1),
 tq = (BRP[9:0] + 1) x tPCLK

 where tq refers to the Time quantum

 tPCLK = time period of the APB clock,

 */
#include "CAN_Driver_Cfg.h"

//CAN_Driver_Tx_Status* CAN_Driver_Tx_global_status = {0x00};
//CAN_Driver_Rx_Status* CAN_Driver_Rx_global_status = {0x00};

static CAN_Driver_Set_State CAN_Driver_StateSetters[] = {
		CAN_Driver_Enter_InitMode, CAN_Driver_Enter_NormalMode,
		CAN_Driver_Enter_SleepMode };

void CAN_Driver_DebugFreeze(uint8 option)
{
	if (option == NOK)
	{
		CAN1->MCR &= (~CAN_DRIVER_DEBUG_FREEZE);
	}
	else if (option == OK)
	{
		CAN1->MCR |= CAN_DRIVER_DEBUG_FREEZE;
	}
	else
	{
		/*Nothing to do*/
	}

}

void CAN_Driver_Enter_NormalMode()
{
	/*Exit from Initialization mode, and enter normal mode*/
	CAN1->MCR &= (~CAN_DRIVER_INIT_REQUEST);

	/*Wait until change confirmed, 11 recessive bits are detected and the line is idle*/
	while (!(CAN1->MSR & CAN_DRIVER_INIT_ACKNOWLEDGE) != 0x00)
	{
	}
}

void CAN_Driver_Enter_SleepMode()
{
	/*Exit from Initialization mode*/
	CAN1->MCR &= (~CAN_DRIVER_INIT_REQUEST);

	/*Enter into Sleep mode*/
	CAN1->MCR |= CAN_DRIVER_SLEEP_MODE_REQUEST;

	/*Wait until change confirmed*/
	while (!((CAN1->MSR & CAN_DRIVER_SLEEP_ACKNOWLEDGE) != 0x00)
			&& ((CAN1->MSR & CAN_DRIVER_INIT_ACKNOWLEDGE) == 0x00))
	{
	}
}

void CAN_Driver_Init()
{

	/*STM32F103C8 has only one can peripheral, so only CAN1 will be used */
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

	/*Enter into initialization mode.
	 Erroneous access to certain configuration registers can cause the hardware to temporarily
	 disturb the whole CAN network. Therefore the CAN_BTR register can be modified by
	 software only while the CAN hardware is in initialization mode.

	 */
	CAN_Driver_ModeChange(CAN_DRIVER_OPERATING_MODE_INIT);

	/*Set up the CAN option registers*/
#if(CAN_DRIVER_RUN_ON_DEBUG_MODE == OK)
	/*Can-debug configuration*/
	CAN_Driver_DebugFreeze(NOK);
#elif(CAN_DRIVER_RUN_ON_DEBUG_MODE == NOK)
	CAN_Driver_DebugFreeze(OK);
#endif

	/*Can Transmit priority*/
#if(CAN_DRIVER_TRANSMIT_PRIORITY == CAN_DRIVER_TRANSMIT_PRIORITY_BY_ID)
	CAN1->MCR |= CAN_DRIVER_TRANSMIT_PRIORITY_BY_ID;
#elif(CAN_DRIVER_TRANSMIT_PRIORITY == CAN_DRIVER_TRANSMIT_PRIORITY_BY_TX_REQ_ORDER)
	CAN1->MCR |= CAN_DRIVER_TRANSMIT_PRIORITY_BY_TX_REQ_ORDER;
#endif

	/*Can Transmission mode*/
#if(CAN_DRIVER_TRANSMISSION_MODE == CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE)
	CAN1->MCR |= CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE;
#elif(CAN_DRIVER_TRANSMIT_PRIORITY == CAN_DRIVER_AUTOMATIC_TRANSMISSION_MODE)
	CAN1->MCR |= CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE;
#endif

	/*Can Rx overwrite or retain the old values*/
#if(CAN_DRIVER_RX_OVERWRITE_ENABLE == OK)
	/*Receive FIFO not locked on overrun. Once a receive FIFO is full the next incoming
	 message will overwrite the previous one */
	CAN1->MCR &= (~CAN_DRIVER_RX_FIFO_LOCKED_MODE);
#else
	/*Receive FIFO locked against overrun. Once a receive FIFO is full the next incoming
	 message will be discarded */
	CAN1->MCR |= CAN_DRIVER_RX_FIFO_LOCKED_MODE;
#endif

	/*Can Time-Triggered transmission*/
#if(CAN_DRIVER_TIME_TRIGGERED_TRANSMISSION == OK)
	CAN1->MCR |= CAN_DRIVER_TIME_TRIGGERED_COMMUNICATION_MODE;
#else
	CAN1->MCR &= (~CAN_DRIVER_TIME_TRIGGERED_COMMUNICATION_MODE);
#endif

	/*Can auto bus off management*/
#if(CAN_DRIVER_AUTOMATIC_BUS_OFF_MANAGEMENT == OK)
	CAN1->MCR |= CAN_DRIVER_AUTOMATIC_BUS_OFF;
#else
	CAN1->MCR &= (~CAN_DRIVER_AUTOMATIC_BUS_OFF);
#endif

	/*Can automatic wake-up mode*/
#if(CAN_DRIVER_AUTOMATIC_WAKE_UP_MODE == OK)
	/*The Bus-Off state is left automatically by hardware once 128 occurrences of 11 recessive
	 bits have been monitored. */
	CAN1->MCR |= CAN_DRIVER_AUTOMATIC_WAKE_UP;
#else
	/*The Bus-Off state is left on software request, once 128 occurrences of 11 recessive bits
	 have been monitored and the software has first set and cleared the INRQ bit of the
	 CAN_MCR register.  */
	CAN1->MCR &= (~CAN_DRIVER_AUTOMATIC_WAKE_UP);
#endif

	/*Set up the CAN bit timing registers*/
	CAN1->BTR &= CAN_DRIVER_BIT_TIMING_CLEAR_MASK;
	/*set TSEG1*/
	CAN1->BTR |= ((((CAN_DRIVER_BIT_SEGMENT1 - 1) & 0x0F) << 16));
	/*set TSEG2*/
	CAN1->BTR |= ((((CAN_DRIVER_BIT_SEGMENT2 - 1) & 0x07) << 20));
	/*set SJW*/
	CAN1->BTR |=
			((((CAN_DRIVER_RESYNCHRONIZATION_JUMP_WIDTH - 1) & 0x03) << 24));
	/*set CAN pescaler*/
	CAN1->BTR |= (((CAN_BAUD_RATE_PRESCALER - 1) & 0x3FF));

	/*Set up additional functionalities, ex. TestModes*/
#if (CAN_DRIVER_TEST_MODE_ENABLE == OK)
	CAN_Driver_SetTestMode();
#endif
}

void CAN_Driver_InitBuffer(CAN_Driver_Message *CAN_MSG)
{
	uint8_t index = 0x00;

	for (index = 0x00; index < 8; index++)
	{
		CAN_MSG->Payload[index] = 0x00;
	}
}

void CAN_Driver_SetBuffer(CAN_Driver_Message* arg, uint8 len, uint8* message)
{
   uint8_t ind = 0x00;
   arg->Length = len;

   for(ind=0x00;ind<len;ind++)
   {
      arg->Payload[ind] = message[ind];
   }
}

void CAN_Driver_Enter_InitMode()
{
	/*Exit from Sleep mode*/
	CAN1->MCR &= (~CAN_DRIVER_SLEEP_MODE_REQUEST);

	/*Enter into Initialization mode*/
	CAN1->MCR |= CAN_DRIVER_INIT_REQUEST;

	/*Wait until change confirmed, INAK is set and SLAK is cleared*/
	while (!((CAN1->MSR & CAN_DRIVER_INIT_ACKNOWLEDGE) != 0x00)
			&& ((CAN1->MSR & CAN_DRIVER_SLEEP_ACKNOWLEDGE) == 0x00))
	{
	}
}

void CAN_Driver_ModeChange(CAN_Driver_Operating_Modes Mode)
{
	CAN_Driver_StateSetters[Mode]();
}

void CAN_Driver_ReceiveMessage(CAN_Driver_Message *msg, uint8 MailBox_Number, uint8 FIFO_Number)
{
	/*Read the message identifiers*/
	if ((CAN1->sFIFOMailBox[FIFO_Number].RIR & (CAN_DRIVER_ID_STANDARD << 2)) == 0x00)
	{
		msg->Format = CAN_DRIVER_ID_STANDARD;
		msg->ID = (uint32_t) (0x000007FF) & (CAN1->sFIFOMailBox[FIFO_Number].RIR >> 21);
	}
	else if ((CAN1->sFIFOMailBox[FIFO_Number].RIR & (CAN_DRIVER_ID_EXTENDED << 2))
			!= 0x00)
	{
		msg->Format = CAN_DRIVER_ID_EXTENDED;
		msg->ID = (uint32_t) (0x0003FFFF) & (CAN1->sFIFOMailBox[FIFO_Number].RIR >> 3);
	}

	/*Read the message format*/
	if ((CAN1->sFIFOMailBox[FIFO_Number].RIR & (CAN_DRIVER_DATA_FRAME << 1)) == 0x00)
	{
		msg->Payload_Type = CAN_DRIVER_DATA_FRAME;
	}
	else if ((CAN1->sFIFOMailBox[FIFO_Number].RIR & (CAN_DRIVER_REMOTE_FRAME << 1))
			!= 0x00)
	{
		msg->Payload_Type = CAN_DRIVER_REMOTE_FRAME;
	}

	/*Get message length*/
	msg->Length = (uint8_t) ((0x0000000F) & (CAN1->sFIFOMailBox[FIFO_Number].RDTR));

	/*Get message lower part*/
	msg->Payload[0] = (uint8_t) (0x000000FF & (CAN1->sFIFOMailBox[FIFO_Number].RDLR));
	msg->Payload[1] =
			(uint8_t) (0x000000FF & (CAN1->sFIFOMailBox[FIFO_Number].RDLR >> 8));
	msg->Payload[2] =
			(uint8_t) (0x000000FF & (CAN1->sFIFOMailBox[FIFO_Number].RDLR >> 16));
	msg->Payload[3] =
			(uint8_t) (0x000000FF & (CAN1->sFIFOMailBox[FIFO_Number].RDLR >> 24));

	/*Get message higher part*/
	msg->Payload[4] = (uint8_t) (0x000000FF & (CAN1->sFIFOMailBox[FIFO_Number].RDHR));
	msg->Payload[5] =
			(uint8_t) (0x000000FF & (CAN1->sFIFOMailBox[FIFO_Number].RDHR >> 8));
	msg->Payload[6] =
			(uint8_t) (0x000000FF & (CAN1->sFIFOMailBox[FIFO_Number].RDHR >> 16));
	msg->Payload[7] =
			(uint8_t) (0x000000FF & (CAN1->sFIFOMailBox[FIFO_Number].RDHR >> 24));

	CAN_Driver_Release_Rx_MailBox(FIFO_Number);

	CAN_Driver_Clear_Request_Completed_Flag(MailBox_Number);
}

void CAN_Driver_Reset()
{
	/*Reset master, enter to sleep mode. Bit is reseted to 0 by hardware*/
	CAN1->MCR |= CAN_DRIVER_RESET;
}

void CAN_Driver_SendMessage(CAN_Driver_Message *msg,uint8 MailBox_Number)
{
	/*Reset the transmission identifier register*/
	CAN1->sTxMailBox[MailBox_Number].TIR = (uint32_t) 0x00;

	/*Set message ID and the IDE (identifier extension)*/
	if (msg->Format == CAN_DRIVER_ID_STANDARD)
	{
		CAN1->sTxMailBox[MailBox_Number].TIR |= (uint32_t) ((msg->ID << 21));
	}
	else if (msg->Format == CAN_DRIVER_ID_EXTENDED)
	{
		CAN1->sTxMailBox[MailBox_Number].TIR |= (uint32_t) ((msg->ID << 3)
				| (CAN_DRIVER_ID_EXTENDED << 2));
	}

	/*Set message type (Data or Remote frame)*/
	if (msg->Payload_Type == CAN_DRIVER_DATA_FRAME)
	{
		CAN1->sTxMailBox[MailBox_Number].TIR |= (CAN_DRIVER_DATA_FRAME << 1);
	}
	else if (msg->Payload_Type == CAN_DRIVER_REMOTE_FRAME)
	{
		CAN1->sTxMailBox[MailBox_Number].TIR |= (CAN_DRIVER_REMOTE_FRAME << 1);
	}

	/*Set the payload (lower part)*/

	CAN1->sTxMailBox[MailBox_Number].TDLR = (((uint32_t) msg->Payload[3] << 24)
			| ((uint32_t) msg->Payload[2] << 16)
			| ((uint32_t) msg->Payload[1] << 8) | (uint32_t) msg->Payload[0]);

	/*Set the payload (upper part)*/

	CAN1->sTxMailBox[MailBox_Number].TDHR = (((uint32_t) msg->Payload[7] << 24)
			| ((uint32_t) msg->Payload[6] << 16)
			| ((uint32_t) msg->Payload[5] << 8) | (uint32_t) msg->Payload[4]);

	/*Clear the message Length*/
	CAN1->sTxMailBox[MailBox_Number].TDTR &= ~((uint32) 0x0F);

	/*Set the message Length*/
	CAN1->sTxMailBox[MailBox_Number].TDTR |= (msg->Length & ((uint32) 0x0F));

	/*Set the Transmit Mailbox Empty interrupt*/
	/*CANx->IER|=(CAN_IER_TMEIE);*/

	/*Request the transmission of the data*/
	CAN1->sTxMailBox[MailBox_Number].TIR |= CAN_TI0R_TXRQ;
}

void CAN_Driver_SetFilter(uint32 ID)
{
	static uint8 CAN_ID_index = 0x00;
	uint32_t CAN_Msg_ID = 0x00;

	/*Bits 27:14 are available in connectivity line devices only and are reserved otherwise.*/
	/*Because the MCU is not a connectivity line device if a greater value then 13 is requested the function will stop
	 the configuration here.*/
	if (CAN_ID_index > 13)
	{
		return;
	}

	/*Set the ID's after the  mailbox identifier registers format*/
#if(CAN_DRIVER_SELECTED_ID_FORMAT==CAN_DRIVER_ID_STANDARD)
	CAN_Msg_ID |= (uint32_t) (ID << 21);

#elif(CAN_DRIVER_SELECTED_ID_FORMAT==CAN_DRIVER_ID_EXTENDED)
	/*Append the EXTENDED IDE after the ID, for STANDARD it is 0*/
	CAN_Msg_ID|=(uint32_t)((ID<<3)|(0x01<<2));

#endif

	/*Set Filter banks in Initialization mode*/
	CAN1->FMR |= CAN_DRIVER_FILTER_BANK_INITIALIZATION_MODE;

	/*Deactivate filter bank*/
	CAN1->FA1R &= (~((uint32_t) (1 << CAN_ID_index)));

	/*Set filter bank in list mode (each bit must match)*/
	CAN1->FM1R |= (uint32_t) (1 << CAN_ID_index);

	/*Set the filter bank to single 32-bit scale configuration*/
	CAN1->FS1R |= (uint32_t) (1 << CAN_ID_index);

	/*Set the ID in the filter bank and in the mask to (in list mode the mask register can be used to)*/
	CAN1->sFilterRegister[CAN_ID_index].FR1 = CAN_Msg_ID;
	CAN1->sFilterRegister[CAN_ID_index].FR2 = 0x00;

	/*Assign to FIFO0-0, FIFO1-1 (FIFO0 in our case) */
	CAN1->FFA1R &= ~(uint32_t) (1 << CAN_ID_index);

	/*Activate Filter Bank*/
	CAN1->FA1R |= ((uint32_t) (1 << CAN_ID_index));

	/*Set Filter banks in Active mode*/
	CAN1->FMR &= CAN_DRIVER_FILTER_BANK_ACTIVE_MODE;

	/*Increase filter index*/
	CAN_ID_index++;
}

void CAN_Driver_SetTestMode()
{
	CAN1->BTR &= ~(CAN_DRIVER_DEBUG_SILENT_MODE
			| CAN_DRIVER_DEBUG_LOOP_BACK_MODE);

#if (CAN_DRIVER_TEST_MODE_SILENT == OK)
	CAN1->BTR|=CAN_DRIVER_DEBUG_SILENT_MODE;
#endif

#if (CAN_DRIVER_TEST_MODE_LOOP_BACK == OK)
	CAN1->BTR |= CAN_DRIVER_DEBUG_LOOP_BACK_MODE;
#endif

#if(CAN_DRIVER_TEST_MODE_SILENT_AND_LOOP_BACK == OK)
	CAN1->BTR|=(CAN_DRIVER_DEBUG_SILENT_MODE|CAN_DRIVER_DEBUG_LOOP_BACK_MODE);
#endif
}

void CAN_Driver_Start()
{
	CAN_Driver_StateSetters[CAN_DRIVER_OPERATING_MODE_NORMAL]();
}

void CAN_Driver_Release_Rx_MailBox(uint8 FIFO_Number)
{
	if (FIFO_Number == CAN_Driver_FIFO_0)
	{
		/*Release FIFO 0 output mailbox*/
		CAN1->RF0R |= CAN_DRIVER_RELEASE_FIFO_MAILBOX;
	}
	else
	{
		/*Release FIFO 1 output mailbox*/
		CAN1->RF1R |= CAN_DRIVER_RELEASE_FIFO_MAILBOX;
	}
}

void CAN_Driver_Clear_Request_Completed_Flag(uint8 MailBox_Number)
{
	if (MailBox_Number == CAN_Driver_MailBox_0)
	{
		/*Clear Request completed flag in MailBox 0*/
		CAN1->TSR |= CAN_TSR_RQCP0;
	}
	else if (MailBox_Number == CAN_Driver_MailBox_1)
	{
		/*Clear Request completed flag in MailBox 1*/
		CAN1->TSR |= CAN_TSR_RQCP1;
	}
	else
	{
		/*Clear Request completed flag in MailBox 2*/
		CAN1->TSR |= CAN_TSR_RQCP2;
	}

}

uint8 CAN_Driver_Check_Message_Pending(uint8 FIFO_Number)
{
	uint8 result = 0x00;

	switch (FIFO_Number)
	{
	case CAN_Driver_FIFO_0:
		if ((CAN1->RF0R & 0x03) != NOK)
		{
			result = SUCCES;
		}
		else
		{
			result = FAILED;
		}
		break;
	case CAN_Driver_FIFO_1:
		if ((CAN1->RF1R & 0x03) != NOK)
		{
			result = SUCCES;
		}
		else
		{
			result = FAILED;
		}
		break;
	default:
		result = FAILED;
		break;
	}

	return result;
}

void CAN_Driver_Wait_for_Ready()
{
#if (CAN_DRIVER_USE_MAILBOX_0 == OK)
	/*This bit is set by hardware when no transmit request is pending for mailbox */
	while ((CAN1->TSR & CAN_DRIVER_TRANSMIT_MAILBOX0_EMPTY) == 0x00)
	{
	}
	/*CAN_Driver_Tx_global_status->CAN_Driver_Tx0_Ready = 0x01;*/
#elif (CAN_DRIVER_USE_MAILBOX_1 == OK)
	while((CAN1->TSR & CAN_DRIVER_TRANSMIT_MAILBOX1_EMPTY)==0x00)
	{}
	CAN_Driver_Tx_global_status->CAN_Driver_Tx1_Ready = 0x01;
#elif (CAN_DRIVER_USE_MAILBOX_2 == OK)
	while((CAN1->TSR & CAN_DRIVER_TRANSMIT_MAILBOX2_EMPTY)==0x00)
	{}
	CAN_Driver_Tx_global_status->CAN_Driver_Tx2_Ready = 0x01;
#endif

}

void CAN_Driver_Wake_Up()
{
	/*Exit from Sleep mode*/
	CAN1->MCR &= (~CAN_DRIVER_SLEEP_MODE_REQUEST);

	/*Wait until change confirmed*/
	while ((CAN1->MSR & CAN_DRIVER_SLEEP_ACKNOWLEDGE) != 0x00)
	{
	}
}
