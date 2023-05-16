/*
 * @Description: 海凌科B40蓝牙模块驱动
 * @Author: viys
 * @LastEditors: viys
 * @Date: 2023-5-9 11:07:41
 * @LastEditTime: 2023-5-9 11:07:41
 */

#ifndef __HLK_B40_H
#define __HLK_B40_H

#include "gd32f10x.h"

#define B40_ID				test_ble

#define B40_RXD_PIN			0				//蓝牙输入引脚
#define B40_TXD_PIN			0				//蓝牙输入引脚
#define B40_RESET_CTRL		0				//蓝牙复位
#define B40_TS_SW_CTRL		0				//蓝牙透传模式切换
#define B40_CONET_STATUS	0				//蓝牙连接状态指示

//AT指令
//二阶拼接
#define B40_CONTACT(x,y) 	x##y
#define B40_CONTACT2(x,y) 	B40_CONTACT(x,y)

//二阶转义
#define B40_STR(x) 			#x   //转字符串
#define B40_STR2(x) 		B40_STR(x)

//AT多参控制
#define B40_CRTL(x,y)		B40_STR2(B40_CONTACT2(x,y))

/*
 *	查看蓝牙软件版本号
 *	参数范围:只读(?)
 */
#define B40_VER				AT+VER=?		//软件版本号

/*
 *	查看蓝牙MAC地址
 *	参数范围:只读(?)
 */
#define B40_MAC 			AT+MAC=?		//MAC地址

/*
 *	恢复蓝牙默认配置
 *	参数范围:1
 */
#define B40_DEFAULT			AT+DEFAULT=1	//恢复默认配置

/*
 *	重启蓝牙模块
 *	参数范围:1
 */
#define B40_REBOOT			AT+REBOOT=1		//重启模块

/*
 *	蓝牙恢复透传模式
 *	参数范围:1
 */
#define B40_TS				AT+TS=1			//恢复透传模式

/*
 *	查看或修改蓝牙名称
 *	参数范围:?,最多25个字符
 *	默认值:HLK_B40_****
 */ 
#define B40_NAME			AT+NAME=		//蓝牙名称

/*
 *	查看或修改蓝牙波特率
 *	参数范围:?,1200,2400,4800,9600,14400,19200,38400,57600, 115200,230400,460800,921600
 *	默认值:115200
 */ 
#define B40_BAND			AT+BAND=		//蓝牙波特率

/*	
 *	查看或修改蓝牙发射功率
 *	参数范围:?,1~18(18个等级)
 *	默认值:8
 *	越小传输距离越短，功耗越低；越大传输距离越远，功耗越大
 */ 
#define B40_RFPOWER			AT+RFPOWER=		//蓝牙发射功率

/*
 *	查看或使能蓝牙休眠
 *	参数范围:?,0(禁用sleep),1(使能sleep)
 *	默认值:0
 *	使能后模块根据SleepEn输入引脚电平的控制自动进入休眠状态
 */ 
#define B40_SLEEPEN			AT+SLEEPEN=		//蓝牙休眠使能

/*
 *	查看或设置蓝牙连接间隔
 *	参数范围:?,6～3200(单位1.25ms,即7.5～4000ms)
 *	默认值:12
 *	越小收发越快，功耗越大；越大收发越慢，延时越大，功耗越低；
 */ 
#define B40_CONNI			AT+CONNI=		//蓝牙连接间隔

/*	
 *	查看或修改蓝牙广播间隔
 *	参数范围:?,80,160,320,800,1600,3200 (单位625us,以上均为建议值)
 *	默认值：800
 */ 
#define B40_ADVI			AT+ADVI=		//蓝牙广播间隔

/*
 *	查看或修改蓝牙广播数据
 *	参数范围:?,16进制数(字符个数为2的倍数,最多52个16进制数)
 *	默认值：无
 */ 
#define B40_ADVDATA			AT+ADVDATA=		//自定义广播数据

/*	查看或修改蓝牙角色
 *	参数范围:?,1(从机),2(主机)
 *	默认值:1
 */ 
