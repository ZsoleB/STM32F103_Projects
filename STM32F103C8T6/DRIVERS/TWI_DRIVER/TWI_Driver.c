/*
 * TWI_Driver.c
 *
 *  Created on: Jul 17, 2018
 *      Author: zsolt.balo
 */

#include "TWI_Driver_Cfg.h"

/*
 By default, I2c operates in slave mode. The interface automatically switches from slave to
 master, after it generates a START condition and from master to slave, if an arbitration
 loss or a Stop generation occurs, allowing multimaster capability.
 */

void TWI_Driver_Init()
{
	uint16 index = 0x00;

	/*Enable the clock in the peripheral bus*/
#if (TWI_DRIVER_TWI1 == OK)
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
#endif

#if (TWI_DRIVER_TWI2 == OK)
	RCC->APB1ENR|=RCC_APB1ENR_I2C2EN;
#endif

	for(index=0x00;index<TWI_DRIVER_INSTANCE_NUM;index++)
	{
		/*Reset the TWI module*/
		TWI_Driver_Reset(index);

#if(TWI_DRIVER_FUNCTIONALITY == TWI_DRIVER_INTERRUPT_FUNCTIONALITY)
		TWI_SETUP[TWI_setup_nr].TWI_Instance->CR2 |= TWI_DRIVER_EVENT_INTERRUPT_EN;
#endif
		/*Peripheral clock frequency*/
		TWI_Driver_SetClock(index);

		/*Enable peripheral*/
		TWI_Driver_Start(index);

		if (TWI_SETUP[index].TWI_acknowledge_enable == OK)
		{
			/* Acknowledge enable*/
			TWI_SETUP[index].TWI_Instance->CR1 |= (1 << 0x0A);
		}

		if (TWI_SETUP[index].TWI_clock_stretching_disable == OK)
		{
			/*Clock stretching disable*/
			TWI_SETUP[index].TWI_Instance->CR1 |= (1 << 0x07);
		}
		else
		{
			/*Clock stretching enable*/
			TWI_SETUP[index].TWI_Instance->CR1 &= (~(1 << 0x07));
		}

		if (TWI_SETUP[index].TWI_general_call_enable == OK)
		{
			/*General call enable*/
			TWI_SETUP[index].TWI_Instance->CR1 |= (1 << 0x06);
		}

		if (TWI_SETUP[index].TWI_smb_bus_mode == OK)
		{
			/*SMB Bus mode*/
			TWI_SETUP[index].TWI_Instance->CR1 |= (1 << 0x01);
		}

		if (TWI_SETUP[index].TWI_dual_addressing == NOK)
		{
			/*Disable dual addressing. Only the first address register can be used*/
			TWI_SETUP[index].TWI_Instance->OAR2 &= (~(0x01));
			/*Own address register 1*/
			TWI_SETUP[index].TWI_Instance->OAR1 = TWI_SETUP[index].TWI_own_address1;
		}
		else
		{
			/*Enable dual addressing. Both address registers can be used*/
			TWI_SETUP[index].TWI_Instance->OAR2 |= 0x01;
			/*Own address register 1*/
			TWI_SETUP[index].TWI_Instance->OAR1 = TWI_SETUP[index].TWI_own_address1;
			/*Own address register 2*/
			TWI_SETUP[index].TWI_Instance->OAR2 = TWI_SETUP[index].TWI_own_address2;
		}
	}
}

uint8 TWI_Driver_ReceiveData(uint8 TWI_setup_nr)
{
	/*Get the value from the TWI data register*/
	return (uint8) (TWI_SETUP[TWI_setup_nr].TWI_Instance->DR);
}

void TWI_Driver_Reset(uint8 TWI_setup_nr)
{
	/*This can be used to reinitialize the peripheral after an error or
	 a locked state. As an example, if the BUSY bit is set and remains locked
	 due to a glitch on the bus, the SWRST bit can be used to exit from this state.*/

	/*Software reset*/
	TWI_SETUP[TWI_setup_nr].TWI_Instance->CR1 |= (1 << 0x0F);
	TWI_SETUP[TWI_setup_nr].TWI_Instance->CR1 &= (~(1 << 0x0F));
}

