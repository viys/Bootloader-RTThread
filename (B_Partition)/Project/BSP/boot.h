#ifndef __BOOT_H
#define __BOOT_H

#include "stdint.h"

typedef void (*load_a)(void);

/* 命令行入口 */
uint8_t bootloader_enter(uint8_t timeout);
/* 输出Bootloader命令行信息 */
void bootloader_info(void);
/* 串口0输入检测 */
void u0_input_detection(void);
/* 串口0发送Xmodem开始传输信号 */
void u0_printf_C(void);
/* 选择分区 */
void bootloader_branch(void);
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


#endif /*__BOOT_H */
