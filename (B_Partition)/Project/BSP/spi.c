#include "spi.h"

void spi0_init(void)
{
	spi_parameter_struct SPI_Init_Struct;
	rcu_periph_clock_enable(RCU_SPI0);
	rcu_periph_clock_enable(RCU_GPIOA);
	
	/* connect PA5 to SPI0_SCK */
    /* connect PA6 to SPI0_MIS0 */
	/* connect PA7 to SPI0_MOSI */
	gpio_init(GPIOA,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_5|GPIO_PIN_7);
	gpio_init(GPIOA,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO_PIN_6);
	
	spi_i2s_deinit(SPI0);
	SPI_Init_Struct.device_mode = SPI_MASTER;
	SPI_Init_Struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
	SPI_Init_Struct.frame_size = SPI_FRAMESIZE_8BIT;
	SPI_Init_Struct.nss = SPI_NSS_SOFT;
	SPI_Init_Struct.endian = SPI_ENDIAN_MSB;
	SPI_Init_Struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
	SPI_Init_Struct.prescale = SPI_PSC_2;
	spi_init(SPI0,&SPI_Init_Struct);
	
	spi_enable(SPI0);
}

uint8_t spi0_rw_byte(uint8_t txd)
{
	while(spi_i2s_flag_get(SPI0,SPI_FLAG_TBE) != 1);
	spi_i2s_data_transmit(SPI0,txd);
	while(spi_i2s_flag_get(SPI0,SPI_FLAG_RBNE) != 1);
	return spi_i2s_data_receive(SPI0);
}

void spi0_write(uint8_t *wdata,uint16_t datalen)
{
	for(uint16_t i=0; i<datalen; i++){
		spi0_rw_byte(wdata[i]);
	}
}

void spi0_read(uint8_t *rdata,uint16_t datalen)
{
	for(uint16_t i=0; i<datalen; i++){
		rdata[i] = spi0_rw_byte(0xff);
	}
}








