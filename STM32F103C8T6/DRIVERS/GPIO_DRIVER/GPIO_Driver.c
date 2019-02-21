/*
 * GPIO_Driver.c
 *
 *  Created on: Jan 10, 2018
 *      Author: zsolt.balo
 */

#include "GPIO_Driver_Cfg.h"


/*Initialize the selected GPIO modules*/
void GPIO_Driver_Init()
{
	uint16 index = 0x00;
	uint16 index1 = 0x00;

	/*Enable the selected peripheral's clock signal*/

	#if GPIO_DRIVER_GPIOA!=NOK
		RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
	#endif
	#if GPIO_DRIVER_GPIOB!=NOK
		RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
	#endif
	#if GPIO_DRIVER_GPIOC!=NOK
		RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;
	#endif
	#if GPIO_DRIVER_GPIOD!=NOK
		RCC->APB2ENR|=RCC_APB2ENR_IOPDEN;
	#endif
	#if GPIO_DRIVER_GPIOE!=NOK
		RCC->APB2ENR|=RCC_APB2ENR_IOPEEN;
	#endif

	for(index=0x00;index<GPIO_DRIVER_INSTANCE_NUM;index++)
	{
		for(index1=0x00;index1<GPIO_SETUP[index].GPIO_Pin_nr;index1++)
		{
			if((GPIO_SETUP[index].GPIO_Pins[index1])<0x08)
			{
				/*The first step is to clear the default setting*/
				GPIO_SETUP[index].GPIO_Port->CRL  &=(~(((uint32)(0x03 <<(4*(GPIO_SETUP[index].GPIO_Pins[index1]))))|
							  	  	  	  	  	  	  ((uint32)(0x03 <<(2*((2*(GPIO_SETUP[index].GPIO_Pins[index1]))+1))))));
				/*Set the GPIO configuration*/
				GPIO_SETUP[index].GPIO_Port->CRL  |=((uint32)(GPIO_SETUP[index].GPIO_Pin_Mode[index1]<<(4*(GPIO_SETUP[index].GPIO_Pins[index1]))))|
													((uint32)(GPIO_SETUP[index].GPIO_Pin_Cfg[index1] <<(2*((2*(GPIO_SETUP[index].GPIO_Pins[index1]))+1))));
			}
			else
			{
				GPIO_SETUP[index].GPIO_Port->CRH  &=(~(((uint32)(0x03 <<(4*((GPIO_SETUP[index].GPIO_Pins[index1])-8))))|
				              	  	  	  	  	  	((uint32)(0x03 <<(2*((2*((GPIO_SETUP[index].GPIO_Pins[index1])-8))+1))))));
				GPIO_SETUP[index].GPIO_Port->CRH  |=((uint32)(GPIO_SETUP[index].GPIO_Pin_Mode[index1] <<(4*((GPIO_SETUP[index].GPIO_Pins[index1])-8))))|
							  	  	  	  	  	    ((uint32)(GPIO_SETUP[index].GPIO_Pin_Cfg[index1] <<(2*((2*((GPIO_SETUP[index].GPIO_Pins[index1])-8))+1))));
			}
		}
	}
}

/*Set the selected pin to 1*/
void GPIO_Driver_SetPin(uint8 GPIO_setup_nr,uint16 Pin)
{
	GPIO_SETUP[GPIO_setup_nr].GPIO_Port->BSRR|=(1<<(GPIO_SETUP[GPIO_setup_nr].GPIO_Pins[Pin]));
}

/*Clear the selected pin*/
void GPIO_Driver_ClearPin(uint8 GPIO_setup_nr,uint16 Pin)
{
	GPIO_SETUP[GPIO_setup_nr].GPIO_Port->BSRR|=((1<<(GPIO_SETUP[GPIO_setup_nr].GPIO_Pins[Pin]))<<16);
}

/*Read the value of the input data (the value of all the bits)*/
uint16 GPIO_Driver_ReadInputData(uint8 GPIO_setup_nr)
{
	uint16 result = 0x00;
	result = ((uint16)(GPIO_SETUP[GPIO_setup_nr].GPIO_Port->IDR));
	return result;
}

/*Read the value of the input data (the value of only one bit)*/
uint8 GPIO_Driver_ReadInputDataBit(uint8 GPIO_setup_nr,uint16 Bit_number)
{
	uint16 input = 0x00;
	uint8 result = 0x00;

	input  = ((uint16)(GPIO_SETUP[GPIO_setup_nr].GPIO_Port->IDR));
	result = ((input & ((0x01)<<(GPIO_SETUP[GPIO_setup_nr].GPIO_Pins[Bit_number])))!=0x00) ? 1 : 0;
	return result;

}

/*Read the value of the output data register(the value of all the bits)*/
uint16 GPIO_Driver_ReadOutputData(uint8 GPIO_setup_nr)
{
	uint16 result = 0x00;
	result = ((uint16)(GPIO_SETUP[GPIO_setup_nr].GPIO_Port->ODR));
	return result;
}
