#include "nrf_drv_wdt.h"
#include "app_error.h"
#include "app_util_platform.h"

#define 	WDT_CONFIG_RELOAD 				20*1000  													//20s一次看门狗溢出

nrf_drv_wdt_channel_id m_channel_id;

/**
 * @brief WDT events handler.
 */
void wdt_event_handler(void)
{
//    LEDS_OFF(LEDS_MASK);
    
    //NOTE: The max amount of time we can spend in WDT interrupt is two cycles of 32768[Hz] clock - after that, reset occurs
}

void wdt_init(void)
{
    uint32_t err_code = NRF_SUCCESS;
    //Configure WDT.
		nrf_drv_wdt_config_t config;	  
		config.behaviour=WDT_CONFIG_BEHAVIOUR;
		config.reload_value=WDT_CONFIG_RELOAD;
		config.interrupt_priority=WDT_CONFIG_IRQ_PRIORITY;

		err_code = nrf_drv_wdt_init(&config, wdt_event_handler);
		APP_ERROR_CHECK(err_code);
		err_code = nrf_drv_wdt_channel_alloc(&m_channel_id);
		APP_ERROR_CHECK(err_code);
//    nrf_drv_wdt_enable();
}
