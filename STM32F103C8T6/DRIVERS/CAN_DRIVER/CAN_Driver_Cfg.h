/*
 * CAN_Driver_Cfg.h
 *
 *  Created on: Apr 19, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_CAN_DRIVER_CAN_DRIVER_CFG_H_
#define DRIVERS_CAN_DRIVER_CAN_DRIVER_CFG_H_

#include "CAN_Driver.h"

#define CAN_DRIVER_NUMBER_OF_CHANNELS 						1
#define CAN_DRIVER_SELECTED_ID_FORMAT						CAN_DRIVER_ID_STANDARD
#define CAN_DRIVER_FREQUENCY								500000

/*The peripheral clock frequency from the system clock source (in our case PLL) divided by the configured division factor*/
#define CAN_DRIVER_PERIPHERAL_FREQUENCY 							((168000000)/4)
/*CAN bit timing parameters (the values can be selected from a standard value table) */
#define CAN_DRIVER_BIT_SEGMENT1 										12

#define CAN_DRIVER_BIT_SEGMENT2										 	 5

#define CAN_DRIVER_RESYNCHRONIZATION_JUMP_WIDTH 						 4

#define CAN_BAUD_RATE_PRESCALER		((CAN_DRIVER_PERIPHERAL_FREQUENCY/(CAN_DRIVER_BIT_SEGMENT1+CAN_DRIVER_BIT_SEGMENT2+1))/CAN_DRIVER_FREQUENCY)

/*Enable the CAN Driver to change its configuration from normal communication mode to a selected test mode*/
#define CAN_DRIVER_TEST_MODE_ENABLE							OK
/*The CAN can receive messages, but can't send any because, Tx is redirected to Rx*/
#define CAN_DRIVER_TEST_MODE_SILENT							NOK
/*The CAN Rx channel is connected directly to the Tx, and disconnected from the exterior*/
#define CAN_DRIVER_TEST_MODE_LOOP_BACK						OK
/*Both Tx and Rx are disconnected from the exterior*/
#define CAN_DRIVER_TEST_MODE_SILENT_AND_LOOP_BACK			NOK
/*CAN driver will run or the reception/transmission will be frozen while in debug*/
#define CAN_DRIVER_RUN_ON_DEBUG_MODE						OK
/*Check transmit mailbox 0*/
#define CAN_DRIVER_USE_MAILBOX_0							OK
/*Check transmit mailbox 1*/
#define CAN_DRIVER_USE_MAILBOX_1							NOK
/*Check transmit mailbox 2*/
#define CAN_DRIVER_USE_MAILBOX_2							NOK
/*Select the desired transmit priority (ID based or by the transmission order)*/
#define CAN_DRIVER_TRANSMIT_PRIORITY						CAN_DRIVER_TRANSMIT_PRIORITY_BY_ID
/*Select the desired transmission mode (automatic or non-automatic)*/
#define CAN_DRIVER_TRANSMISSION_MODE						CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE
/*

	Check if the RX FIFO can be overwritten by the new values,else
the three oldest frames will be retained, ignoring the new ones

*/
#define CAN_DRIVER_RX_OVERWRITE_ENABLE						OK
#define CAN_DRIVER_RX_FILTER_SCALE							CAN_DRIVER_FILTER_SCALE_32_BIT
/*

	In this mode, the internal counter of the CAN hardware is activated and used to generate the
Time Stamp value. The internal counter is incremented each CAN bit time. The internal counter
is captured on the sample point of the Start Of Frame bit in both reception and transmission.

 */
#define CAN_DRIVER_TIME_TRIGGERED_TRANSMISSION				NOK
/*This controls the behavior of the CAN hardware on leaving the Bus-Off state.

NOK - State is left on software request, once 128 occurrences of 11 recessive bits
have been monitored and the software has first set and cleared the INRQ bit of the
CAN_MCR register.

OK - The Bus-Off state is left automatically by hardware once 128 occurrences of 11 recessive
bits have been monitored.

*/
#define CAN_DRIVER_AUTOMATIC_BUS_OFF_MANAGEMENT				NOK
/*

 This bit controls the behavior of the CAN hardware on message reception during Sleep
mode.

NOK - The Sleep mode is left on software request by clearing the SLEEP bit of the CAN_MCR
register.

OK - The Sleep mode is left automatically by hardware on CAN message detection.
The SLEEP bit of the CAN_MCR register and the SLAK bit of the CAN_MSR register are
cleared by hardware.

 */
#define CAN_DRIVER_AUTOMATIC_WAKE_UP_MODE					NOK

#endif /* DRIVERS_CAN_DRIVER_CAN_DRIVER_CFG_H_ */
