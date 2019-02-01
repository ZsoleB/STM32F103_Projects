/* Includes */
#include "GPIO_Driver_Cfg.h"
#include "SPI_Driver_Cfg.h"
#include "SYSTICK_Driver_Cfg.h"

#define DELAY_TIME 200

uint32 TestVAr=0x00;

#define _a                                       		 		0x01
#define _b                                        				0x02
#define _c                                        				0x04
#define _d                                        				0x08
#define _e                                        				0x10
#define _f                                        				0x20
#define _g                                        				0x40
#define _dp                                        				0x80

#define _H_						 	  				  _b|_c|_e|_f|_g
#define _E_ 						 	 			  _a|_d|_e|_f|_g
#define _L_ 							  	    			_d|_e|_f
#define _O_                       	   			   _a|_b|_c|_d|_e|_f

uint8 state = 0x00;

int main(void)
{
	SYSTICK_Driver_Init();
	SYSTICK_Driver_Start();

	GPIO_Driver_Init();

	SPI_Driver_Init();
	SPI_Driver_Start(SPI_DRIVER_1);
/*Hello*/
	while (1)
	{
		SPI_Driver_Transcieve_Data(SPI_DRIVER_1,(uint16_t)_H_);
		SYSTICK_Driver_Delay_ms(200);
		SPI_Driver_Transcieve_Data(SPI_DRIVER_1,(uint16_t)_E_);
		SYSTICK_Driver_Delay_ms(200);
		SPI_Driver_Transcieve_Data(SPI_DRIVER_1,(uint16_t)_L_);
		SYSTICK_Driver_Delay_ms(200);
		SPI_Driver_Transcieve_Data(SPI_DRIVER_1,(uint16_t)_L_);
		SYSTICK_Driver_Delay_ms(200);
		SPI_Driver_Transcieve_Data(SPI_DRIVER_1,(uint16_t)_O_);
		SYSTICK_Driver_Delay_ms(200);
	}
}
