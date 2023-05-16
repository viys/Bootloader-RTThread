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

#endif /*__BOOT_H */
