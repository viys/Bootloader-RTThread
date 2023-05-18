#ifndef __FMC_H
#define __FMC_H

#include "gd32f10x.h"

#define FLASH_STAT_ADDR	0x08000000

/* 对于大于512k的芯片,有两片闪存,前512k存在bank0,后续的容量存在bank1 */
#if defined (GD32F10X_MD)

#define Flash_Page_Size_Bank0 1024

#elif defined (GD32F10X_HD) || defined (GD32F10X_XD) || defined (GD32F10X_CL)

#define Flash_Page_Size_Bank0 2048
#define Flash_Page_Size_Bank1 4096

#endif /* define GD32F10x */

/* gd32 flash 擦除函数 */
void gd32_erase_flash(uint32_t start,uint16_t num);
/* gd32 flash 写函数 */
void gd32_write_flash(uint32_t saddr,uint32_t *wdata,uint32_t wnum);
/* fmc 测试函数 */
void fmc_test(void);

#endif /* __FMC_H */
