
#include <stdint.h>


typedef enum {
    Green_led_FLASH      = 1,    /*бл╣фиак╦*/
    Red_led_FLASH        = 2,    /*╨Л╣фиак╦*/
    Green_Red_FLASH      = 3,    /*бл╣ф╨Л╣ф╫╩лФиак╦*/
	  White_led_FLASH      = 4,    /*╟в╣фиак╦*/
	  Green_led_light      = 5,    /*бл╣фаа*/
	  Red_led_light        = 6,    /*╨Л╣фаа*/
	  White_led_light      = 7     /*╟в╣фаа*/
}LED_Flash_Type;

void LED_flash_init(void);
void LED_flash(uint8_t flash_type ,uint32_t time_interval ,uint16_t loop);
