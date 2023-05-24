# 版本说明

## viys

### A区文件配置:

1. 修改**keil**烧录起始地址为`0x08005000`.

2. 修改` system_gd32f10x.c`对应部分.

   ```c
   #define VECT_TAB_OFFSET  (uint32_t)0x000            /* vector table base offset */
   ⏬
   #define VECT_TAB_OFFSET  (uint32_t)0x5000            /* vector table base offset */
   ```

### B区文件配置:

1. 修改**keil**烧录结束地址为`0x4FFF`.

2. `main.h`文件存放芯片的特殊信息,更换芯片需修改.

   ```c
   /*
    * GD32 RAM	ROM  bank0_size bank1_size
    * 		64k	512k 	2k			4k
    */
   ```


### 升级传输文件格式

`.bin`：keil文件转换命令`fromelf.exe --bin -o .\rtt_gd103.bin .\rtt_gd103.axf`

### 版本号格式

`VER-1.0.0-2023/5/30-%00:%08`(26个字符)

## FLASH存储说明

FLASH分为10个FIRM_Block区,1~9区目前可以存储不同的代码,每块为64k.

## 使用说明

待补充,我要吃饭去了❤