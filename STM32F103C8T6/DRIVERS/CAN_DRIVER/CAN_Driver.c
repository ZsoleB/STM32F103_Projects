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
#include "CAN_Driver.h"
#include "CAN_Driver_Cfg.h"

//CAN_Driver_Tx_Status* CAN_Driver_Tx_global_status = {0x00};
//CAN_Driver_Rx_Status* CAN_Driver_Rx_global_status = {0x00};

static CAN_Driver_Set_State CAN_Driver_StateSetters[]=
{
	CAN_Driver_Enter_InitMode,
	CAN_Driver_Enter_NormalMode,
	CAN_Driver_Enter_SleepMode
};

void CAN_Driver_DebugFreeze(CAN_TypeDef *CANx)
{
	#if (CAN_DRIVER_RUN_ON_DEBUG_MODE == OK)
		CANx->MCR &= (~(1<<16));
	#else
		CANx->MCR |= (1<<16);
	#endif
}

void CAN_Driver_Enter_NormalMode(CAN_TypeDef *CANx)
{
	/*Exit from Initialization mode, and enter normal mode*/
	CANx->MCR &=(~(0x01));

	/*Wait until change confirmed, 11 recessive bits are detected and the line is idle*/
	while(!(CANx->MSR & (0x01))!=0x00){}
}

void CAN_Driver_Enter_SleepMode(CAN_TypeDef *CANx)
{
	/*Exit from Initialization mode*/
	CANx->MCR &=(~(0x01));

	/*Enter into Sleep mode*/
	CANx->MCR |=(0x01<<1);

	/*Wait until change confirmed*/
	while(!((CANx->MSR & 0x02)!=0x00)&&
		  ((CANx->MSR & 0x01)==0x00)){}
}

void CAN_Driver_Init(CAN_TypeDef *CANx)
{

	RCC->APB1ENR|=RCC_APB1ENR_CAN1EN;
	/*Enter into initialization mode.
	Erroneous access to certain configuration registers can cause the hardware to temporarily
	disturb the whole CAN network. Therefore the CAN_BTR register can be modified by
	software only while the CAN hardware is in initialization mode.

	 */
	CAN_Driver_ModeChange(CANx,CAN_DRIVER_OPERATING_MODE_INIT);

	/*Set up the CAN option registers*/

	/*Can-debug configuration*/
	CAN_Driver_DebugFreeze(CANx);

	/*Self-test Mode*/
	CAN_Driver_SetTestMode(CANx);

	/*Can Transmit priority*/
	#if(CAN_DRIVER_TRANSMIT_PRIORITY == CAN_DRIVER_TRANSMIT_PRIORITY_BY_ID)
		CANx->MCR &= (~(1<<2));
	#elif(CAN_DRIVER_TRANSMIT_PRIORITY == CAN_DRIVER_TRANSMIT_PRIORITY_BY_TX_REQ_ORDER)
		CANx->MCR |= (1<<2);
	#endif

	/*Can Transmission mode*/
	#if(CAN_DRIVER_TRANSMISSION_MODE == CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE)
		CANx->MCR |= (1<<4);
	#elif(CAN_DRIVER_TRANSMIT_PRIORITY == CAN_DRIVER_AUTOMATIC_TRANSMISSION_MODE)
		CANx->MCR &= (~(1<<4));
	#endif

	/*Can Rx overwrite or retain the old values*/
	#if(CAN_DRIVER_RX_OVERWRITE_ENABLE == OK)
		CANx->MCR &= (~(1<<3));
	#else
		CANx->MCR |= (1<<3);
	#endif

	/*Can Time-Triggered transmission*/
	#if(CAN_DRIVER_TIME_TRIGGERED_TRANSMISSION == OK)
		CANx->MCR |= (1<<7);
	#else
		CANx->MCR &= (~(1<<7));
	#endif

	/*Can auto bus off management*/
	#if(CAN_DRIVER_AUTOMATIC_BUS_OFF_MANAGEMENT == OK)
		CANx->MCR |= (1<<6);
	#else
		CANx->MCR &= (~(1<<6));
	#endif

	/*Can automatic wake-up mode*/
	#if(CAN_DRIVER_AUTOMATIC_WAKE_UP_MODE == OK)
		CANx->MCR |= (1<<5);
	#else
		CANx->MCR &= (~(1<<5));
	#endif

	/*Set up the CAN bit timing registers*/
	/*Clear the TSEG1,TSEG2,SJW=4,CAN time quanta*/
	CANx->BTR &=  (~((0x03<<24)|(0x07<<20)|(0x0F<<16)|(0x3FF)));
	/*set TSEG1*/
	CANx->BTR |=  ((((CAN_DRIVER_BIT_SEGMENT1-1) & 0x0F)<<16));
	/*set TSEG2*/
	CANx->BTR |=  ((((CAN_DRIVER_BIT_SEGMENT2-1) & 0x07)<<20));
	/*set SJW*/
	CANx->BTR |=  ((((CAN_DRIVER_RESYNCHRONIZATION_JUMP_WIDTH-1) & 0x03)<<24));
	/*set CAN pescaler*/
	CANx->BTR |=  (((CAN_BAUD_RATE_PRESCALER-1) & 0x3FF));

	/*Set up additional functionalities, ex. TestModes*/
	#if (CAN_DRIVER_TEST_MODE_ENABLE == OK)
		CAN_Driver_SetTestMode(CANx);
	#endif
}

