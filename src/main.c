/* Includes */
#include "FLASH_Driver_Cfg.h"

#define TEST_ADDRESS        0x08019000

uint32 test = 0x00;


int main(void)
{
	FLASH_Driver_UnLock();
	FLASH_Driver_Program(TEST_ADDRESS,0xBEEF);
	FLASH_Driver_Lock();

	while (1)
	{
		/*Do nothing*/
		test++;
	}
}
