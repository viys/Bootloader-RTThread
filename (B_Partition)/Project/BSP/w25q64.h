#ifndef __W25Q64_H
#define __W25Q64_H

#include "gd32f10x.h"

#define CS_ENABLE 		gpio_bit_reset(GPIOA,GPIO_PIN_4)
#define CS_DISENABLE 	gpio_bit_set(GPIOA,GPIO_PIN_4)

#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256
#define SPI_FLASH_BlockSize				64*1024

/*命令定义-开头*/
#define W25X_WriteEnable		      	0x06 
#define W25X_WriteDisable		      	0x04 
#define W25X_ReadStatusReg		    	0x05 
#define W25X_WriteStatusReg		    	0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		     	0x0B 
#define W25X_FastReadDual		      	0x3B 
#define W25X_PageProgram		  	    0x02 
#define W25X_BlockErase			  	    0xD8 
#define W25X_SectorErase		  	    0x20 
#define W25X_ChipErase			     	0xC7 
#define W25X_PowerDown			 	    0xB9 
#define W25X_ReleasePowerDown	  	  	0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   		0x90 
#define W25X_JedecDeviceID		    	0x9F

/* WIP(busy)标志,FLASH内部正在写入 */
#define WIP_Flag                  0x01
#define Dummy_Byte                0xFF

/* w25q64初始化 */
void w25q64_init(void);
/* w25q64擦除64k */
void w25q64_erase64k(uint8_t blockNB);
/* w25q64 page 写 */
void w25q64_page_write(uint8_t *wbuff,uint16_t pageNB);
/* w25q64 读数据 */
void w25q64_read(uint8_t *rbuff,uint32_t addr,uint32_t datalen);
/* 测试 w25q64 */
void w25q64_test(void);
void w25q64test(void);
#endif /* __W25Q64_H */
