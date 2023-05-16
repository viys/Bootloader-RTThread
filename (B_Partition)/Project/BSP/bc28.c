#include "bc28.h"
#include "systick.h"


void bc28_init(void)
{
	/* 使能 GPIOB 的时钟 */
	rcu_periph_clock_enable(RCU_GPIOB);
	/* PB0 检测4g模块的入网状态 */
	gpio_init(GPIOB,GPIO_MODE_IPD,GPIO_OSPEED_50MHZ,GPIO_PIN_0);
	/* PB0 控制4g模块的复位 */
	gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_7);
	
	gpio_bit_set(GPIOB,GPIO_PIN_2);
	delay_1ms(500);
	
}









