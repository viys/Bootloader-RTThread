#include "fmc.h"
#include "uart.h"

void gd32_erase_flash(uint16_t start,uint16_t num)
{
	
	/* 解锁flash */
	fmc_unlock();
	for(uint16_t i=0; i<num; i++){
		fmc_page_erase((FLASH_STAT_ADDR + start*Flash_Page_Size_Bank0) + Flash_Page_Size_Bank0*i);
	}
	/* 锁定flash */
	fmc_lock();
}

void gd32_write_flash(uint32_t saddr,uint32_t *wdata,uint32_t wnum)
{
	/* 解锁flash */
	fmc_unlock();
	/* 写入数据 */
	while(wnum){
		fmc_word_program(saddr,*wdata);
		wnum -= 4;
		saddr += 4;
		wdata ++;
	}
	/* 锁定flash */
	fmc_lock();
}

void fmc_test(void)
{
	uint32_t wbuff[1024];
	
	for(uint32_t i=0; i<1024; i++){
		wbuff[i] = 0x12345678;
	}
	
	gd32_erase_flash(60,2);
	gd32_write_flash(60*1024+FLASH_STAT_ADDR,wbuff,1024*4);
	
	for(uint16_t i=0; i<1024; i++){
		u0_printf("t1\r\n");
		u0_printf("%x\r\n",*(uint32_t *)((60*1024+FLASH_STAT_ADDR)+(i*4)));
	}

}

