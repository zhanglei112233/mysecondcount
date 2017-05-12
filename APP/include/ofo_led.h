
#include <stdint.h>


typedef enum {
    Green_led_FLASH      = 1,    /*�̵���˸*/
    Red_led_FLASH        = 2,    /*�����˸*/
    Green_Red_FLASH      = 3,    /*�̵ƺ�ƽ�����˸*/
	  White_led_FLASH      = 4,    /*�׵���˸*/
	  Green_led_light      = 5,    /*�̵���*/
	  Red_led_light        = 6,    /*�����*/
	  White_led_light      = 7     /*�׵���*/
}LED_Flash_Type;

void LED_flash_init(void);
void LED_flash(uint8_t flash_type ,uint32_t time_interval ,uint16_t loop);
