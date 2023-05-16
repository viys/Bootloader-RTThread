#include "led.h"

#define DBG_TAG "led"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>


/* LED初始化函数 */
rt_err_t led_init(rt_device_t dev)
{
	rt_pin_init(LED0_PIN, PIN_MODE_OUTPUT);
	return RT_EOK;
}

/* 打开LED设备函数 */
rt_err_t led_open(rt_device_t dev, rt_uint16_t oflag)
{
	LOG_D("led_open success...\n");
	return RT_EOK;
}

/* 关闭LED设备函数 */
rt_err_t led_close(rt_device_t dev)
{
	LOG_D("led_close success...\n");
	return RT_EOK;
}

/* 读取LED设备状态函数 */
rt_size_t led_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
	FlagStatus led_status;
	led_status = rt_pin_read(LED0_PIN);
	rt_kprintf("led status is %d",led_status);
	return RT_EOK;
}

/* 改变LED设备状态函数 */
rt_size_t led_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
	
	return RT_EOK;
}

/* LED设备控制函数 */
rt_err_t led_control(rt_device_t dev, int cmd, void *args)
{
	switch(cmd){
		case LED_ON:
			rt_pin_write(LED0_PIN, PIN_LOW);
			break;
		case LED_OFF:
			rt_pin_write(LED0_PIN, PIN_HIGH);
			break;
		default :
			break;
	
	}
	
	return RT_EOK;
}

int rt_led_init(void)
{
	rt_err_t err;
	rt_device_t led_dev;
	
	led_dev = rt_device_create(RT_Device_Class_Miscellaneous, 32);
	if(led_dev == RT_NULL){
		LOG_E("rt_device_create[led] failed...\n");
		return -RT_ENOMEM;
	}
	
	led_dev->init = led_init;
	led_dev->open = led_open;
	led_dev->close = led_close;
	led_dev->read = led_read;
//	led_dev->write = led_write;
	led_dev->control = led_control;
	
	err = rt_device_register(led_dev, "led", RT_DEVICE_FLAG_RDWR);
	if(err != RT_EOK){
		LOG_E("rt_device_register[led] failed...\n");
		return -RT_ERROR;
	}
	
	
	return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_led_init)
