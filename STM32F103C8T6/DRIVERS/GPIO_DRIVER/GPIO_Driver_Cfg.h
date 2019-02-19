/*
 * GPIO_Driver_Cfg.h
 *
 *  Created on: Jan 23, 2018
 *      Author: zsolt.balo
 */
#ifndef GPIO_DRIVER_CFG_H_
#define GPIO_DRIVER_CFG_H_

#include "GPIO_Driver.h"

#define GPIO_DRIVER_GPIOA 				  			NOK
#define GPIO_DRIVER_GPIOB 				  			OK
#define GPIO_DRIVER_GPIOC 				  			NOK
#define GPIO_DRIVER_GPIOD 				  			NOK
#define GPIO_DRIVER_GPIOE 				  			NOK
#define GPIO_DRIVER_INSTANCE_NUM 					((uint32)0x01)

typedef enum
{
	GPIO_DRIVER_PORTB,
}GPIO_Driver_Instances;

typedef enum
{
	GPIO_DRIVER_PORTB_PIN6,
	GPIO_DRIVER_PORTB_PIN7
}GPIO_Driver_B_Pin_Instances;

#endif /* GPIO_DRIVER_CFG_STM32F103_H_ */
