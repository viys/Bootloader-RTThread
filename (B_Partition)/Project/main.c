#include "gd32f10x.h"
#include "systick.h"
#include "uart.h"
#include "w25q64.h"
#include "fmc.h"
#include "main.h"
#include "boot.h"
#include "at24cxx.h"

OTA_InfoCB OTA_Info;

int main(void)
{
	systick_config();
	
	uart0_init(921600);
	
	i2c_eeprom_init();

	w25q64_init();
	
	at24cxx_read_OTA_info();
	
	bootloader_brance();
	
	while(1)
	{
		u0_transmit_test();
		delay_1ms(2000);
	}
}

