#include "SYSTICK_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"
#include "EXTI_Driver_Cfg.h"

uint8 daCounter = 0x00;

void EXTI1_IRQHandler()
{
	daCounter++;
	EXTI_Driver_Clear_PendingInterrupt(EXTI_DRIVER_INTERRUPT_PIN_1);
}

int main()
{
	SYSTICK_Driver_Init();
	SYSTICK_Driver_Start();

	GPIO_Driver_Init();
	EXTI_Driver_Init(EXTI_DRIVER_INTERRUPT_PIN_1,EXTI_DRIVER_INTERRUPT_PORT_A,EXTI_DRIVER_INTERRUPT_ACTION);
	EXTI_Driver_Rising_Trigger_Select(EXTI_DRIVER_INTERRUPT_PIN_1);

	while (1)
	{
		daCounter++;
		if(daCounter==0x07)
		{
			EXTI_Driver_Generate_SWInterrupt(EXTI_DRIVER_INTERRUPT_PIN_1);
		}
	}
}
