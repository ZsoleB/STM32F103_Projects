/*
 * SYSTEM_Driver_Cfg.h
 *
 *  Created on: Oct 1, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_CFG_H_
#define DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_CFG_H_

#include "SYSTEM_Driver.h"

#define SYSTEM_DRIVER_CLK_SOURCE 			SYSTEM_DRIVER_SWITCH_TO_PLL
#define SYSTEM_DRIVER_PLL_SOURCE 			SYSTEM_DRIVER_PLL_CLOCK_SRC_HSE
#define SYSTEM_DRIVER_PLL_MULTIPLIER 		SYSTEM_DRIVER_PLLMUL_9
#define SYSTEM_DRIVER_HCLK_DIV 	 			SYSTEM_DRIVER_AHB_NDIV
#define SYSTEM_DRIVER_PCLK1_DIV 			SYSTEM_DRIVER_APB1_DIV2
#define SYSTEM_DRIVER_PCLK2_DIV 			SYSTEM_DRIVER_APB2_NDIV

/*Select the low power mode(s), which can be used by the application*/
#define SYSTEM_DRIVER_SLEEP_ENABLE 			NOK
#define SYSTEM_DRIVER_STOP_ENABLE 			NOK
#define SYSTEM_DRIVER_STANDBY_ENABLE 		NOK

/*Select the how should the sleep mode behave, before entering in the sleep state*/
#define SYSTEM_DRIVER_SLEEP_MODE 			SYSTEM_DRIVER_SLEEP_NOW

/*Select the how should the low-power mode(s) be entered*/
#define SYSTEM_DRIVER_SLEEP_ENTER 			SYSTEM_DRIVER_USE_WFI
#define SYSTEM_DRIVER_STOP_ENTER 			SYSTEM_DRIVER_USE_WFI
#define SYSTEM_DRIVER_STANDBY_ENTER 		SYSTEM_DRIVER_USE_WFI

/*The event wake-up can't be used, when SLEEP-ON-EXIT is used*/
#if((SYSTEM_DRIVER_SLEEP_MODE == SYSTEM_DRIVER_SLEEP_ON_EXIT)&&\
(SYSTEM_DRIVER_SLEEP_ENTER  != SYSTEM_DRIVER_USE_WFI))

#error "The sleep mode can't be entered and/or woken up, when SLEEP-ON-EXIT is used"

#endif

#define SYSTEM_DRIVER_WKUP_PIN_ENABLE 		OK

/*When the voltage regulator operates in low-power mode, an additional startup delay is
incurred when waking up from Stop mode. By keeping the internal regulator ON during Stop
mode, the consumption is higher although the startup time is reduced.*/
#define SYSTEM_DRIVER_STOP_MODE_LP_ENABLE 	OK

#define SYSTEM_DRIVER_PVD_ENABLE 			OK
#define SYSTEM_DRIVER_PVD_THRESHOLD 		SYSTEM_DRIVER_PVD_LEVEL_6

#endif /* DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_CFG_H_ */
