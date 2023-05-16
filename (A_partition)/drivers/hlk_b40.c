#include "hlk_b40.h"

#define DBG_TAG "hlk_b40"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

void b40_sleep_ctrl(rt_base_t pin)
{
//	rt_pin_mode(pin,PIN_MODE_OUTPUT);//应放在设备注册那里

}


rt_err_t b40_init(rt_device_t dev)
{
	if(B40_RXD_PIN != -1 && B40_TXD_PIN != -1){
		//此处使用dbg_uart
	}
	if(B40_RESET_CTRL != -1){
		rt_pin_init(B40_RESET_CTRL,PIN_MODE_OUTPUT);
		rt_pin_write(B40_RESET_CTRL,PIN_LOW);
	}
	if(B40_TS_SW_CTRL != -1){
		rt_pin_init(B40_TS_SW_CTRL,PIN_MODE_OUTPUT);
		rt_pin_write(B40_RESET_CTRL,PIN_HIGH);
	}
	if(B40_CONET_STATUS != -1){
		rt_pin_init(B40_CONET_STATUS,PIN_MODE_INPUT);	
	}
	if(B40_SLEEP_CTRL != -1){
		rt_pin_mode(B40_SLEEP_CTRL,PIN_MODE_OUTPUT);
		rt_pin_write(B40_RESET_CTRL,PIN_LOW);
	}
	if(B40_SLEEP_STATUS != -1){
		rt_pin_init(B40_SLEEP_STATUS,PIN_MODE_INPUT);
	}
	return RT_EOK;
}


rt_err_t b40_open(rt_device_t dev, rt_uint16_t oflag)
{
	
	return RT_EOK;
}

rt_err_t b40_close(rt_device_t dev)
{
	
	return RT_EOK;
}

rt_size_t b40_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
	
	return RT_EOK;
}

rt_size_t b40_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
	
	return RT_EOK;
}

rt_err_t b40_control(rt_device_t dev, int cmd, void *args)
{
	
	return RT_EOK;
}
int rt_b40_init(void)
{
	rt_err_t err;
	rt_device_t b40_dev;
	
	b40_dev = rt_device_create(RT_Device_Class_NetIf, 32);
	if(b40_dev == RT_NULL){
		LOG_E("rt_device_create[hlk-b40] failed...\n");
		return -RT_ENOMEM;
	}
	
	b40_dev->init = b40_init;
	b40_dev->open = b40_open;
	b40_dev->close = b40_close;
	b40_dev->read = b40_read;
	b40_dev->write = b40_write;
	b40_dev->control = b40_control;
	
	err = rt_device_register(b40_dev, "hlk-b40", RT_DEVICE_FLAG_RDWR);
	if(err != RT_EOK){
		LOG_E("rt_device_register[hlk-b40] failed...\n");
		return -RT_ERROR;
	}

	return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_b40_init)
