#include "boot.h"
#include "main.h"
#include "uart.h"
#include "fmc.h"
#include "at24cxx.h"
#include "string.h"
#include "w25q64.h"
#include "systick.h"

load_a LOAD_A;

static uint8_t bootloader_enter(uint8_t timeout)
{
	u0_printf("Please enter 'w' within %ds to enter BootLoader command\r\n",timeout/10);
	while(timeout--){
		delay_1ms(100);
		if(U0_RxBuff[0] == 'w'){
			
			/* 进入命令行 */
			return 1;
		}
	}
	
	return 0;
	
}

/* 输出Bootloader命令行信息 */
static void bootloader_info(void)
{
	/* 擦除A区代码 */
	u0_printf("[1]Erase A partition\r\n");
	/* 串口IAP下载A区代码 */
	u0_printf("[2]Serial download to A\r\n");
	/* 设置版本号 */
	u0_printf("[3]Set the version number\r\n");
	/* 查询版本号 */
	u0_printf("[4]Query the version number\r\n");
	/* 向外部FLASH下载程序 */
	u0_printf("[5]Download program to E-flash\r\n");
	/* 使用外部FLASH内程序 */
	u0_printf("[6]Use E-Flash`s programs\r\n");
	/* 软件重启 */
	u0_printf("[7]Reboot\r\n");
}

/* 16位CRC校验 */
uint16_t xmodem_CRC16(uint8_t *data,uint16_t datalen)
{
	/* Xmdoem CRC校验的初始值，必须是0x0000 */
	uint16_t Crcinit = 0x0000;
	/* Xmdoem CRC校验的多项式，必须是0x1021 */
	uint16_t Crcipoly = 0x1021;
	
	/* 根据datalen大小，有多少字节循环多少次 */
	while(datalen--){
		
		/* 先将带校验的字节，挪到高8位 */
		Crcinit = (*data << 8) ^ Crcinit;
		
		/* 每个字节8个二进制位，循环8次 */
		for(uint8_t i=0;i<8;i++){
			
			if(Crcinit&0x8000){
				/* 判断BIT15是1还是0,是1的话，进入if */
				
				/* 是1的话，先左移，再异或多项式 */
				Crcinit = (Crcinit << 1) ^ Crcipoly;
			}
			else{
				/* 判断BIT15是1还是0,是0的话，进入else */
				
				/* 是0的话，只左移 */
				Crcinit = (Crcinit << 1);
			}
		}
		
		/* 下移，计算一个字节数据 */
		data++;
	}
	/* 返回校验后的数据 */
	return Crcinit;
}

/* Bootloader命令行事件处理 */
void bootloader_event(uint8_t *data,uint16_t datalen)
{
	if(BootSta_Flag == 0){
	
		if((datalen==1)&&(data[0]=='1')){
			/* 擦除A区代码 */
			
			u0_printf("Erase A partition\r\n");
			/* 擦除A区 */
			gd32_erase_flash(GD32_A_SPAGE,GD32_A_PAGE_NUM);
			
			u0_printf("Finsh erase\r\n");
			
		}else if((datalen==1)&&(data[0]=='2')){
			/* 串口IAP下载A区代码 */
			
			/* 通过Xmodem协议,串口IAP下载程序到A区,请使用二进制文件 */
			u0_printf("Via Xmodem:IAP download program to A,please upload bin\r\n");
			/* 擦除A区 */
			gd32_erase_flash(GD32_A_SPAGE,GD32_A_PAGE_NUM);
			/* 相应的Flag置位 */
			FlagSET(BootSta_Flag,IAP_XMODEC_FLAG|IAP_XMODED_FLAG);
			/* Xmodem时间计数器清零 */
			UpdataA.Xmodem_Timer = 0;
			/* Xmodem传输计数值清零 */
			UpdataA.xmodem_NB = 0;
			
		}else if((datalen==1)&&(data[0]=='7')){
			/* 软件重启 */
			
			u0_printf("Rebooting ...\r\n");
			delay_1ms(100);
			/* 重启 */
			NVIC_SystemReset();
		}
	}
	
	/* 进行Xmodem IAP下载 */
	if(FlagGET(BootSta_Flag,IAP_XMODED_FLAG)){
		if((datalen==133)&&(data[0]==0x01)){
			FlagCLR(BootSta_Flag,IAP_XMODEC_FLAG);
			UpdataA.Xmodem_CRC = xmodem_CRC16(&data[3],128);
			
			
			if(UpdataA.Xmodem_CRC == data[131]*256+data[132]){
				/* CRC校验通过 */
				
				/* 接收次数 */
				UpdataA.xmodem_NB ++;
				/* 将Xmode数据加载到UpdataA.Updata_buff */
				memcpy(&UpdataA.Updata_buff[((UpdataA.xmodem_NB-1)%(GD32_PAGE_SIZE/128))*128],&data[3],128);
				
				if(UpdataA.xmodem_NB%(GD32_PAGE_SIZE/128) == 0){
					gd32_write_flash(GD32_A_SADDR + ((UpdataA.xmodem_NB/(GD32_PAGE_SIZE/128))-1)*GD32_PAGE_SIZE,\
									(uint32_t *)UpdataA.Updata_buff,\
									GD32_PAGE_SIZE);
				}
				
				/* 以16进制发送0x06 */
				u0_printf("\x06");
			}else{
				/* CRC校验不通过 */
				
				/* 以16进制发送0x15 */
				u0_printf("\x15");
			}
		}
		if((datalen==1)&&(data[0]==0x04)){
			u0_printf("\x06");
			if(UpdataA.xmodem_NB%(GD32_PAGE_SIZE/128) != 0){
					gd32_write_flash(GD32_A_SADDR + ((UpdataA.xmodem_NB/(GD32_PAGE_SIZE/128)))*GD32_PAGE_SIZE,\
									(uint32_t *)UpdataA.Updata_buff,\
									(UpdataA.xmodem_NB%(GD32_PAGE_SIZE/128))*128);
			}
		}
	}
}


