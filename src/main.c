#include "SYSTICK_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"
#include "CAN_Driver_Cfg.h"

volatile uint32 TimerCounter = 0x00;
uint8 DummyValue = 0x01;
CAN_Driver_Message TestPayload;
CAN_Driver_Message TestRxPayload;
uint8 tx_payload[] = {0xFF,0x12,0xBA};

int main()
{
	SYSTICK_Driver_Init();
	SYSTICK_Driver_Start();

	GPIO_Driver_Init();

	CAN_Driver_Init();
	CAN_Driver_SetFilter(0x01);
	CAN_Driver_InitBuffer(&TestPayload);
	CAN_Driver_InitBuffer(&TestRxPayload);
	CAN_Driver_Start();

	TestPayload.ID = 0x01;
	TestPayload.Format = CAN_DRIVER_ID_STANDARD;
	TestPayload.Payload_Type = CAN_DRIVER_DATA_FRAME;
	CAN_Driver_SetBuffer(&TestPayload,3,tx_payload);

	while (1)
	{
		CAN_Driver_Wait_for_Ready();

		CAN_Driver_SendMessage(&TestPayload,CAN_Driver_MailBox_0);

		while (CAN_Driver_Check_Message_Pending(CAN_Driver_FIFO_0) == FAILED)
		{
			/*Do nothing*/
		}

		CAN_Driver_ReceiveMessage(&TestRxPayload,CAN_Driver_MailBox_0,CAN_Driver_FIFO_0);

		SYSTICK_Driver_Delay_ms(200);
	}
}
