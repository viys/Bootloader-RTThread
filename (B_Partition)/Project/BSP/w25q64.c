#include "w25q64.h"
#include "spi.h"
#include "uart.h"
#include "systick.h"
#include "main.h"
#include "string.h"

void w25q64_init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_4);
	CS_DISENABLE;
	spi0_init();
}

void w25q64_waitbusy(void)
{
	uint8_t res;
	do{
		CS_ENABLE;
		spi0_rw_byte(W25X_ReadStatusReg);
		res = spi0_rw_byte(Dummy_Byte);
		CS_DISENABLE;
	}while((res&W25X_WriteStatusReg) == WIP_Flag);
	
}

void w25q64_enable(void)
{
	w25q64_waitbusy();
	CS_ENABLE;
	spi0_rw_byte(W25X_WriteEnable);
	CS_DISENABLE;
}

void w25q64_erase64k(uint8_t blockNB)
{
	uint8_t wdata[4];
	
	wdata[0] = W25X_BlockErase;
	wdata[1] = (blockNB*64*1024) >> 16;
	wdata[2] = (blockNB*64*1024) >> 8;
	wdata[3] = (blockNB*64*1024) >> 0;
	
	w25q64_waitbusy();
	w25q64_enable();
	CS_ENABLE;
	spi0_write(wdata,4);
	CS_DISENABLE;
	w25q64_waitbusy();
}

void w25q64_page_write(uint8_t *wbuff,uint16_t pageNB)
{
	uint8_t wdata[4];
	
	wdata[0] = W25X_PageProgram;
	wdata[1] = (pageNB*SPI_FLASH_PageSize) >> 16;
	wdata[2] = (pageNB*SPI_FLASH_PageSize) >> 8;
	wdata[3] = (pageNB*SPI_FLASH_PageSize) >> 0;
	
	w25q64_waitbusy();
	w25q64_enable();
	CS_ENABLE;
	spi0_write(wdata,4);
	spi0_write(wbuff,SPI_FLASH_PerWritePageSize);
	CS_DISENABLE;
}

void w25q64_read(uint8_t *rbuff,uint32_t addr,uint32_t datalen)
{
	uint8_t wdata[4];
	
	wdata[0] = W25X_ReadData;
	wdata[1] = (addr) >> 16;
	wdata[2] = (addr) >> 8;
	wdata[3] = (addr) >> 0;
	
	w25q64_waitbusy();
	CS_ENABLE;
	spi0_write(wdata,4);
	spi0_read(rbuff,datalen);
	CS_DISENABLE;
}

void w25q64_test(void)
{
	uint8_t wdata[256];

	
	w25q64_erase64k(0);
	
	for(uint16_t i=0; i<4; i++){
		for(uint16_t j=0; j<4; j++){
			wdata[j] = i;
		}
		w25q64_page_write(wdata,i);
	}
	
	delay_1ms(50);
	w25q64test();
}

void w25q64test(void)
{
	uint8_t rdata[256];
	for(uint16_t i=0; i<4; i++){
		w25q64_read(rdata,i*4.,256);
		for(uint16_t j=0; j<4; j++){
			u2_printf("地址%d=%x\r\n",i*4+j,rdata[j]);
		
		}
	}
}

