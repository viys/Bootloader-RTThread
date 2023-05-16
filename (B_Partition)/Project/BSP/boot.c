#include "boot.h"
#include "main.h"
#include "uart.h"
#include "fmc.h"

load_a LOAD_A;

void bootloader_brance(void)
{
	/* OTA_SET_FLAG 设为0x11111111避免大小端问题 */
	if(OTA_Info.OTA_flag == OTA_SET_FLAG){
		u0_printf("OTA更新\r\n");
	
	}else{
		u0_printf("跳转分区\r\n");
		load_A(GD32_A_SADDR);
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
