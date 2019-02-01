/*
 * SPI_Driver.h
 *
 *  Created on: May 7, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_SPI_DRIVER_SPI_DRIVER_H_
#define DRIVERS_SPI_DRIVER_SPI_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"
#include "GPIO_Driver_Cfg.h"

#define SPI_DRIVER_2_LINE_UNIDIRECTIONAL_DATA_FLOW					(((uint8)0x00)<<0x0F)
#define SPI_DRIVER_1_LINE_BIDIRECTIONAL_DATA_FLOW                   (((uint8)0x01)<<0x0F)
#define SPI_DRIVER_SOFTWARE_SLAVE_MANAGEMENT_CONFIG					(0x01<<0x09)
#define SPI_DRIVER_INTERNAL_SLAVE_SELECT_CONFIG						(0x01<<0x08)
#define SPI_DRIVER_SS_OUTPUT_ENABLE_CONFIG							(0x01<<0x02)
#define SPI_DRIVER_RECEIVE_ONLY_MODE                                (((uint8)0x00)<<0x0E)
#define SPI_DRIVER_TRANSMIT_ONLY_MODE                               (((uint8)0x01)<<0x0E)
#define SPI_DRIVER_8_BIT_DATA_FORMAT                                (((uint8)0x00)<<0x0B)
#define SPI_DRIVER_16_BIT_DATA_FORMAT                               (((uint8)0x01)<<0x0B)

/*Receive and Transmit*/
#define SPI_DRIVER_FULL_DUPLEX                                      (((uint8)0x00)<<0x0A)

/*Receive only mode*/
#define SPI_DRIVER_OUTPUT_DISABLED                                  (((uint8)0x01)<<0x0A)
#define SPI_DRIVER_MSB_FIRST                                        (((uint8)0x00)<<0x07)
#define SPI_DRIVER_LSB_FIRST                                        (((uint8)0x01)<<0x07)
#define SPI_DRIVER_BAUD_RATE_DIV2                                   (((uint8)0x00)<<0x03)
#define SPI_DRIVER_BAUD_RATE_DIV4                                   (((uint8)0x01)<<0x03)
#define SPI_DRIVER_BAUD_RATE_DIV8                                   (((uint8)0x02)<<0x03)
#define SPI_DRIVER_BAUD_RATE_DIV16                                  (((uint8)0x03)<<0x03)
#define SPI_DRIVER_BAUD_RATE_DIV32                                  (((uint8)0x04)<<0x03)
#define SPI_DRIVER_BAUD_RATE_DIV64                                  (((uint8)0x05)<<0x03)
#define SPI_DRIVER_BAUD_RATE_DIV128                                 (((uint8)0x06)<<0x03)
#define SPI_DRIVER_BAUD_RATE_DIV256                                 (((uint8)0x07)<<0x03)
#define SPI_DRIVER_MASTER_CONFIGURATION                             (((uint8)0x01)<<0x02)
#define SPI_DRIVER_SALVE_CONFIGURATION                              (((uint8)0x00)<<0x02)
#define SPI_DRIVER_CPOL_IDLE_0                                      (((uint8)0x00)<<0x01)
#define SPI_DRIVER_CPOL_IDLE_1                                      (((uint8)0x01)<<0x01)
#define SPI_DRIVER_PERIPHERAL_ENABLE                                (((uint8)0x01)<<0x06)
#define SPI_DRIVER_PERIPHERAL_DISABLE                               (((uint8)0x00)<<0x06)
#define SPI_DRIVER_CPHA_FIRST_CLOCK_TRANSITION                      ((uint8)0x00)
#define SPI_DRIVER_CPHA_SECOND_CLOCK_TRANSITION                     ((uint8)0x01)
#define SPI_DRIVER_CRC_POLYNOME										 ((uint16)0x0888)
#define SPI_DRIVER_BUSY_FLAG                                         ((uint16)0x0080)
#define SPI_DRIVER_OVERRUN_FLAG                                      ((uint16)0x0040)
#define SPI_DRIVER_MODE_FAULT                                        ((uint16)0x0020)
#define SPI_DRIVER_CRC_ERROR_FLAG                                    ((uint16)0x0010)
#define SPI_DRIVER_UNDERRUN_FLAG                                     ((uint16)0x0008)
#define SPI_DRIVER_CHANNEL_SIDE                                      ((uint16)0x0004)
#define SPI_DRIVER_TRANSMIT_BUFFER_EMPTY                             ((uint16)0x0002)
#define SPI_DRIVER_RECEIVE_BUFFER_NOT_EMPTY                          ((uint16)0x0001)
#define SPI_DRIVER_DUMMY_PAYLOAD                          			 ((uint32)0x00)

typedef struct
{
	SPI_TypeDef* SPI_Instance;
	uint8 SPI_Driver_communication_port;
	uint8 SPI_Driver_slave_select_port;
	uint8 SPI_Driver_slave_select_pin;
	uint8 SPI_Driver_miso_pin;
	uint8 SPI_Driver_mosi_pin;
	uint8 SPI_Driver_sck_pin;
	/*Divide 36 MHz with the selected prescaler*/
	uint8 SPI_Driver_baud_rate_control;
	uint8 SPI_Driver_clock_polarity;
	uint8 SPI_Driver_clock_phase;
	uint8 SPI_Driver_data_frame_format;
	uint8 SPI_Driver_frame_direction;
	uint8 SPI_Driver_master_slave_selection;
	uint8 SPI_Driver_receive_only_or_full_duplex;
	uint8 SPI_Driver_software_slave_management;
	uint8 SPI_Driver_inetrnal_slave_select;
	uint8 SPI_Driver_ss_output_enable;
	uint8 SPI_Driver_output_enable_in_bidirectional_mode;
	uint8 SPI_Driver_bidirectional_data_mode_enable;
	uint8 SPI_Driver_crc_calculation_enable;
}SPI_Driver_Setup_Type;

extern SPI_Driver_Setup_Type* SPI_SETUP;

void SPI_Driver_Init();
uint8 SPI_Driver_Get_Status(uint8 SPI_setup_nr,uint16 StatusCode);
uint16 SPI_Driver_Send_Data(uint8 SPI_setup_nr,uint16 data);
uint16 SPI_Driver_Transcieve_Data(uint8 SPI_setup_nr,uint16 data);
void SPI_Driver_Set_Slave_Select_Low(uint8 SPI_setup_nr);
void SPI_Driver_Set_Slave_Select_High(uint8 SPI_setup_nr);
void SPI_Driver_Start(uint8 SPI_setup_nr);
void SPI_Driver_Stop(uint8 SPI_setup_nr);

#endif /* DRIVERS_SPI_DRIVER_SPI_DRIVER_H_ */
