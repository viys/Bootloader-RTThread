#ifndef __SPI_H
#define __SPI_H

#include "gd32f10x.h"

/* spi初始化函数 */
void spi0_init(void);
/* spi读写一个字节 */
uint8_t spi0_rw_byte(uint8_t txd);
/* spi写函数 */
void spi0_write(uint8_t *wdata,uint16_t datalen);
/* spi读函数 */
void spi0_read(uint8_t *rdata,uint16_t datalen);

#endif /* __SPI_H */
