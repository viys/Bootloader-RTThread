#ifndef __LED_H
#define __LED_H

#include "rtthread.h"
#include "drv_pin.h"


/* LED设备开关宏定义 */
#define LED_OFF	0x00
#define LED_ON	0x01

/* LED引脚定义 */
#define LED0_PIN    GET_PIN(C, 13)

rt_err_t led_init(rt_device_t dev);
rt_err_t led_open(rt_device_t dev, rt_uint16_t oflag);
rt_err_t led_close(rt_device_t dev);
rt_size_t led_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
rt_size_t led_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
rt_err_t led_control(rt_device_t dev, int cmd, void *args);
int rt_led_init(void);

#endif /* __LED_H */
