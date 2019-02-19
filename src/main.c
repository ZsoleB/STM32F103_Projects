#include "SYSTICK_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"
#include "HWENCODER_Driver_Cfg.h"

uint32 dummy_value = 0x00;

int main()
{
	SYSTICK_Driver_Init();
	GPIO_Driver_Init();
	TCNT_Driver_Init();
	HWENCODER_Driver_Init();
	TCNT_Driver_Start(TCNT_DRIVER_TIM4);
	while (1)
	{
		dummy_value = HWENCODER_Driver_Get_Count_Value(HWENCODER_DRIVER_1);
	}
}
