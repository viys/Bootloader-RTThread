#include "uart.h"

uint8_t U0_RxBuff[U0_RX_SIZE];
uint8_t U0_TxBuff[U0_TX_SIZE];
UCB_CB 	U0CB;

uint8_t U2_RxBuff[U2_RX_SIZE];
uint8_t U2_TxBuff[U2_TX_SIZE];
UCB_CB 	U2CB;

static void u0rx_ptr_init(void)
{
	/* IN指针指向SE指针对结构体数组的0号成员 */
	U0CB.URxDataIN = &U0CB.URxDataPtr[0];
	/* OUT指针指向SE指针对结构体数组的0号成员 */
	U0CB.URxDataOUT = &U0CB.URxDataPtr[0];
	/* END指针指向SE指针对结构体数组的最后一个成员 */
	U0CB.URxDataEND = &U0CB.URxDataPtr[URxNUM-1];
	/* 使用 IN 指针指向的SE指针对中的S指针标记第一次接收的起始位置 */
	U0CB.URxDataIN->start = U0_RxBuff;
	/* 积累接收数量清零 */
	U0CB.URxCounter = 0;
}

static void u2rx_ptr_init(void)
{
	/* IN指针指向SE指针对结构体数组的0号成员 */
	U2CB.URxDataIN = &U2CB.URxDataPtr[0];
	/* OUT指针指向SE指针对结构体数组的0号成员 */
	U2CB.URxDataOUT = &U2CB.URxDataPtr[0];
	/* END指针指向SE指针对结构体数组的最后一个成员 */
	U2CB.URxDataEND = &U2CB.URxDataPtr[URxNUM-1];
	/* 使用 IN 指针指向的SE指针对中的S指针标记第一次接收的起始位置 */
	U2CB.URxDataIN->start = U2_RxBuff;
	/* 积累接收数量清零 */
	U2CB.URxCounter = 0;
}

static void dma0_init(void)
{
	/* DMA初始化结构体 */
	dma_parameter_struct Dma_Init_Sturt;
	/* 打开 DMA0 时钟 */
	rcu_periph_clock_enable(RCU_DMA0);
	
	/* 串口0对应的 DMA 通道配置 */
	/* 复位 DMA0 的通道4(串口0的接收通道) */
	dma_deinit(DMA0,DMA_CH4);
	
	/* 设置外设地址,串口0的数据寄存器 */
	Dma_Init_Sturt.periph_addr = USART0+4;
	/* 外设数据宽度,8位1个字节 */
	Dma_Init_Sturt.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
	/* 设置接收缓冲区地址 */
	Dma_Init_Sturt.memory_addr = (uint32_t)U0_RxBuff;
	/* 缓冲区数据宽度,8位1个字节 */
	Dma_Init_Sturt.memory_width = DMA_MEMORY_WIDTH_8BIT;
	/* 设置最大接收量 */
	Dma_Init_Sturt.number = U0_RX_MAX+1;
	/* 设置优先级 */
	Dma_Init_Sturt.priority = DMA_PRIORITY_HIGH;
	/* 外设地址增加关闭 */
	Dma_Init_Sturt.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	/* 内存地址增加打开 */
	Dma_Init_Sturt.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	/* 传输方向:外设寄存器到内存缓冲区 */
	Dma_Init_Sturt.direction = DMA_PERIPHERAL_TO_MEMORY;
	/* 初始化 DMA0 的通道4 */
	dma_init(DMA0,DMA_CH4,&Dma_Init_Sturt);
	/* 关闭循环模式 */
	dma_circulation_disable(DMA0,DMA_CH4);
	/* 打开 DMA0 的通道4(串口0接收通道) */
	dma_channel_enable(DMA0,DMA_CH4);
	
	/* 串口2对应的 DMA 通道配置 */
	/* 复位 DMA0 的通道2(串口2的接收通道) */
	dma_deinit(DMA0,DMA_CH2);
	
	/* 设置外设地址,串口2的数据寄存器 */
	Dma_Init_Sturt.periph_addr = USART2+4;
	/* 外设数据宽度,8位1个字节 */
	Dma_Init_Sturt.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
	/* 设置接收缓冲区地址 */
	Dma_Init_Sturt.memory_addr = (uint32_t)U2_RxBuff;
	/* 缓冲区数据宽度,8位1个字节 */
	Dma_Init_Sturt.memory_width = DMA_MEMORY_WIDTH_8BIT;
	/* 设置最大接收量 */
	Dma_Init_Sturt.number = U2_RX_MAX+1;
	/* 设置优先级 */
	Dma_Init_Sturt.priority = DMA_PRIORITY_HIGH;
	/* 外设地址增加关闭 */
	Dma_Init_Sturt.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	/* 内存地址增加打开 */
	Dma_Init_Sturt.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	/* 传输方向:外设寄存器到内存缓冲区 */
	Dma_Init_Sturt.direction = DMA_PERIPHERAL_TO_MEMORY;
	/* 初始化 DMA0 的通道4 */
	dma_init(DMA0,DMA_CH2,&Dma_Init_Sturt);
	/* 关闭循环模式 */
	dma_circulation_disable(DMA0,DMA_CH2);
	/* 打开 DMA0 的通道4(串口0接收通道) */
	dma_channel_enable(DMA0,DMA_CH2);
}