void CAN_Driver_InitTxPayload(CAN_Driver_Message *CAN_MSG)
{
	uint8_t index=0x00;

	for(index=0x00;index<8;index++)
	{
		CAN_MSG->Payload[index]=0x00;
	}
}

void CAN_Driver_Enter_InitMode(CAN_TypeDef *CANx)
{
	/*Exit from Sleep mode*/
	CANx->MCR &=(~(0x01<<1));

	/*Enter into Initialization mode*/
	CANx->MCR |=(0x01);

	/*Wait until change confirmed, INAK is set and SLAK is cleared*/
	while(!((CANx->MSR & 0x01)!=0x00)&&
		  ((CANx->MSR & 0x02)==0x00)){}
}

void CAN_Driver_ModeChange(CAN_TypeDef *CANx,CAN_Driver_Operating_Modes Mode)
{
	CAN_Driver_StateSetters[Mode](CANx);
}

void CAN_Driver_ReceiveMessage(CAN_TypeDef *CANx,CAN_Driver_Message *msg)
{
	/*Read the message identifiers*/
	if((CANx->sFIFOMailBox[0].RIR & (CAN_DRIVER_ID_STANDARD<<2))== 0x00)
	{
		msg->Format = CAN_DRIVER_ID_STANDARD;
		msg->ID = (uint32_t)(0x000007FF)&(CANx->sFIFOMailBox[0].RIR>>21);
	}
	else if((CANx->sFIFOMailBox[0].RIR & (CAN_DRIVER_ID_EXTENDED<<2))!= 0x00)
	{
		msg->Format = CAN_DRIVER_ID_EXTENDED;
		msg->ID = (uint32_t)(0x0003FFFF)&(CANx->sFIFOMailBox[0].RIR>>3);
	}

	/*Read the message format*/
	if((CANx->sFIFOMailBox[0].RIR & (CAN_DRIVER_DATA_FRAME<<1))== 0x00)
	{
		msg->Payload_Type = CAN_DRIVER_DATA_FRAME;
	}
	else if((CANx->sFIFOMailBox[0].RIR & (CAN_DRIVER_REMOTE_FRAME<<1))!= 0x00)
	{
		msg->Payload_Type = CAN_DRIVER_REMOTE_FRAME;
	}

	/*Get message length*/
	msg->Length = (uint8_t)((0x0000000F)&(CANx->sFIFOMailBox[0].RDTR));

	/*Get message lower part*/
	msg->Payload[0] = (uint8_t)(0x000000FF & (CANx->sFIFOMailBox[0].RDLR));
	msg->Payload[1] = (uint8_t)(0x000000FF & (CANx->sFIFOMailBox[0].RDLR>>8));
	msg->Payload[2] = (uint8_t)(0x000000FF & (CANx->sFIFOMailBox[0].RDLR>>16));
	msg->Payload[3] = (uint8_t)(0x000000FF & (CANx->sFIFOMailBox[0].RDLR>>24));

	/*Get message higher part*/
	msg->Payload[4] = (uint8_t)(0x000000FF & (CANx->sFIFOMailBox[0].RDHR));
	msg->Payload[5] = (uint8_t)(0x000000FF & (CANx->sFIFOMailBox[0].RDHR>>8));
	msg->Payload[6] = (uint8_t)(0x000000FF & (CANx->sFIFOMailBox[0].RDHR>>16));
	msg->Payload[7] = (uint8_t)(0x000000FF & (CANx->sFIFOMailBox[0].RDHR>>24));

	/*Release FIFO0 Output MailBox*/
	CANx->RF0R|=CAN_RF0R_RFOM0;
}

