#include "ofo_led.h"
#include "ofo_config.h"
#include "app_timer.h"
#include "nordic_common.h"
#include "nrf_gpio.h"

#define   LED_NUMBER            3
#define   LED_TIMER_PERIOD      APP_TIMER_TICKS(1, 0)

APP_TIMER_DEF(LED_timer_id);
uint16_t LED_flash_loop_times = 0;
uint8_t  LED_flash_types = 0;

/* pin ordered by layout order */
const uint8_t led_pin_array[LED_NUMBER] =
    {
        Green_LED_PIN,Red_LED_PIN,White_LED_PIN
		};
		
/* flash method */
const uint8_t  Green_LED_flash[]    =
    {
        0x01,0x00
    };
const uint8_t Red_LED_flash[]    =
    {
        0x02,0x00
    };
const uint8_t Green_Red_flash[]    =
    {
        0x01,0x02
    };		
const uint8_t all_flash[]    =
    {
        0x07,0x00
    };
static void single_led_control(uint8_t num, uint8_t status)
{
    if(status) 
		{
      nrf_gpio_pin_set(led_pin_array[num]);
    } 
		else 
		{
      nrf_gpio_pin_clear(led_pin_array[num]);
    }
}

/* use a number to control LED status */
static void all_led_flash_control(uint8_t para)
{
    uint8_t pin = 0;
    for(; pin < LED_NUMBER ; ++pin) {
        single_led_control(pin,((para >> pin) & 0x01));
    }
}

void led_action_stop(void)
{
	app_timer_stop(LED_timer_id);
	LED_flash_loop_times = 0;
	LED_flash_types      = 0;
	all_led_flash_control(0x00); //close all led
}

static void LED_timer_handler(void * p_context)
{
	  UNUSED_PARAMETER(p_context);
    static uint32_t current_flash_loop = 0;
	  
	  switch(LED_flash_types)
		{
			case Green_led_FLASH:
				all_led_flash_control(Green_LED_flash[current_flash_loop%2]);
			break;
			
			case Red_led_FLASH:
				all_led_flash_control(Red_LED_flash[current_flash_loop%2]);
			break;
			
			case Green_Red_FLASH:
				all_led_flash_control(Green_Red_flash[current_flash_loop%2]);
			break;
			
			case Green_led_light:
				single_led_control(0,1);
			break;
			
			case Red_led_light:
				single_led_control(1,1);
			break;

			case White_led_light:
				single_led_control(2,1);
			break;

			default:
			break;
		}
		
    if((current_flash_loop < LED_flash_loop_times)||(LED_flash_loop_times == 0)) 
		{
			current_flash_loop++;
    } 
		else 
		{
			led_action_stop();
			current_flash_loop   = 0;
    }
}
void LED_flash_init(void)
{
    uint32_t           err_code;
	
    err_code = app_timer_create(&LED_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                LED_timer_handler);
	  APP_ERROR_CHECK(err_code);
}

void LED_flash(uint8_t flash_type ,uint32_t time_interval ,uint16_t loop)
{
	  LED_flash_loop_times = loop;
	  LED_flash_types = flash_type;
	  app_timer_start(LED_timer_id ,time_interval*LED_TIMER_PERIOD ,NULL);
}
