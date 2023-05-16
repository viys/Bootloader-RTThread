#include "gd32f10x.h"
#include "rtthread.h"
#include "app.h"
#include "led.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include "hlk_b40.h"

rt_thread_t apptaskstart_ptr = RT_NULL;
void AppTaskStart(void* paremeter);

void AppTaskStart(void* paremeter)
{
    rt_err_t ret_app = 0;
    rt_kprintf("Start creating and starting tasks ...\n");
    ////静态创建任务2
    ret_app = rt_thread_init(&th2, "th2", th2_test, NULL, th2_stack, sizeof(th2_stack), th2_test_priority, 5);
    if(ret_app == RT_EOK){
        rt_thread_startup(&th2);
        rt_kprintf("th2 initialized successfully\n");
    }else{
        LOG_E("th2 initialized failed\n");
    }
    ////静态创建任务3
    ret_app = rt_thread_init(&th3, "th3", th3_test, NULL, th3_stack, sizeof(th3_stack), th3_test_priority, 5);
        if(ret_app == RT_EOK){
            rt_thread_startup(&th3);
            rt_kprintf("th3 initialized successfully\n");
        }else{
            LOG_E("th3 initialized failed\n");
        }


}

#include "ledblink.h"
#define LED0_PIN    GET_PIN(C, 0)



rt_device_t dev;
//static	uint8_t temp1[2];

int main(){
//	rt_err_t ret;

	apptaskstart_ptr = rt_thread_create("AppTaskStart", AppTaskStart, NULL, 512, 18, 5);
    rt_thread_startup(apptaskstart_ptr);

    led_add_device(LED0_PIN);
	
	dev = rt_device_find("led");
	if(dev == RT_NULL){
		LOG_E("rt_device_find[led] failed...\n");
		return -RT_EINVAL;
	}
	
    while (1)
    {
		
//		rt_kprintf("%s\r\n",B40_CRTL(B40_BAND,115200));
		
		rt_thread_mdelay(1000);

    }

}
