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
volatile uint32_t BootSta_Flag;

int main(void)
{
	systick_config();
	
	uart0_init(380400);
	
	i2c_eeprom_init();

	w25q64_init();
	
	
	at24cxx_read_OTA_info();	
	
	bootloader_brance();
	
	while(1)
	{
		delay_1ms(10);
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
			if(UpdataA.Xmodem_Timer >= 100){
				/* 发送下载起始位 */
				u0_printf("C");
				/* 计数值清零 */
				UpdataA.Xmodem_Timer = 0;
			}
			UpdataA.Xmodem_Timer ++;
		}
		
		/* 将外部FLAH中代码写入A区 */
//		if(FlagGET(BootSta_Flag,UPDATA_A_FLAG)){
//			/* 更新A区 */
//			
//			u0_printf("Length: %d bytes\r\n",OTA_Info.Firelen[UpdataA.W25q64_blockNB]);
//			
//			/* 保证将要写入的数据是4字节对齐的 */
//			if(OTA_Info.Firelen[UpdataA.W25q64_blockNB]%4 == 0){
//				/* 长度正确 */
//				
//				/* 擦除 GD32 内部 FLASH */
//				gd32_erase_flash(GD32_A_SADDR,GD32_A_PAGE_NUM);
//				
//				
//				/******************************** 43.8:44*/ 
//				/* 更新代码 */
//				for(uint8_t i=0; i<OTA_Info.Firelen[UpdataA.W25q64_blockNB]/GD32_PAGE_SIZE; i++){
//					/* 从 FLASH 读取代码 */
//					w25q64_read(UpdataA.Updata_buff,\
//								i*GD32_PAGE_SIZE+UpdataA.W25q64_blockNB*SPI_FLASH_BlockSize,\
//								GD32_PAGE_SIZE);
//					/* 将代码更新到 GD32 */
//					gd32_write_flash(GD32_A_SADDR + i*GD32_PAGE_SIZE,\
//									(uint32_t *)UpdataA.Updata_buff,\
//									GD32_PAGE_SIZE);
//				}
//				
//				/* 更新剩余代码 */
//				if(OTA_Info.Firelen[UpdataA.W25q64_blockNB]%4 != 0){
//					w25q64_read(UpdataA.Updata_buff,\
//								OTA_Info.Firelen[UpdataA.W25q64_blockNB]/GD32_PAGE_SIZE*GD32_PAGE_SIZE+UpdataA.W25q64_blockNB*SPI_FLASH_BlockSize,\
//								GD32_PAGE_SIZE);
//					gd32_write_flash(GD32_A_SADDR + OTA_Info.Firelen[UpdataA.W25q64_blockNB]/GD32_PAGE_SIZE*GD32_PAGE_SIZE,\
//									(uint32_t *)UpdataA.Updata_buff,\
//									GD32_PAGE_SIZE);
//				}
//				
//				/* 清除更新标志位 */
//				if(UpdataA.W25q64_blockNB == 0){
//					OTA_Info.OTA_flag = 0;
//					at24cxx_write_OTA_info();
//				}
//				
//				/* 重启 */
//				NVIC_SystemReset();
//				
//			}else{
//				/* 长度错误 */
//				
//				/* 清空标志位 */
//				FlagCLR(BootSta_Flag,UPDATA_A_FLAG);
//				u0_printf("length Wrong\r\n");
//			}
//		}
	}
}

