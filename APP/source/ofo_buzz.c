#include "ofo_buzz.h"
#include <stdbool.h>
#include "app_timer.h"
#include "nordic_common.h"
#include "nrf_gpio.h"

unsigned char buzz_st = 0;		//ÊÇ·ñÔÚ·äÃù×´Ì¬
unsigned char buzz_index = 0;
VoiceType Tone;
const VoiceType KEY_TONE = {40,	0x00};
const VoiceType KEYC_TONE = {40,0xF0};
const VoiceType PasswordOK_TONE = {40,0x11};
const VoiceType PasswordERR_TONE = {80,0xaa};
const VoiceType LockClose_TONE = {40,0x11};

APP_TIMER_DEF(Buzz_timer_id);

static void buzz_timer_handler(void * p_context)
{
	UNUSED_PARAMETER(p_context);
	buzz_index ++;
	if(((Tone.tone) == 0)||(buzz_index > 8))
	{
		app_timer_stop(Buzz_timer_id);
		BUZZ_OFF();
		buzz_st = 0;
		buzz_index  = 0;
//		ERR_LED_OFF(); 
	}
	else
	{
		if((Tone.tone)&(1<<(8-buzz_index)))
		{
				Tone.tone &= ~(1<(8-buzz_index));	
				BUZZ_ON();
		}
		else
		{
				BUZZ_OFF();
		}
	}
}

void Buzz_init(void)
{		
    uint32_t           err_code;	
	
		BUZZ_OFF();
    err_code = app_timer_create(&Buzz_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                buzz_timer_handler);
	  APP_ERROR_CHECK(err_code);
	
	  KeyVoice();
}

void PlayVoice(VoiceType vTone)
{
		uint32_t   err_code;	
		Tone = vTone;
		BUZZ_ON();
		buzz_index = 0;
		err_code = app_timer_start(Buzz_timer_id, (Tone.time*32768/1000)/*BSP_MS_TO_TICK(BSP_LOCK_TIMEOUT_MS)*/, NULL);
	  APP_ERROR_CHECK(err_code);
	
		buzz_st = 1;
}

void KeyCVoice(void)
{
	  PlayVoice(KEYC_TONE);
}
void KeyVoice(void)
{
		PlayVoice(KEY_TONE);
}

void VoicePasswordOK(void)
{
		PlayVoice(PasswordOK_TONE);
}
void VoicePasswordErr(void)
{
//	  ERR_LED_ON(); 
	  PlayVoice(PasswordERR_TONE);

}
void VoiceLockClose(void)
{
		PlayVoice(LockClose_TONE);
}
