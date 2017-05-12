#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"
#include "app_error.h"
#include "nrf_gpio.h"

#define COMPARE_COUNTERTIME  (3UL)                                        /**< Get Compare event COMPARE_TIME seconds after the counter starts from 0. */

const nrf_drv_rtc_t rtc = NRF_DRV_RTC_INSTANCE(1); /**< Declaring an instance of nrf_drv_rtc for RTC0. */

/** @brief: Function for handling the RTC0 interrupts.
 * Triggered on TICK and COMPARE0 match.
 */
static void rtc_handler(nrf_drv_rtc_int_type_t int_type)
{
    if (int_type == NRF_DRV_RTC_INT_COMPARE0)
    {
        printf("%s","123456");
			  nrf_gpio_pin_toggle(22);
    }
    else if (int_type == NRF_DRV_RTC_INT_TICK)
    {
			  printf("%s","ABCDEF");
			  nrf_gpio_pin_toggle(21);
    }
}

/** @brief Function starting the internal LFCLK XTAL oscillator.
 */
void lfclk_config(void)
{
    ret_code_t err_code = nrf_drv_clock_init(NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request();
//	  nrf_drv_clock_hfclk_request();
}

/** @brief Function initialization and configuration of RTC driver instance.
 */
void rtc_config(void)
{
    uint32_t err_code;

    //Initialize RTC instance
    err_code = nrf_drv_rtc_init(&rtc, NULL, rtc_handler);
    APP_ERROR_CHECK(err_code);

    //Enable tick event & interrupt
    nrf_drv_rtc_tick_enable(&rtc,true);

    //Set compare channel to trigger interrupt after COMPARE_COUNTERTIME seconds
    err_code = nrf_drv_rtc_cc_set(&rtc,0,COMPARE_COUNTERTIME*RTC1_CONFIG_FREQUENCY,true);
    APP_ERROR_CHECK(err_code);

    //Power on RTC instance
    nrf_drv_rtc_enable(&rtc);
}
