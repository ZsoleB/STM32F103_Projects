/*
 * Lin_Driver.h
 *
 *  Created on: Oct 23, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_LIN_DRIVER_LIN_DRIVER_H_
#define DRIVERS_LIN_DRIVER_LIN_DRIVER_H_

#include "USART_Driver_Cfg.h"
#include "SYSTICK_Driver_Cfg.h"

#define LIN_DRIVER_ENABLE											((uint32)(0x01<<0x0E))
#define LIN_DRIVER_SEND_BREAK										((uint32)(0x01<<0x00))
#define LIN_DRIVER_LIN_BREAK_DETECTION_LENGTH_10					((uint32)(0x00<<0x05))
#define LIN_DRIVER_LIN_BREAK_DETECTION_LENGTH_11					((uint32)(0x01<<0x05))
#define LIN_DRIVER_SEND_BREAK										((uint32)(0x01<<0x00))
#define LIN_DRIVER_SYNC_FIELD										((uint8)(0x55))

typedef struct
{
	USART_Driver_Setup_Type* USART_Setup_Instance;
	uint16 USART_Instance_number;
}LIN_Driver_Setup_Type;

typedef struct
{
	uint8_t Lin_frame_id:6;
	uint8_t Lin_frame_parity:2;
}LIN_Driver_PID_Field_Type;

extern LIN_Driver_Setup_Type* LIN_SETUP;
extern LIN_Driver_PID_Field_Type* LIN_PID;

void LIN_Driver_Init();
void LIN_Driver_Init_Cfg();
void LIN_Driver_Start(uint8 LIN_setup_nr);
void LIN_Driver_SendBreak(uint8 LIN_setup_nr);
void LIN_Driver_SendID(uint8 LIN_setup_nr,uint8 LIN_id);
void LIN_Driver_SendData(uint8 LIN_setup_nr,uint8 LIN_data);
uint8_t LIN_Driver_PID_Calculator(uint8_t data);

#endif /* DRIVERS_LIN_DRIVER_LIN_DRIVER_H_ */
