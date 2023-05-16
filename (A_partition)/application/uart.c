#include "uart.h"

#define DBG_TAG "uart"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

/* 挂载UARTDBG设备 */
#ifdef RT_USING_CONSOLE

/* UARTDBG初始化函数 */
rt_err_t uartdbg_init(rt_device_t dev)
{
	dbgusart_config();
	return RT_EOK;
}

/* 打开UARTDBG设备函数 */
rt_err_t uartdbg_open(rt_device_t dev, rt_uint16_t oflag)
{
	
	return RT_EOK;
}

/* 关闭UARTDBG设备函数 */
rt_err_t uartdbg_close(rt_device_t dev)
{
	
	return RT_EOK;
}

/* 读取UARTDBG设备状态函数 */
rt_size_t uartdbg_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
	
	return RT_EOK;
}

/* 改变UARTDBG设备状态函数 */
rt_size_t uartdbg_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
	
	return RT_EOK;
}

/* UARTDBG设备控制函数 */
rt_err_t uartdbg_control(rt_device_t dev, int cmd, void *args)
{
	
	return RT_EOK;
}

int rt_uartdbg_init(void)
{
	rt_err_t err;
	rt_device_t uartdbg_dev;
	
	uartdbg_dev = rt_device_create(RT_Device_Class_Char, 0);
	if(uartdbg_dev == RT_NULL){
		LOG_E("rt_device_create[led] failed...\n");
		return -RT_ENOMEM;
	}
	
	uartdbg_dev->init = uartdbg_init;
	uartdbg_dev->open = uartdbg_open;
	uartdbg_dev->close = uartdbg_close;
	uartdbg_dev->read = uartdbg_read;
	uartdbg_dev->write = uartdbg_write;
	uartdbg_dev->control = uartdbg_control;
	
	err = rt_device_register(uartdbg_dev, "uartdbg", RT_DEVICE_FLAG_RDWR);
	if(err != RT_EOK){
		LOG_E("rt_device_register[uartdbg] failed...\n");
		return -RT_ERROR;
	}
	
	dbgusart_config();
	return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_uartdbg_init)

#endif /* RT_USING_CONSOLE */