#define B40_ROLE			AT+ROLE=		//蓝牙角色

/*
 *	查看或修改蓝牙配对绑定使能
 *	参数范围:?,0(无需配对绑定),1(需要配对绑定)
 *	默认值:0
 */ 
#define B40_ENCRYPT			AT+ENCRYPT=		//配对绑定使能

/*
 *	查看或修改蓝牙配对码
 *	参数范围:6位整数
 *	默认值：123456
 */ 
#define B40_PINCODE			AT+PINCODE=		//配对码

/*
 *	查看或修改主机模式下连接扫描方式
 *	参数范围:?,0(通过MAC地址连接),1(通过蓝牙名称连接)
 *	默认值：0
 */ 
#define B40_SCANMODE		AT+SCANMODE=	//主机模式下连接扫描方式

/*
 *	查看或修改目的蓝牙MAC地址
 *	参数范围:?,MAC地址(12个16进制数)
 */ 
#define B40_PEERMAC			AT+PEERMAC=		//模块做主机时,自动去连接的从机的MAC地址

/*
 *	查看或修改目的蓝牙名称
 *	参数范围:最多25个字符
 */ 
#define B40_PEERNAME		AT+PEERNAME=	//模块做主机时,自动去连接的从机的蓝牙名称

/*
 *	查看和设置OTA和空中配置的访问密码
 *	参数范围:最多8个字符
 *	默认值:HiLink
 */
#define B40_AUTHPWG			AT+AUTHPWG=		//OTA和空中配置的访问密码

/*
 *	查询当前蓝牙连接的设备信息
 *	参数范围:只读(?)
 *	应答内容包括:当前连接的设备个数每个设备的Role,MAC
 */ 
#define B40_CONNSTATE		AT+CONNSTATE=	//查询当前蓝牙连接的设备信息

/*
 *	查看和修改蓝牙做主机时的重连间隔
 *	参数范围:?,0(代表仅启动时尝试连接一次不重连),1～60(连接断开后间隔指定秒数后自动重连)
 *	默认值:5
 *	只可取整数,单位s
 */ 
#define B40_RECONNI			AT+RECONNI=		//模块做主机时，蓝牙自动重连间隔

/*	
 *	查看或修改蓝牙透传服务UUIDS
 *	参数范围:?,32个16进制数
 *	默认值:0000fff000001000800000805f9b34fb
 */ 
#define B40_UUIDS			AT+UUIDS=		//蓝牙透传服务UUID

/*
 *	查看或修改蓝牙透传服务UUIDR
 *	参数范围:?,32个16进制数
 *	默认值:0000fff100001000800000805f9b34fb
 *	透传服务中的Read特征UUID(模块发,APP收)
 */ 
#define B40_UUIDR			AT+UUIDR=		//透传服务中的Read特征UUID(模块发,APP收)

/*
 *	查看或修改蓝牙透传服务UUIDW
 *	参数范围:?,32个16进制数
 *	默认值:0000fff200001000800000805f9b34fb
 *	透传服务中的Write特征UUID(APP发,模块收)
 */ 
#define B40_UUIDW			AT+UUIDW=		//透传服务中的Write特征UUID(APP发,模块收)

/*	
 *	主动断开当前和模块的所有蓝牙连接
 *	参数范围:1
 */ 
#define B40_DISCONN			AT+DISCONN=		//主动断开当前和模块的所有蓝牙连接

/*
 *	查看或修改蓝牙广播使能
 *	参数范围:?,0(禁用模块的蓝牙广播),1(使能模块的蓝牙广播)
 *	默认值：1
 *	禁用后模块不能被手机或其他蓝牙主机扫描到
 */ 
#define B40_ADVEN			AT+ADVEN=		//模块蓝牙广播使能

/*
 *	查看或修改从机模式下蓝牙的最大允许连接数
 *	参数范围:?,整数
 *	默认值10
 */ 
#define B40_MAXCONN			AT+MAXCONN=		//从机模式下时,允许的最大蓝牙连接数

/* 蓝牙初始化函数 */
void b40_init(void);


#endif /* __HLK_B40_H */












