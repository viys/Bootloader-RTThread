#ifndef __UART_H
#define __UART_H

#include "gd32f10x.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

#define U0_RX_SIZE	2048
#define U0_TX_SIZE	2048
#define U0_RX_MAX	256

#define U2_RX_SIZE	2048
#define U2_TX_SIZE	2048
#define U2_RX_MAX	256

#define URxNUM		10

/* uart control blok */
typedef struct{
	/* s用于标记起始位置 */
	uint8_t *start;
	/* e用于标记结束位置 */
	uint8_t *end;
}UCB_URxBuffPtr;

/* 串口控制区指针结构体 */
typedef struct{
	/* 积累接受数据量 */
	uint16_t URxCounter;
	/* se指针对于结构体数组 */
	UCB_URxBuffPtr URxDataPtr[URxNUM];
	/* IN指针用于标记接收数据 */
	UCB_URxBuffPtr *URxDataIN;
	/* OUT指针用于提取接受的数据 */
	UCB_URxBuffPtr *URxDataOUT;
	/* IN 和 OUT 指针的结尾标志 */
	UCB_URxBuffPtr *URxDataEND;
}UCB_CB;

extern UCB_CB U0CB;
extern uint8_t U0_RxBuff[U0_RX_SIZE];
extern UCB_CB U2CB;
extern uint8_t U2_RxBuff[U2_RX_SIZE];

/* BootLoader 串口初始化 */
/* uart0外设初始化 */
void uart0_init(uint32_t bandrate);
/* uart0指针初始化 */
void u0rx_ptr_init(void);
/* uart0 printf重定向 */
void u0_printf(char *format,...);

/* 透传模块 串口初始化 */
/* uart2外设初始化 */
void uart2_init(uint32_t bandrate);
/* uart2指针初始化 */
void u2rx_ptr_init(void);
/* uart2 printf重定向 */
void u2_printf(char *format,...);

/* uart0 transmit测试函数 */
void u0_transmit_test(void);
	
#endif /* __UART_H */
