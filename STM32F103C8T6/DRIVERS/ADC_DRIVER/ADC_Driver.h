/*
 * ADC_Driver.h
 *
 *  Created on: Jan 22, 2018
 *      Author: zsolt.balo
 */

#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"

/*ADC Configuration*/
#define ADC_DRIVER_ON												(0x01)
#define ADC_DRIVER_OFF												(~(0x01))
#define ADC_DRIVER_REGULAR_START									((0x01)<<0x16)
#define ADC_DRIVER_RESET_CALLIBRATION								((0x01)<<0x03)
#define ADC_DRIVER_CALLIBRATION										((0x01)<<0x02)
#define ADC_DRIVER_DISCONTINUOUS_MODE_ENABLE						((0x01)<<0x0B)
#define ADC_DRIVER_CONTINUOUS_CONVERSION							((0x01)<<0x01)
#define ADC_DRIVER_EXTERNAL_TRIGGER_ENABLE							((0x01)<<0x14)
#define ADC_DRIVER_EXTERNAL_TRIGGER_SWSTART							((0x07)<<0x11)
#define ADC_ALIGNMENT_LEFT											((0x01)<<0x0B)
#define ADC_ALIGNMENT_RIGHT											((0x00)<<0x0B)
#define ADC_DRIVER_REGULAR_CHANNEL_START_FLAG 						(0x10)
#define ADC_DRIVER_REGULAR_CHANNEL_END_OF_CONVERSION_FLAG 			(0x02)
#define ADC_DRIVER_ANALOG_WATCHDOG_FLAG 							(0x01)
#define ADC_DRIVER_PRESCALE_BY_2 									((0x00)<<14);/*Can be set in RCC_CFGR register*/
#define ADC_DRIVER_PRESCALE_BY_4 									((0x01)<<14);
#define ADC_DRIVER_PRESCALE_BY_6 									((0x02)<<14);
#define ADC_DRIVER_PRESCALE_BY_8 									((0x03)<<14);
#define ADC_DRIVER_CHANNEL_SAMPLING_TIME_1_5_CYCLES 				(0x00)
#define ADC_DRIVER_CHANNEL_SAMPLING_TIME_7_5_CYCLES 				(0x01)
#define ADC_DRIVER_CHANNEL_SAMPLING_TIME_13_5_CYCLES 				(0x02)
#define ADC_DRIVER_CHANNEL_SAMPLING_TIME_28_5_CYCLES 				(0x03)
#define ADC_DRIVER_CHANNEL_SAMPLING_TIME_41_5_CYCLES 				(0x04)
#define ADC_DRIVER_CHANNEL_SAMPLING_TIME_55_5_CYCLES 				(0x05)
#define ADC_DRIVER_CHANNEL_SAMPLING_TIME_71_5_CYCLES 				(0x06)
#define ADC_DRIVER_CHANNEL_SAMPLING_TIME_239_5_CYCLES 				(0x07)
#define ADC_DRIVER_SEQUENCE_1_CONVERSION							(0x00<<0x14)
#define ADC_DRIVER_SEQUENCE_2_CONVERSIONS							(0x01<<0x14)
#define ADC_DRIVER_SEQUENCE_3_CONVERSIONS							(0x02<<0x14)
#define ADC_DRIVER_SEQUENCE_4_CONVERSIONS							(0x03<<0x14)
#define ADC_DRIVER_SEQUENCE_5_CONVERSIONS							(0x04<<0x14)
#define ADC_DRIVER_SEQUENCE_6_CONVERSIONS							(0x05<<0x14)
#define ADC_DRIVER_SEQUENCE_7_CONVERSIONS							(0x06<<0x14)
#define ADC_DRIVER_SEQUENCE_8_CONVERSIONS							(0x07<<0x14)
#define ADC_DRIVER_SEQUENCE_9_CONVERSIONS							(0x08<<0x14)
#define ADC_DRIVER_SEQUENCE_10_CONVERSIONS							(0x09<<0x14)
#define ADC_DRIVER_SEQUENCE_11_CONVERSIONS							(0x0A<<0x14)
#define ADC_DRIVER_SEQUENCE_12_CONVERSIONS							(0x0B<<0x14)
#define ADC_DRIVER_SEQUENCE_13_CONVERSIONS							(0x0C<<0x14)
#define ADC_DRIVER_SEQUENCE_14_CONVERSIONS							(0x0D<<0x14)
#define ADC_DRIVER_SEQUENCE_15_CONVERSIONS							(0x0E<<0x14)
#define ADC_DRIVER_SEQUENCE_16_CONVERSIONS							(0x0F<<0x14)
#define ADC_DRIVER_SEQUENCE_POSITION_1								0x00
#define ADC_DRIVER_SEQUENCE_POSITION_2								0x01
#define ADC_DRIVER_SEQUENCE_POSITION_3								0x02
#define ADC_DRIVER_SEQUENCE_POSITION_4								0x03
#define ADC_DRIVER_SEQUENCE_POSITION_5								0x04
#define ADC_DRIVER_SEQUENCE_POSITION_6								0x05
#define ADC_DRIVER_SEQUENCE_POSITION_7								0x06
#define ADC_DRIVER_SEQUENCE_POSITION_8								0x07
#define ADC_DRIVER_SEQUENCE_POSITION_9								0x08
#define ADC_DRIVER_SEQUENCE_POSITION_10								0x09
#define ADC_DRIVER_SEQUENCE_POSITION_11								0x0A
#define ADC_DRIVER_SEQUENCE_POSITION_12								0x0B
#define ADC_DRIVER_SEQUENCE_POSITION_13								0x0C
#define ADC_DRIVER_SEQUENCE_POSITION_14								0x0D
#define ADC_DRIVER_SEQUENCE_POSITION_15								0x0E
#define ADC_DRIVER_SEQUENCE_POSITION_16								0x0F
#define ADC_DRIVER_CHANNEL_0								        0x00
#define ADC_DRIVER_CHANNEL_1								        0x01
#define ADC_DRIVER_CHANNEL_2								        0x02
#define ADC_DRIVER_CHANNEL_3								        0x03
#define ADC_DRIVER_CHANNEL_4								        0x04
#define ADC_DRIVER_CHANNEL_5								        0x05
#define ADC_DRIVER_CHANNEL_6								        0x06
#define ADC_DRIVER_CHANNEL_7								        0x07
#define ADC_DRIVER_CHANNEL_8								        0x08
#define ADC_DRIVER_CHANNEL_9								        0x09
#define ADC_DRIVER_CHANNEL_10								        0x0A
#define ADC_DRIVER_CHANNEL_11								        0x0B
#define ADC_DRIVER_CHANNEL_12								        0x0C
#define ADC_DRIVER_CHANNEL_13								        0x0D
#define ADC_DRIVER_CHANNEL_14								        0x0E
#define ADC_DRIVER_CHANNEL_15								        0x0F
#define ADC_DRIVER_CHANNEL_16								        0x10
#define ADC_DRIVER_CHANNEL_17								        0x11