void bootloader_brance(void)
{
	/* 判断是否进入命令行 */
	if(bootloader_enter(10) == 0){
	
		/* 不进入命令行 */
		/* 进行更新标志位判断 */
		if(OTA_Info.OTA_flag == OTA_SET_FLAG){
			u0_printf("OTA updata\r\n");
			BootSta_Flag |= UPDATA_A_FLAG;
			UpdataA.W25q64_blockNB = 0;
		}else{
			u0_printf("Jump to A partition\r\n");
			load_A(GD32_A_SADDR);
		}
	}
	
	/* 进入BootLoader命令行或者跳转A分区失败 */	
	u0_printf("Enter BootLoader command\r\n");
	/* 打印命令信息 */
	bootloader_info();
}

__asm void MSR_SP(uint32_t addr)
{
	MSR MSP, r0
	BX R14
}

void load_A(uint32_t addr)
{
	if(*(uint32_t *)addr >= GD32_RAM_SADDR && *(uint32_t *)addr <= GD32_RAM_EADDR){
		/* 保存 SP 指针 */
		MSR_SP(*(uint32_t *)addr);
		/* 保存 PC 指针 */
		LOAD_A = (load_a)*(uint32_t *)(addr + 4);
		bootloader_peripheral_clear();
		LOAD_A();
	}else{
		u0_printf("! Failed to jump to A partition\r\n");
	
	}
}

void bootloader_peripheral_clear(void)
{
	/* 用过什么清理什么 */
	usart_deinit(USART0);
	usart_deinit(USART2);
	gpio_deinit(GPIOA);
	gpio_deinit(GPIOB);
	spi_i2s_deinit(SPI0);
}

void at24cxx_read_OTA_info(void)
{
	/* 清理 OTA_Info */
	memset(&OTA_Info,0,OTA_InfoCB_SIZE);
	/* 存取更新标志位 OTA_Info */
	eeprom_buffer_read_timeout((uint8_t *)&OTA_Info,EEP_FIRST_PAGE,OTA_InfoCB_SIZE);

	u0_printf("%x\r\n",OTA_Info.OTA_flag);
}

void at24cxx_write_OTA_info(void)
{
	uint8_t *wptr;
	
	wptr = (uint8_t *)&OTA_Info;
	/* 不知道这里为什么不能一次性发16个 */
	for(uint8_t i=0; i<OTA_InfoCB_SIZE/8; i++){
		eeprom_page_write_timeout(wptr+i*8,i*8,8);
		delay_1ms(5);
	}
}


void w25q64_read_OTA_info(void)
{
	/* 此处会出现大小端问题 */
	memset(&OTA_Info,0,OTA_InfoCB_SIZE);
	//保存OTA_Info(待补充)
	w25q64_read((uint8_t *)&OTA_Info,0,OTA_InfoCB_SIZE);
}