void CAN_Driver_Reset(CAN_TypeDef *CANx)
{
	/*Reset master, enter to sleep mode. Bit is reseted to 0 by hardware*/
	CANx->MCR|=((0x01)<<0x0F);
}

void CAN_Driver_SendMessage(CAN_TypeDef *CANx,CAN_Driver_Message *msg)
{
	/*Reset the transmission identifier register*/
	CANx->sTxMailBox[0].TIR =(uint32_t)0x00;

	/*Set message ID and the IDE (identifier extension)*/
	if(msg->Format == CAN_DRIVER_ID_STANDARD)
	{
		CANx->sTxMailBox[0].TIR |= (uint32_t)((msg->ID<<21));
	}
	else if(msg->Format == CAN_DRIVER_ID_EXTENDED)
	{
		CANx->sTxMailBox[0].TIR |= (uint32_t)((msg->ID<<3)|(0x01<<2));
	}

	/*Set message type (Data or Remote frame)*/
	if(msg->Payload_Type == CAN_DRIVER_DATA_FRAME)
	{
		CANx->sTxMailBox[0].TIR |= (0x00<<1);
	}
	else if(msg->Payload_Type == CAN_DRIVER_REMOTE_FRAME)
	{
		CANx->sTxMailBox[0].TIR |= (0x01<<1);
	}

	/*Set the payload (lower part)*/

	CANx->sTxMailBox[0].TDLR = (((uint32_t)msg->Payload[3]<<24)|
								((uint32_t)msg->Payload[2]<<16)|
								((uint32_t)msg->Payload[1]<<8) |
								 (uint32_t)msg->Payload[0]);

	/*Set the payload (upper part)*/

	CANx->sTxMailBox[0].TDHR = (((uint32_t)msg->Payload[7]<<24)|
								((uint32_t)msg->Payload[6]<<16)|
								((uint32_t)msg->Payload[5]<<8) |
								 (uint32_t)msg->Payload[4]);

	/*Clear the message Length*/
	CANx->sTxMailBox[0].TDTR &= ~((uint32)0x0F);

	/*Set the message Length*/
	CANx->sTxMailBox[0].TDTR |= (msg->Length & ((uint32)0x0F));

	/*Set the Transmit Mailbox Empty interrupt*/
	/*CANx->IER|=(CAN_IER_TMEIE);*/

	/*Request the transmission of the data*/
	CANx->sTxMailBox[0].TIR |=CAN_TI0R_TXRQ;
}

