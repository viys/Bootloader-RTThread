#include "drv_pin.h"

/* 引脚初始化
此函数报错不影响时钟的正常打开,若想不让报错注释掉rcu_periph_clock_enable(PIN_RCU(pin));
打开RCU_REG_VAL(PIN_RCU(pin)) |= BIT(RCU_BIT_POS(PIN_RCU(pin)));的注释即可.
*/
rt_err_t rt_pin_init(rt_base_t pin, rt_base_t mode)
{
	rcu_periph_clock_enable(PIN_RCU(pin));
//	RCU_REG_VAL(PIN_RCU(pin)) |= BIT(RCU_BIT_POS(PIN_RCU(pin)));
	rt_pin_mode(pin, mode);
//	gpio_bit_reset(GPIOC, GPIO_PIN_13);
	return RT_EOK;
}

/* 设置引脚模式 */
void rt_pin_mode(rt_base_t pin, rt_base_t mode)
{
	rt_base_t mode_tmp = RT_NULL;
	switch(mode){
		case PIN_MODE_OUTPUT:
			mode_tmp = GPIO_MODE_OUT_PP;
			break;
		case PIN_MODE_INPUT:
			mode_tmp = GPIO_MODE_IN_FLOATING;
			break;
		case PIN_MODE_INPUT_PULLUP:
			mode_tmp = GPIO_MODE_IPU;
			break;
		case PIN_MODE_INPUT_PULLDOWN:
			mode_tmp = GPIO_MODE_IPD;
			break;
		case PIN_MODE_OUTPUT_OD:
			mode_tmp = GPIO_MODE_OUT_OD;
			break;
		default :
			RT_ASSERT(PIN_OPS_ERR);
			break;
	}
	
	gpio_init(PIN_GDPORT(pin), mode_tmp, GPIO_OSPEED_50MHZ, PIN_GDPIN(pin));
}

/* 设置引脚电平 */
void rt_pin_write(rt_base_t pin, rt_base_t value)	
{
	
	switch(value){
		case PIN_LOW:
			gpio_bit_reset(PIN_GDPORT(pin), PIN_GDPIN(pin));
			break;
		case PIN_HIGH:
			gpio_bit_set(PIN_GDPORT(pin), PIN_GDPIN(pin));
			break;
		default :
			RT_ASSERT(PIN_OPS_ERR);
			break;
	}
	
}

/* 读取引脚电平 */
int rt_pin_read(rt_base_t pin)
{
	return gpio_input_bit_get(PIN_GDPORT(pin), PIN_GDPIN(pin));
}

/* 绑定引脚中断回调函数 */
rt_err_t rt_pin_attach_irq(rt_int32_t pin, rt_uint32_t mode,
                             void (*hdr)(void *args), void  *args)
{

	return -RT_ENOSYS;
}

/* 脱离引脚中断回调函数 */
rt_err_t rt_pin_detach_irq(rt_int32_t pin)
{

	return -RT_ENOSYS;
}

/* 使能引脚中断 */
rt_err_t rt_pin_irq_enable(rt_base_t pin, rt_uint32_t enabled)
{

	return -RT_ENOSYS;
}

/* 获取引脚编号 */
/* Get pin number by name,such as PA.0,P0.12 */
rt_base_t rt_pin_get(const char *name)
{

    return 1;
}





 