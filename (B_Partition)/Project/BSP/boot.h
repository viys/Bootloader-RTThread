#ifndef __BOOT_H
#define __BOOT_H

#include "stdint.h"

typedef void (*load_a)(void);

/* 选择分区 */
void bootloader_brance(void);
/* 保存 SP 指针 */
__asm void MSR_SP(uint32_t addr);
/* 保存 PC 指针 */
void load_A(uint32_t addr);
/* 跳转A区前外设寄存器清理 */
void bootloader_peripheral_clear(void);
/* nflash 查看更新标志位 */
void w25q64_read_OTA_info(void);
/* eeprom 查看更新标志位 */
void at24cxx_read_OTA_info(void);
/* eeprom 写入更新标志位 */
void at24cxx_write_OTA_info(void);
/* 查看将读取的 OTA_flag 值 */
void print_OTA_update_value(uint8_t sw);


#endif /*__BOOT_H */