typedef struct
{
	ADC_TypeDef* ADC_Instance;
	uint32 ADC_Single_Conversion;
	uint32 ADC_Scan_Mode;
	uint32 ADC_Discontinuous_Mode;
	uint32 ADC_Alignment;
	uint32 ADC_Sequence_Length;
	uint8 ADC_Channel_nr;
	uint8 ADC_Channels[10];
	uint8 ADC_Channel_SampligTime[10];
	uint8 ADC_Channel_Position[10];
}ADC_Driver_Setup_Type;

extern ADC_Driver_Setup_Type* ADC_SETUP;

uint16 ADC_Driver_GetSample(uint8 ADC_Instance_Number);
uint8 ADC_Driver_GetStatus(uint8 ADC_Instance_Number,uint8 Event);
void ADC_Driver_ClearStatus(uint8 ADC_Instance_Number);
void ADC_Driver_Init();
void ADC_Driver_Off(uint8 ADC_Instance_Number);
void ADC_Driver_On(uint8 ADC_Instance_Number);
void ADC_Driver_StartSampling(uint8 ADC_Instance_Number);
void ADC_Driver_SetChannel(uint8 ADC_Instance_Number,uint8 ChannelNumber);
void ADC_Driver_Set_Prescale_Value();

#endif /* ADC_DRIVER_H_ */
