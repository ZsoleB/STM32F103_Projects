/*
 * Lin_Drive_Cfg.h
 *
 *  Created on: Oct 23, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_LIN_DRIVER_LIN_DRIVER_CFG_H_
#define DRIVERS_LIN_DRIVER_LIN_DRIVER_CFG_H_

#include "Lin_Driver.h"

#define LIN_DRIVER_INSTANCE_NUM 								((uint32)0x01)
#define LIN_DRIVER_LIN_BREAK_DETECTION_LENGTH					LIN_DRIVER_LIN_BREAK_DETECTION_LENGTH_11

typedef enum
{
	LIN_DRIVER_1,
}LIN_Driver_Instances;

#endif /* DRIVERS_LIN_DRIVER_LIN_DRIVER_CFG_H_ */