void CAN_Driver_SetFilter(CAN_TypeDef *CANx,uint32 ID)
{
	static uint8  CAN_ID_index = 0x00;
	uint32_t CAN_Msg_ID 	   = 0x00;

	/*Bits 27:14 are available in connectivity line devices only and are reserved otherwise.*/
	/*Because the MCU is not a connectivity line device if a greater value then 13 is requested the function will stop
	 the configuration here.*/
	if(CAN_ID_index>13){ return; }

	/*Set the ID's after the  mailbox identifier registers format*/
	#if(CAN_DRIVER_SELECTED_ID_FORMAT==CAN_DRIVER_ID_STANDARD)
		CAN_Msg_ID|=(uint32_t)(ID<<21);

	#elif(CAN_DRIVER_SELECTED_ID_FORMAT==CAN_DRIVER_ID_EXTENDED)
		/*Append the EXTENDED IDE after the ID, for STANDARD it is 0*/
		CAN_Msg_ID|=(uint32_t)((ID<<3)|(0x01<<2));

	#endif

	/*Set Filter banks in Initialization mode*/
	CANx->FMR |= 0x01;

	/*Deactivate filter bank*/
	CANx->FA1R &= (~((uint32_t)(1<<CAN_ID_index)));

	/*Set filter bank in list mode (each bit must match)*/
	CANx->FM1R|=(uint32_t)(1<<CAN_ID_index);

	/*Set the filter bank to single 32-bit scale configuration*/
	CANx->FS1R|=(uint32_t)(1<<CAN_ID_index);

	/*Set the ID in the filter bank and in the mask to (in list mode the mask register can be used to)*/
	CANx->sFilterRegister[CAN_ID_index].FR1 = CAN_Msg_ID;
	CANx->sFilterRegister[CAN_ID_index].FR2 = 0x00;

	/*Assign to FIFO0-0, FIFO1-1 (FIFO0 in our case) */
	CANx->FFA1R &= ~(uint32_t)(1<<CAN_ID_index);

	/*Activate Filter Bank*/
	CANx->FA1R |= ((uint32_t)(1<<CAN_ID_index));

	/*Set Filter banks in Active mode*/
	CANx->FMR &= (~(0x01));

	/*Increase filter index*/
	CAN_ID_index++;
}

void CAN_Driver_SetTestMode(CAN_TypeDef *CANx)
{
	CANx->BTR &= ~((0x01<<31)|(0x01<<30));

	#if (CAN_DRIVER_TEST_MODE_SILENT == OK)
		CANx->BTR|=(0x01<<31);
	#endif

	#if (CAN_DRIVER_TEST_MODE_LOOP_BACK == OK)
		CANx->BTR|=(0x01<<30);
	#endif

	#if(CAN_DRIVER_TEST_MODE_SILENT_AND_LOOP_BACK == OK)
		CANx->BTR|=((0x01<<31)|(0x01<<30));
	#endif
}

void CAN_Driver_Start(CAN_TypeDef *CANx)
{
	CAN_Driver_StateSetters[CAN_DRIVER_OPERATING_MODE_NORMAL](CANx);
}

void CAN_Driver_Wait_for_Ready (CAN_TypeDef *CANx)
{
	#if (CAN_DRIVER_USE_MAILBOX_0 == OK)
	/*This bit is set by hardware when no transmit request is pending for mailbox */
		while((CANx->TSR & (0x01<<26))==0x00){}
		/*CAN_Driver_Tx_global_status->CAN_Driver_Tx0_Ready = 0x01;*/
	#elif (CAN_DRIVER_USE_MAILBOX_1 == OK)
		while((CANx->TSR & (0x01<<27))==0x00){}
		CAN_Driver_Tx_global_status->CAN_Driver_Tx1_Ready = 0x01;
	#elif (CAN_DRIVER_USE_MAILBOX_2 == OK)
		while((CANx->TSR & (0x01<<28))==0x00){}
		CAN_Driver_Tx_global_status->CAN_Driver_Tx2_Ready = 0x01;
	#endif

}

void CAN_Driver_Wake_Up(CAN_TypeDef *CANx)
{
	/*Exit from Sleep mode*/
	CANx->MCR &=(~(0x01<<1));

	/*Wait until change confirmed*/
	while((CANx->MSR & (0x02))!=0x00){}
}