void TWI_Driver_SetClock(uint8 TWI_setup_nr)
{
	uint16 result = 0x04;

	/*Stop the peripheral before setting the clock*/
	TWI_Driver_Stop(TWI_setup_nr);

	/*Set peripheral clock frequency in CR2*/
	TWI_SETUP[TWI_setup_nr].TWI_Instance->CR2 |= TWI_DRIVER_PCLOCK_MHZ;

	/*Speed mode selection*/
	if (TWI_SETUP[TWI_setup_nr].TWI_clock_mode == TWI_DRIVER_STANDARD_SPEED_100KHz)
	{
		/*Standard mode selected*/
		TWI_SETUP[TWI_setup_nr].TWI_Instance->CCR &= (~(1 << 0x0F));

		/*Clock control*/
		result = (uint16) ((TWI_DRIVER_PCLK_VALUE)/(TWI_SETUP[TWI_setup_nr].TWI_clock_frequency << 1));

		if (result < 0x04)
		{
			result = 0x04;
		}

		TWI_SETUP[TWI_setup_nr].TWI_Instance->CCR |= result;

		/* Maximum rise time in Fm/Sm mode (values can be looked up in the datasheet)*/
		TWI_SETUP[TWI_setup_nr].TWI_Instance->TRISE = (uint16) (TWI_DRIVER_PCLOCK_MHZ + 1);

	}
	else
	{
		/*Fast mode selected*/
		TWI_SETUP[TWI_setup_nr].TWI_Instance->CCR |= (1 << 0x0F);

		/*Duty cycle*/
		if (TWI_SETUP[TWI_setup_nr].TWI_fast_mode_duty_cycle == TWI_DRIVER_FAST_SPEED_DUTY_CYCLE_2)
		{

			TWI_SETUP[TWI_setup_nr].TWI_Instance->CCR &= (~(0x01 << 0x0E));

			/*Clock control*/
			result = (uint16) ((TWI_DRIVER_PCLK_VALUE)/(TWI_SETUP[TWI_setup_nr].TWI_clock_frequency * 3));
		}
		else
		{

			TWI_SETUP[TWI_setup_nr].TWI_Instance->CCR |= (0x01 << 0x0E);

			/*Clock control*/
			result = (uint16) ((TWI_DRIVER_PCLK_VALUE)/(TWI_SETUP[TWI_setup_nr].TWI_clock_frequency * 25));
		}

		if (result < 0x01)
		{
			result = 0x01;
		}

		TWI_SETUP[TWI_setup_nr].TWI_Instance->CCR |= result;

		/* Maximum rise time in Fm/Sm mode (values can be looked up in the datasheet)*/
		TWI_SETUP[TWI_setup_nr].TWI_Instance->TRISE = (uint16) ((TWI_DRIVER_PCLOCK_MHZ*((uint16_t) 300 / (uint16_t) 1000)) + 1);
	}
}

void TWI_Driver_SendData(uint8 TWI_setup_nr, uint8 Payload)
{
	TWI_SETUP[TWI_setup_nr].TWI_Instance->DR = Payload;
}

void TWI_Driver_SendAddress(uint8 TWI_setup_nr, uint8 Address)
{
	TWI_SETUP[TWI_setup_nr].TWI_Instance->DR = Address;
}

void TWI_Driver_SendStart(uint8 TWI_setup_nr)
{
	TWI_SETUP[TWI_setup_nr].TWI_Instance->CR1 |= (1 << 0x08);
}

void TWI_Driver_SendStop(uint8 TWI_setup_nr)
{
	TWI_SETUP[TWI_setup_nr].TWI_Instance->CR1 |= (1 << 0x09);
}

void TWI_Driver_Start(uint8 TWI_setup_nr)
{
	/*Start I2C peripheral*/
	TWI_SETUP[TWI_setup_nr].TWI_Instance->CR1 |= 0x01;
}

void TWI_Driver_Stop(uint8 TWI_setup_nr)
{
	/*Start I2C peripheral*/
	TWI_SETUP[TWI_setup_nr].TWI_Instance->CR1 &= (~(0x01));
}

uint8 TWI_Driver_Get_Status(uint8 TWI_setup_nr, uint32 StatusCode)
{
	uint32 CompleteStatus = 0x00, flag1 = 0x00, flag2 = 0x00;
	uint8 ResultCode = 0x00;

	flag1 = TWI_SETUP[TWI_setup_nr].TWI_Instance->SR1;
	flag2 = TWI_SETUP[TWI_setup_nr].TWI_Instance->SR2;
	CompleteStatus = ((flag2 << 16) | flag1);

	if (CompleteStatus == StatusCode)
	{
		ResultCode = SUCCES;
	}
	else
	{
		ResultCode = FAILED;
	}
	return ResultCode;
}

#if(TWI_DRIVER_FUNCTIONALITY == TWI_DRIVER_POLLING_FUNCTIONALITY)

void TWI_Driver_PollingOneByteTx(uint8 TWI_setup_nr, uint8 message,
uint8 Address)
{
	TWI_Driver_SendStart(TWI_setup_nr);

	while (TWI_Driver_Get_Status(TWI_setup_nr, TWI_DRIVER_EV5) != SUCCES)
	{
		/*Wait until the flags are set*/
	}
	TWI_Driver_SendAddress(TWI_setup_nr, Address);

	while (TWI_Driver_Get_Status(TWI_setup_nr, TWI_DRIVER_EV6) != SUCCES)
	{
		/*Wait until the flags are set*/
	}
	TWI_Driver_SendData(TWI_setup_nr, message);

	while (TWI_Driver_Get_Status(TWI_setup_nr, TWI_DRIVER_EV8_2) != SUCCES)
	{
		/*Wait until the flags are set*/
	}
	TWI_Driver_SendStop(TWI_setup_nr);
}
void TWI_Driver_PollingTx(uint8 TWI_setup_nr,
		TWI_DRIVER_Messagebuffer_Type* payload)
{
}
void TWI_Driver_PollingOneByteRx(uint8 TWI_setup_nr, uint8 message,
uint8 Address)
{
}
void TWI_Driver_PollingRx(uint8 TWI_setup_nr,
		TWI_DRIVER_Messagebuffer_Type* payload)
{
}

#elif(TWI_DRIVER_FUNCTIONALITY == TWI_DRIVER_INTERRUPT_FUNCTIONALITY)

void TWI_Driver_InterruptOneByteTx(uint8 TWI_setup_nr, uint8 message,
		uint8 Address)
{
}
void TWI_Driver_InterruptTx(uint8 TWI_setup_nr,
		TWI_DRIVER_Messagebuffer_Type* payload)
{
}
void TWI_Driver_InterruptOneByteRx(uint8 TWI_setup_nr, uint8 message,
		uint8 Address)
{
}
void TWI_Driver_InterruptRx(uint8 TWI_setup_nr,
		TWI_DRIVER_Messagebuffer_Type* payload)
{
}

#endif
