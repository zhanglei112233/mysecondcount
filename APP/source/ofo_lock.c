#include "ofo_lock.h"
#include "ofo_config.h"
#include "app_timer.h"
#include "nordic_common.h"
#include "nrf_gpio.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"

static unsigned char LockTimeSt = 0;
static unsigned short LockTimeTimes = 0;
extern uint8_t lock1_test;
extern uint8_t lock2_test;

LockSt  lock_st;
APP_TIMER_DEF(Lock_timer_id);			//锁定时器

#define   LOCK_OPEN_TIMER_PERIOD   APP_TIMER_TICKS(10, 0)

#define   GetOPEN_ST		nrf_gpio_pin_read(Lock_Open_SW)				//1：锁打开 0：锁关闭 //锁是否被打开
#define   GetCLOSE_ST		nrf_gpio_pin_read(Lock_Close_SW)			//1：锁锁是否被关闭

#define 	M_RUN()	 			nrf_gpio_pin_set(MOT_CTL_PIN);
#define		M_STOP()			nrf_gpio_pin_clear(MOT_CTL_PIN);
#define   M_Toggle()    nrf_gpio_pin_toggle(MOT_CTL_PIN);

#define 	LED_ON()	 		nrf_gpio_pin_clear(Red_LED_PIN);
#define		LED_OFF()			nrf_gpio_pin_set(Red_LED_PIN);
#define	  LED_Toggle() 	nrf_gpio_pin_toggle(Red_LED_PIN);

static void lock_timer_handler(void * p_context)
{	
	UNUSED_PARAMETER(p_context);
	
	switch(LockTimeSt)
	{
		case 0:			//初始判断
			LockTimeTimes ++;
			if(LockTimeTimes>20)			//被松开一定的时间
			{
					LockTimeSt = 1;
					LockTimeTimes = 0;
				  nrf_drv_gpiote_in_event_enable(Lock_Open_SW, true);
			}
			break;
		case 1:
			if(GetOPEN_ST == 0)
			{
				LockTimeTimes ++;
				if(LockTimeTimes>500)			//产生了错误  超时
				{
						LockTimeSt = 0xff;
						lock_st.Opening = 0;
				}
			}
			else							//被按下了，开锁成功
			{
				app_timer_stop(Lock_timer_id);
				LockTimeSt = 0;
				LockTimeTimes = 0;
				M_STOP();	
				nrf_drv_gpiote_in_event_disable(Lock_Open_SW);
//				LockTrade.OpenTime = TimeStamp;
				lock_st.Opening = 1;
			}
			break;		
		default:
				app_timer_stop(Lock_timer_id);
				LockTimeSt = 0;
				LockTimeTimes = 0;
				M_STOP();	
		    nrf_drv_gpiote_in_event_disable(Lock_Open_SW);
			break;
	}
//		dprintf("LockSt%d\r\n",GetOPEN_ST);
}

/**@brief Function for handling button events.
 *
 * @param[in]   pin_no   The pin number of the button pressed.
 */
void switch_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{	
	  switch (pin)
		{
			case Lock_Open_SW:
				if(lock1_test == 1)
				{
					dprintf("OPEN_ST : OK\r\n");
				}
				else
				{
					app_timer_stop(Lock_timer_id);
					LockTimeSt = 0;
					LockTimeTimes = 0;
					M_STOP();	
					nrf_drv_gpiote_in_event_disable(Lock_Open_SW);
				}
			break;
			
			case Lock_Close_SW:
				if(lock2_test == 1)
          dprintf("CLOSE_ST : OK\r\n");
			break;
		}
}

void lock_set_init(void)
{
	  uint32_t err_code;
	
		LED_ON();
		M_STOP();
		app_timer_create(&Lock_timer_id,
                     APP_TIMER_MODE_REPEATED,
                     lock_timer_handler);		
	
    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);  //
    in_config.pull = NRF_GPIO_PIN_NOPULL;
    err_code = nrf_drv_gpiote_in_init(Lock_Open_SW, &in_config, switch_event_handler);
    APP_ERROR_CHECK(err_code);
//    nrf_drv_gpiote_in_event_enable(Lock_Open_SW, true);
	
    nrf_drv_gpiote_in_config_t in_config1 = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);  //
    in_config.pull = NRF_GPIO_PIN_NOPULL;
    err_code = nrf_drv_gpiote_in_init(Lock_Close_SW, &in_config1, switch_event_handler);
    APP_ERROR_CHECK(err_code);
//    nrf_drv_gpiote_in_event_enable(Lock_Close_SW, true);
}
void OpenLockTime(void)
{
		uint32_t   err_code;	

		err_code = app_timer_start(Lock_timer_id, LOCK_OPEN_TIMER_PERIOD, NULL);
    APP_ERROR_CHECK(err_code);
		M_RUN();
//		lock_st.Opening = 1;
//		LockTrade.OpenTime = TimeStamp;
}

//获取现在锁的状态
// 0：闭合  1：开启 2：状态未知
uint8_t GetLockSt(void)
{
	if(GetCLOSE_ST)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t GetLockPos(void)
{
	if(GetOPEN_ST)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

