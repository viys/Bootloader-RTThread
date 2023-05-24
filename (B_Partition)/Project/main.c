#include "gd32f10x.h"
#include "systick.h"
#include "uart.h"
#include "w25q64.h"
#include "fmc.h"
#include "main.h"
#include "boot.h"
#include "at24cxx.h"

OTA_InfoCB OTA_Info;
UpDataA_CB UpdataA;
volatile uint32_t BootSta_Flag = 0;

int main(void)
{
	systick_config();
	
	uart0_init(460800);

	/* 用到较为复杂的更新功能时打开注释 */
	i2c_eeprom_init();

	w25q64_init();

	at24cxx_read_OTA_info();	
	
	bootloader_branch();
	
	while(1)
	{
		/* Bootloader命令行程序 */
		u0_input_detection();
		
		/* 串口IAP下载代码 */
		u0_printf_C();
		
		/* 将外部FLAH中代码写入A区 */
		event_write_eflash_to_A();
	
	}
}

