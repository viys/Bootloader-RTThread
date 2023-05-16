#include "gd32f10x.h"
#include "systick.h"
#include "uart.h"
#include "w25q64.h"
#include "fmc.h"
#include "main.h"
#include "boot.h"

OTA_InfoCB OTA_Info;
uint8_t rdata[256];

int main(void)
{
	systick_config();
	
	uart0_init(921600);

	w25q64_init();
	
	w25q64_read_OTA_info();
	
	u0_printf("进入B分区\r\n");
	
	bootloader_brance();
	
	while(1)
	{
		u0_transmit_test();
		delay_1ms(2000);
	}
}

