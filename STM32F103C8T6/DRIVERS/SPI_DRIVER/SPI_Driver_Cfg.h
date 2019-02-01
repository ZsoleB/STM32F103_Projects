/*
 * SPI_Driver_Cfg.h
 *
 *  Created on: May 7, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_SPI_DRIVER_SPI_DRIVER_CFG_H_
#define DRIVERS_SPI_DRIVER_SPI_DRIVER_CFG_H_

#include "SPI_Driver.h"

#define SPI_DRIVER_SPI1												OK
#define SPI_DRIVER_SPI2												NOK
#define SPI_DRIVER_CRC_CALCULATION_ENABLE							NOK
#define SPI_DRIVER_INSTANCE_NUM 									((uint32)0x01)

typedef enum
{
	SPI_DRIVER_1
}SPI_Driver_Instances;

#endif /* DRIVERS_SPI_DRIVER_SPI_DRIVER_CFG_H_ */
