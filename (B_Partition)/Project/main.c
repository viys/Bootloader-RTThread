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
// DBG
	uart2_init(460800);
//	dbg_efaslh();
	
	bootloader_brance();
	
	while(1)
	{
		/* Bootloader命令行程序 */
		if(U0CB.URxDataOUT != U0CB.URxDataIN){
			/* 命令处理 */
			bootloader_event(U0CB.URxDataOUT->start,U0CB.URxDataOUT->end - U0CB.URxDataOUT->start + 1);
			U0CB.URxDataOUT ++;
			
			if(U0CB.URxDataOUT == U0CB.URxDataEND){
				U0CB.URxDataOUT = &U0CB.URxDataPtr[0];
			}
		
		}
		
		/* 串口IAP下载代码 */
		if(FlagGET(BootSta_Flag,IAP_XMODEC_FLAG)){
			
			/* 达到Xmodem约定时间 */
			if(UpdataA.Xmodem_Timer >= 1000){
				/* 发送下载起始位 */
				u0_printf("C");
				/* 计数值清零 */
				UpdataA.Xmodem_Timer = 0;
			}
			
		}
		
		/* 将外部FLAH中代码写入A区 */
		event_write_eflash_to_A();
	
	}
}

