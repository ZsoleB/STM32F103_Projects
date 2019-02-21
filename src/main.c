#include "SYSTEM_Driver_Cfg.h"
#include "SYSTICK_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"

int main()
{
	SYSTICK_Driver_Init();
	GPIO_Driver_Init();
	SYSTEM_Driver_PVD_Init();

	while (1)
	{
		if ((SYSTEM_Driver_PVD_Get_Power_Status())==SUCCES)
		{
			GPIO_Driver_SetPin(GPIO_DRIVER_PORTA, GPIO_DRIVER_PORTA_PIN3);
		}
		else
		{
			GPIO_Driver_SetPin(GPIO_DRIVER_PORTA, GPIO_DRIVER_PORTA_PIN3);
			SYSTICK_Driver_Delay_ms(200);
			GPIO_Driver_ClearPin(GPIO_DRIVER_PORTA, GPIO_DRIVER_PORTA_PIN3);
			SYSTICK_Driver_Delay_ms(200);
		}
	}
}
