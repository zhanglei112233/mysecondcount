#include <string.h>
#include <stdint.h>
#include "ofo_key_unlock.h"
#include "nrf_gpio.h"
#include "ofo_config.h"
#include "app_error.h"
#include "ofo_buzz.h"
#include "ofo_led.h"
#include "ofo_lock.h"
#include "nrf_drv_gpiote.h"
#include "app_timer.h"
#include "nordic_common.h"

APP_TIMER_DEF(Key_unlock_timer_id);

#define  PassWord_ERRS             10					  //ÃÜÂë´íÎó´ÎÊý
#define  PassWord_ERR_TIMEOUT      (1*60)				//ÃÜÂë´íÎóÐÝÃßÊ±¼ä 
#define  KEY_CODE_LEN              4
#define  KEY_UNLOCK_TIMER_PERIOD   APP_TIMER_TICKS(1000, 0)

static unsigned int  KeyTimeOutErr = 0;           //ÃÜÂë´íÎó³¬Ê±
static unsigned int  KeyTimeOut    = 0;           //°´¼ü³¬Ê±
static         char  KeyReadBuf[KEY_CODE_LEN] ={0};
static unsigned char KeyIndex 	   = 0;
static unsigned char password_err  = 0;

typedef enum{KEY1= '1', KEY2= '2', KEY3='3', KEY4 = '4', KEYC,KEYNULL}KEY_Value;
typedef struct
{
  char password[3][KEY_CODE_LEN];
	unsigned char password_len;
	unsigned char password_num;
	
}PASSWORD;

PASSWORD lock_pass_word = 
{
	"1111",
	"2222",
	"3333",
	4,
	0
};


/**@brief Function for handling button events.
 *
 * @param[in]   pin_no   The pin number of the button pressed.
 */
void button_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{	
	  uint32_t err_code;
	
	  err_code = app_timer_start(Key_unlock_timer_id, KEY_UNLOCK_TIMER_PERIOD, NULL);
	  APP_ERROR_CHECK(err_code);
    KeyTimeOut = 0;
	  if(password_err >= PassWord_ERRS)
		{
			  if(KeyTimeOutErr <= PassWord_ERR_TIMEOUT)
				{
					return;
				}
				password_err = 0;
				KeyTimeOutErr = 0;
		}
    switch (pin)
    {
        case password_key1:	
			    KeyReadBuf[KeyIndex ++] = KEY1;
				break;
				
        case password_key2:	
			    KeyReadBuf[KeyIndex ++] = KEY2;
				break;
				
        case password_key3:	
			    KeyReadBuf[KeyIndex ++] = KEY3;
				break;
				
        case password_key4:
			    KeyReadBuf[KeyIndex ++] = KEY4;
				break;
				
        case password_keyc:
					memset(KeyReadBuf,0,KEY_CODE_LEN);
					KeyIndex = 0;
					KeyTimeOutErr = 0;
					KeyCVoice();
				break;
					
        default:
          APP_ERROR_HANDLER(pin);
          break;
    }
		
		if(KeyIndex < lock_pass_word.password_len)
		{
				KeyVoice();
			  LED_flash(White_led_light ,1000 ,3);   //°×É«µÄµÆÁÁÈýÃë
		}
		else
		{
			  if (strcmp(KeyReadBuf, lock_pass_word.password[0]) == 0)    //µÚÒ»¸öÃÜÂëÆ¥Åä³É¹¦
				{
						VoicePasswordOK();
						memset(lock_pass_word.password[0],0,KEY_CODE_LEN);
						OpenLockTime();
						password_err = 0;
				}
				else if(strcmp(KeyReadBuf, lock_pass_word.password[1]) == 0)//µÚ¶þ¸öÃÜÂëÆ¥Åä³É¹¦
				{
						VoicePasswordOK();
						memset(lock_pass_word.password[1],0,KEY_CODE_LEN);
						OpenLockTime();
						password_err = 0;
				}
				else if(strcmp(KeyReadBuf, lock_pass_word.password[2]) == 0)//µÚÈý¸öÃÜÂëÆ¥Åä³É¹¦
				{
						VoicePasswordOK();
						memset(lock_pass_word.password[2],0,KEY_CODE_LEN);
						OpenLockTime();
						password_err = 0;
				}
				else			                                                 //ÃÜÂëÆ¥ÅäÊ§°Ü
				{
						VoicePasswordErr();	
						password_err++;
				}														
		}
		
}


/**
 * @brief Function for configuring: PIN_IN pin for input, PIN_OUT pin for output, 
 * and configures GPIOTE to give an interrupt on pin change.
 */
void gpiote_int_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_gpiote_in_config_t in_config1 = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    in_config1.pull = NRF_GPIO_PIN_NOPULL;
    err_code = nrf_drv_gpiote_in_init(password_key1, &in_config1, button_event_handler);
    APP_ERROR_CHECK(err_code);
    nrf_drv_gpiote_in_event_enable(password_key1, true);
	
    nrf_drv_gpiote_in_config_t in_config2 = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    in_config2.pull = NRF_GPIO_PIN_NOPULL;
    err_code = nrf_drv_gpiote_in_init(password_key2, &in_config2, button_event_handler);
    APP_ERROR_CHECK(err_code);
    nrf_drv_gpiote_in_event_enable(password_key2, true);
	
    nrf_drv_gpiote_in_config_t in_config3 = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    in_config3.pull = NRF_GPIO_PIN_NOPULL;
    err_code = nrf_drv_gpiote_in_init(password_key3, &in_config3, button_event_handler);
    APP_ERROR_CHECK(err_code);
    nrf_drv_gpiote_in_event_enable(password_key3, true);
		
    nrf_drv_gpiote_in_config_t in_config4 = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    in_config4.pull = NRF_GPIO_PIN_NOPULL;
    err_code = nrf_drv_gpiote_in_init(password_key4, &in_config4, button_event_handler);
    APP_ERROR_CHECK(err_code);
    nrf_drv_gpiote_in_event_enable(password_key4, true);
	
    nrf_drv_gpiote_in_config_t in_config5 = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    in_config5.pull = NRF_GPIO_PIN_NOPULL;
    err_code = nrf_drv_gpiote_in_init(password_keyc, &in_config5, button_event_handler);
    APP_ERROR_CHECK(err_code);
    nrf_drv_gpiote_in_event_enable(password_keyc, true);
}

static void key_unlock_timer_handler(void * p_context)
{
	  UNUSED_PARAMETER(p_context);
	
	  if(password_err >= PassWord_ERRS)
		{
			KeyTimeOutErr++;
		}
		KeyTimeOut++;
		if(KeyTimeOut > 100)
		{
			KeyIndex = 0;
			KeyTimeOut = 0;
			password_err = 0;
			app_timer_stop(Key_unlock_timer_id);
		}
}
void key_unlock_init(void)
{
    uint32_t           err_code;	
	
    err_code = app_timer_create(&Key_unlock_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                key_unlock_timer_handler);
	  APP_ERROR_CHECK(err_code);
	
	  gpiote_int_init();
}
