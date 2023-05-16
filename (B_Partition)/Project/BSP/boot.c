#include "boot.h"
#include "main.h"
#include "uart.h"
#include "fmc.h"
#include "at24cxx.h"
#include "string.h"
#include "w25q64.h"
#include "systick.h"

load_a LOAD_A;

void bootloader_brance(void)
{
	/* OTA_SET_FLAG 设为0x11111111避免大小端问题 */
	if(OTA_Info.OTA_flag == OTA_SET_FLAG){
		u0_printf("OTA更新\r\n");
	
	}else{
		u0_printf("跳转A分区\r\n");
//		load_A(GD32_A_SADDR);
	}
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

//	u0_printf("%s\r\n",&OTA_Info.OTA_flag);
}


void w25q64_read_OTA_info(void)
{
	/* 此处会出现大小端问题 */
	memset(&OTA_Info,0,OTA_InfoCB_SIZE);
	//保存OTA_Info(待补充)
	w25q64_read((uint8_t *)&OTA_Info,0,OTA_InfoCB_SIZE);
	
	BigLittleSwap32(OTA_Info.OTA_flag);
	
//	u0_printf("%s\r\n",&OTA_Info.OTA_flag);
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

