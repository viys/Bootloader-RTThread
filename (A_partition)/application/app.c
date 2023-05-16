/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-07     y zy       the first version
 */
#include "app.h"
#include "drv_uart.h"

#define DBG_TAG "app"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

rt_thread_t th1_ptr = RT_NULL;
struct rt_thread th2;
struct rt_thread th3;

rt_uint8_t th2_stack[512] = {0};
rt_uint8_t th3_stack[512] = {0};

rt_sem_t dynamic_sem = RT_NULL;

#ifdef FINSH_USING_MSH

void th1_test_start(void *paremeter)
{
    th1_ptr = rt_thread_create("th1", th1_test, NULL, 512, th1_test_priority, 5);//动态创建任务
    if(th1_ptr != RT_NULL){
        rt_thread_startup(th1_ptr);
        LOG_D("th1 created successfully\n");
    }else{
        LOG_E("th1 created failed\n");
    }
}

MSH_CMD_EXPORT(th1_test_start, th1 start);

#endif

void th1_test(void* paremeter)
{
    while(1){
		
        return;
    }
}

void th2_test(void* paremeter)
{

    while(1){
//		rt_kprintf("th2_test is runing...\n");
		rt_thread_mdelay(1000);
    }
}

void th3_test(void* paremeter)
{

    while(1){
//		rt_kprintf("th3_test is runing...\n");
		rt_thread_mdelay(2100);
    }
}