void uart0_init(uint32_t bandrate)
{
	/* 打开串口0时钟 */
	rcu_periph_clock_enable(RCU_USART0);
	/* 打开 GPIOA 时钟 */
	rcu_periph_clock_enable(RCU_GPIOA);
	
	/* connect PA9  to U0_TX */
	/* connect PA10 to U0_RX */
	gpio_init(GPIOA,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);
	gpio_init(GPIOA,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO_PIN_10);
	
	/* 复位串口0 */
	usart_deinit(USART0);
	/* 设置波特率 */
	usart_baudrate_set(USART0,bandrate);
	/* 不使用校验位 */
	usart_parity_config(USART0,USART_PM_NONE);
	/* 8位数据位 */
	usart_word_length_set(USART0,USART_WL_8BIT);
	/* 1位停止位 */
	usart_stop_bit_set(USART0,USART_STB_1BIT);
	/* 开启发送功能 */
	usart_transmit_config(USART0,USART_TRANSMIT_ENABLE);
	/* 开启接收功能 */
	usart_receive_config(USART0,USART_RECEIVE_ENABLE);
	/* 开接收dma */
	usart_dma_receive_config(USART0,USART_RECEIVE_DMA_ENABLE);
	
	/* 设置中断分组:2 */
	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
	/* 打开串口0中断,并设置优先级 */
	nvic_irq_enable(USART0_IRQn,0,0);
	/* 打开串口0空闲中断 */
	usart_interrupt_enable(USART0,USART_INT_IDLE);
	
	/* 串口0控制结构体初始化 */
	u0rx_ptr_init();
	/* 串口0对应dma初始化 */
	dma0_init();
	
	/* 串口0开启 */
	usart_enable(USART0);
}

void uart2_init(uint32_t bandrate)
{
	/* 打开串口2时钟 */
	rcu_periph_clock_enable(RCU_USART2);
	/* 打开 GPIOB 时钟 */
	rcu_periph_clock_enable(RCU_GPIOB);
	
	/* connect PB10 to U2_TX */
	/* connect PB11 to U2_RX */
	gpio_init(GPIOB,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_10);
	gpio_init(GPIOB,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO_PIN_11);
	
	/* 复位串口2 */
	usart_deinit(USART2);
	/* 设置波特率 */
	usart_baudrate_set(USART2,bandrate);
	/* 不使用校验位 */
	usart_parity_config(USART2,USART_PM_NONE);
	/* 8位数据位 */
	usart_word_length_set(USART2,USART_WL_8BIT);
	/* 1位停止位 */
	usart_stop_bit_set(USART2,USART_STB_1BIT);
	/* 开启发送功能 */
	usart_transmit_config(USART2,USART_TRANSMIT_ENABLE);
	/* 开启接收功能 */
	usart_receive_config(USART2,USART_RECEIVE_ENABLE);
	/* 开接收dma */
	usart_dma_receive_config(USART2,USART_RECEIVE_DMA_ENABLE);
	
	/* 打开串口0中断,并设置优先级 */
	nvic_irq_enable(USART2_IRQn,0,0);
	/* 打开串口0空闲中断 */
	usart_interrupt_enable(USART2,USART_INT_IDLE);
	
	/* 串口2控制结构体初始化 */
	u2rx_ptr_init();
	
	/* 串口2开启 */
	usart_enable(USART2);
}

void u0_transmit_test(void)
{
	if(U0CB.URxDataOUT != U0CB.URxDataIN){
		u0_printf("resevie %d byte\r\n",U0CB.URxDataOUT->end - U0CB.URxDataOUT->start + 1);
		for(int i=0; i < U0CB.URxDataOUT->end - U0CB.URxDataOUT->start + 1; i++){
			u0_printf("%c",U0CB.URxDataOUT->start[i]);
		}
		u0_printf("\r\n");
		
		U0CB.URxDataOUT++;
		if(U0CB.URxDataOUT == U0CB.URxDataEND){
			U0CB.URxDataOUT = &U0CB.URxDataPtr[0];
		}
	}

}

void u0_printf(char *format,...)
{
	/* 建立一个va_list变量listdata */
	va_list listdata;
	/* 向listdata加载,...代表不定长的参数 */
	va_start(listdata,format);
	
	/* 格式化输出到缓冲区 U0_TxBuff */
	vsprintf((char *)U0_TxBuff,format,listdata);
	/* 释放lostdata */
	va_end(listdata);
	
	/* 根据 U0_TxBuff 的缓冲区数量,一个字节一个字节的循环发送 */
	for(uint16_t i=0;i<strlen((const char*)U0_TxBuff);i++){
		/* 等待发送缓冲区为0 */
		while(usart_flag_get(USART0,USART_FLAG_TBE) != 1);
		/* 填入数据 */
		usart_data_transmit(USART0,U0_TxBuff[i]);
	}
	
	/* 等到最后一个字节数据发送完毕 */
	while(usart_flag_get(USART0,USART_FLAG_TC) != 1);
	
}

void u2_printf(char *format,...)
{
	/* 建立一个va_list变量listdata */
	va_list listdata;
	/* 向listdata加载,...代表不定长的参数 */
	va_start(listdata,format);
	
	/* 格式化输出到缓冲区 U2_TxBuff */
	vsprintf((char *)U2_TxBuff,format,listdata);
	/* 释放lostdata */
	va_end(listdata);
	
	/* 根据 U0_TxBuff 的缓冲区数量,一个字节一个字节的循环发送 */
	for(uint16_t i=0;i<strlen((const char*)U2_TxBuff);i++){
		/* 等待发送缓冲区为0 */
		while(usart_flag_get(USART2,USART_FLAG_TBE) != 1);
		/* 填入数据 */
		usart_data_transmit(USART2,U2_TxBuff[i]);
	}
	
	/* 等到最后一个字节数据发送完毕 */
	while(usart_flag_get(USART2,USART_FLAG_TC) != 1);
}
