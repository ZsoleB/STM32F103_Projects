/*
 * RTC_Driver.h
 *
 *  Created on: Oct 26, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_RTC_DRIVER_RTC_DRIVER_H_
#define DRIVERS_RTC_DRIVER_RTC_DRIVER_H_

#include "stm32f10x.h"
#include "StdTypes.h"

#define RTC_DRIVER_RESET_BAKUP_DOMAIN							(0x01<<0x10)
#define RTC_DRIVER_ENABLE										(0x01<<0x0F)
#define RTC_DRIVER_DISABLE										(~(0x01<<0x0F))
#define RTC_DRIVER_NO_CLK										(~(0x03<<0x08))
#define RTC_DRIVER_LSE_CLK										(0x01<<0x08)
#define RTC_DRIVER_LSI_CLK										(0x02<<0x08)
/*The HSE clock is divided by 128 internally*/
#define RTC_DRIVER_HSE_CLK										(0x03<<0x08)
#define RTC_DRIVER_LSE_CLK_ON									(0x01)
#define RTC_DRIVER_LSE_CLK_OFF									(0x00)
#define RTC_DRIVER_LSE_CLOCK_READY								((0x01)<<0x01)
#define RTC_DRIVER_REGISTERS_SYNCHRONIZED_FLAG					((0x01)<<0x03)
#define RTC_DRIVER_DISABLE_BACKUP_WRITE_PROTECTION				(0x01<<0x08)
#define RTC_DRIVER_ENABLE_BACKUP_WRITE_PROTECTION				(~(0x01<<0x08))
#define RTC_DRIVER_SYNCHRONIZED									(0x01<<0x03)
#define RTC_DRIVER_SECOND_INTERRUPT_ENABLE						(0x01)
#define RTC_DRIVER_ALARM_INTERRUPT_ENABLE						(0x02)
#define RTC_DRIVER_OVERFLOW_INTERRUPT_ENABLE					(0x04)

typedef void (*RTC_Driver_callback_type)();
RTC_Driver_callback_type RTC_Driver_Interrupt_Callback;

void RTC_Driver_Init();
uint8 RTC_Driver_Read_SecondStatus();
void RTC_Driver_Synchronize();

#endif /* DRIVERS_RTC_DRIVER_RTC_DRIVER_H_ */
