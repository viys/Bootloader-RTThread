#ifndef __DRV_UART_H
#define __DRV_UART_H

#include "gd32f10x.h"
#include "stdio.h"

#define DEBUG_USART	USART0

void dbgusart_config(void);

#endif /* __DRV_UART_H */
