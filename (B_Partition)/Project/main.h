#ifndef __MAIN_H
#define __MAIN_H

#include "stdint.h"
#include "fmc.h"

/*
 * GD32 RAM	ROM  bank0_size bank1_size
 * 		64k	512k 	2k			4k
 */

#define GD32_RAM_SADDR		0x20000000
#define GD32_RAM_EADDR		GD32_RAM_SADDR + GD32_RAM_SIZE - 1
#define GD32_RAM_SIZE		64*1024
#define GD32_ROM_SIZE		512*1024

#define GD32_FLASH_SADDR	0x08000000										//FLASH起始地址
#define GD32_PAGE_SIZE		Flash_Page_Size_Bank0							//扇区大小
#define GD32_PAGE_NUM		GD32_ROM_SIZE/GD32_PAGE_SIZE					//总扇区个数
#define	GD32_B_PAGE_NUM		10												//B区扇区个数
#define GD32_A_PAGE_NUM		GD32_PAGE_NUM - GD32_B_PAGE_NUM					//A区扇区个数
#define GD32_A_SPAGE		GD32_B_PAGE_NUM									//A区起始扇区编号
#define GD32_A_SADDR		GD32_FLASH_SADDR + GD32_A_SPAGE*GD32_PAGE_SIZE	//A区起始地址

#define OTA_SET_FLAG		0x01020304	//需要OTA更新A区对比位

/* 状态标志位 */
#define UPDATA_A_FLAG		0x00000001	//A区需要更新状态位
#define IAP_XMODEC_FLAG		0x00000002	//串口IAP开始传输状态位
#define IAP_XMODED_FLAG		0x00000004	//串口IAP数据处理状态位
#define SET_VERSION_FLAG	0x00000008	//设置版本号状态位
#define WRITE_E_FLASH_FLAG	0x00000010	//向外部FLASH写程序
#define FLASH_XMODEM_FALG	0x00000020	//向外部FLASH传输文件

/* uint16_t 大小端互换 */
#define BigLittleSwap16(A)  ((((uint16_t)(A) & 0xff00) >> 8) | \
							(((uint16_t)(A) & 0x00ff) << 8))
 
/* uint32_t 大小端互换 */
#define BigLittleSwap32(A)  ((((uint32_t)(A) & 0xff000000) >> 24) | \
							(((uint32_t)(A) & 0x00ff0000) >> 8) | \
							(((uint32_t)(A) & 0x0000ff00) << 8) | \
							(((uint32_t)(A) & 0x000000ff) << 24))

#define FlagSET(Flag,bit)	(Flag |= bit)	//Flag置位
#define FlagCLR(Flag,bit)	(Flag &= ~bit)	//Flag清位
#define FlagGET(Flag,bit)	(Flag & bit)	//Flag获取

typedef struct{
	/* 更新标志位,等于 UPDATA_A_FLAG 时切换OTA更新A区分支 */
	uint32_t OTA_flag;
	/* 不同块中固件的长度,0号成员固定为OTA的大小 */
	uint32_t Firelen[11];
	/* 固件版本号 */
	uint8_t OTA_ver[32];
}OTA_InfoCB;
#define OTA_InfoCB_SIZE	sizeof(OTA_InfoCB)

typedef struct{
	uint8_t Updata_buff[GD32_PAGE_SIZE];
	uint32_t W25q64_blockNB;
	uint32_t Xmodem_Timer;
	uint32_t xmodem_NB;
	uint32_t Xmodem_CRC;
}UpDataA_CB;
#define UPDATAA_CB_SIZE	sizeof(UpDataA_CB)

extern OTA_InfoCB OTA_Info;
extern UpDataA_CB UpdataA;
extern volatile uint32_t BootSta_Flag;

#endif /* __MAIN_H */

