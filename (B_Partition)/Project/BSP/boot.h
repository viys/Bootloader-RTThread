#ifndef __BOOT_H
#define __BOOT_H

#include "stdint.h"

typedef void (*load_a)(void);

/* 选择分区 */
void bootloader_brance(void);
/* Bootloader命令行事件处理 */
void bootloader_event(uint8_t *data,uint16_t datalen);
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
/* 16位CRC校验函数 */
uint16_t xmodem_CRC16(uint8_t *data,uint16_t datalen);
/* 将外部FLAH中代码写入A区 */
void event_write_eflash_to_A(void);
void dbg_efaslh(void);

#endif /*__BOOT_H */
