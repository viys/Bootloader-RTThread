/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-07     y zy       the first version
 */
#ifndef APPLICATIONS_APP_H_
#define APPLICATIONS_APP_H_

#include <rtthread.h>
#include "gd32f10x.h"

#define th1_test_priority   20
#define th2_test_priority   19
#define th3_test_priority   18

extern rt_thread_t th1_ptr;
extern struct rt_thread th2;
extern struct rt_thread th3;

extern rt_uint8_t th2_stack[512];
extern rt_uint8_t th3_stack[512];

extern rt_sem_t dynamic_sem;

void th1_test(void* paremeter);
void th2_test(void* paremeter);
void th3_test(void* paremeter);
void th1_test_start(void *paremeter);


#endif /* APPLICATIONS_APP_H_ */
