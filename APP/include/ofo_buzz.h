
#ifndef BUZZ_H
#define BUZZ_H
#include "ofo_config.h"

typedef struct 
{
		unsigned  char time;				//	Ê±¼ä
		unsigned  char tone; 				//	Òôµ÷
} VoiceType;
	
#define 	BUZZ_ON()	 			nrf_gpio_pin_set(BUZZ_PIN);
#define		BUZZ_OFF()			nrf_gpio_pin_clear(BUZZ_PIN);
#define	  BUZZ_Toggle() 	nrf_gpio_pin_toggle(BUZZ_PIN);
		
void KeyCVoice(void);
void KeyVoice(void);
void VoicePasswordOK(void);
void VoicePasswordErr(void);
void VoiceLockClose(void);
void Buzz_init(void);
#endif



