#include "SYSTICK_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"
#include "ADC_Driver_Cfg.h"

uint16 ADC_Sample = 0x00;

int main()
{
	SYSTICK_Driver_Init();
	SYSTICK_Driver_Start();

	GPIO_Driver_Init();
	ADC_Driver_Init();

	while (1)
	{
		ADC_Driver_StartSampling(ADC_DRIVER_1);
		if((ADC_Driver_GetStatus(ADC_DRIVER_1,ADC_DRIVER_REGULAR_CHANNEL_END_OF_CONVERSION_FLAG))==SUCCES)
		{
			ADC_Sample = ADC_Driver_GetSample(ADC_DRIVER_1);
		}
	}
}
