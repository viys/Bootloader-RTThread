#ifndef __UART_H
#define __UART_H

#include "rtthread.h"
#include "drv_uart.h"


rt_err_t dbguart_init(rt_device_t dev);
rt_err_t dbguart_open(rt_device_t dev, rt_uint16_t oflag);
rt_err_t dbguart_close(rt_device_t dev);
rt_size_t dbguart_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
rt_size_t dbguart_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
rt_err_t dbguart_control(rt_device_t dev, int cmd, void *args);

#endif /* __UART_H */
