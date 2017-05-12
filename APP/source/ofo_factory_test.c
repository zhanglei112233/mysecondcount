#include "ofo_factory_test.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ofo_config.h"
#include "ofo_lock.h"
#include "ofo_date.h"
#include "ofo_flash.h"
#include "ofo_lis3dh.h"
#include "ofo_buzz.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_drv_gpiote.h"

uint8_t accredit = 0;
uint8_t lock1_test = 0;
uint8_t lock2_test = 0;

//授权认证
void AUTCommandDeal( uint8_t * p_data, uint16_t length)
{
//		if (strcmp(p_data, Hard_parm.BLECode) == 0)
		{				
				accredit = 1;
		}
}

//设置命令
void SETCommandDeal( uint8_t * p_data, uint16_t length)
{
	uint32_t i;			//
	uint8_t dat;
  AxesRaw_t  ACC_Raw;
	uint8_t    BLE_ADV[BLE_NAME_LEN];
	char       BLE_ADV_WF[BLE_NAME_LEN];
	uint8_t    LOCK_SN_WR[Lock_No_LEN];
	uint8_t    BLE_ADV_SW[] = "ofo_adv_tes";
	switch(p_data[0])
	{
		case CMD_OPEN:
			OpenLockTime();
			break;

		case CMD_SET_TIME:			
			i = p_data[1];	i = i<<8;
			i += p_data[2];	i = i<<8;
			i = p_data[3];	i = i<<8;
			i += p_data[4];	
			SetTimeStamp(i);
			break;

		case CMD_LIS3DH_ID:			
      LIS3DH_GetWHO_AM_I(&dat);	
      if(dat == 0x33)		
			{
				dprintf("CMD_LIS3DH_ID : OK\r\n");
			}
			else
			{
				dprintf("CMD_LIS3DH_ID : Error\r\n");
			}
			break;
		
		case CMD_LIS3DH_DT:		
			LIS3DH_GetAccAxesRaw(&ACC_Raw);
		  if((abs(ACC_Raw.AXIS_X) < 512) && (abs(ACC_Raw.AXIS_Y) < 512) && (abs(ACC_Raw.AXIS_Z) >= 3840))
			{
				dprintf("CMD_LIS3DH_DT : OK\r\n");
			}
			else
			{
				dprintf("CMD_LIS3DH_DT : Error\r\n");
			}
			break;
			
		case CMD_GSM_SIG:		
		  break;
		
		case CMD_GSM_GPS:
		  break;
		
		case CMD_GSM_SIM:
		  break;
		
		case CMD_Flash_ADV:
			WriteParm(BLE_NAME_ADD,BLE_ADV_SW,12);
		  Readparm(BLE_NAME_ADD ,BLE_ADV ,12);
		  memcpy(BLE_ADV_WF ,BLE_ADV ,12);
		  if(strcmp(BLE_ADV_WF ,"ofo_adv_tes"))
			{
				dprintf("CMD_Flash_RW : Error\r\n");
			}
			else
			{
				dprintf("CMD_Flash_RW : OK\r\n");
			}
		  break;
		
		case CMD_Flash_HW:
		  break;
			
		case CMD_Flash_SW:
		  break;

		case CMD_Flash_NM:
		  break;
			
		case CMD_KEY_Test:
		  break;
			
		case CMD_LED_ON:
			nrf_gpio_pin_set(Green_LED_PIN);
		  nrf_gpio_pin_set(Red_LED_PIN);
		  nrf_gpio_pin_set(White_LED_PIN);
		  break;
		
		case CMD_LED_OFF:
			nrf_gpio_pin_clear(Green_LED_PIN);
		  nrf_gpio_pin_clear(Red_LED_PIN);
		  nrf_gpio_pin_clear(White_LED_PIN);
		  break;

		case CMD_Buzzer:
		  BUZZ_ON();
		  nrf_delay_ms(2000);
		  BUZZ_OFF();
		  nrf_delay_ms(100);
  		break;

		case CMD_Lock1:
			lock1_test = 1;
		  nrf_drv_gpiote_in_event_enable(Lock_Open_SW, true);
			lock2_test = 1;
		  nrf_drv_gpiote_in_event_enable(Lock_Close_SW, true);
		  break;
		
		case CMD_Lock2:
			lock1_test = 0;
		  nrf_drv_gpiote_in_event_disable(Lock_Open_SW);
			lock2_test = 0;
		  nrf_drv_gpiote_in_event_disable(Lock_Close_SW);
		  break;
				
		case CMD_BAT_V:
		  break;
		
		case CMD_LOCK_SN:
			WriteParm(Lock_No_ADD ,&p_data[1] ,Lock_No_LEN);
		  Readparm(Lock_No_ADD ,LOCK_SN_WR ,Lock_No_LEN);
		  dprintf("%s\r\n",LOCK_SN_WR);
		  break;
		
			case CMD_Sleep:
		  break;
		
		default:
			dprintf("cmd err ");
			break;
	}
}

void CommandDeal( uint8_t * p_data, uint16_t length)
{
		switch(p_data[0])
		{
			case CMD_SET:
				if((length >=1)&&(accredit))
				{
						SETCommandDeal(p_data+1,length-1);
				}
				break;
			case CMD_GET:
				if((length >=1)&&(accredit))
				{
//						GETCommandDeal(p_data+1,length-1);
				}
				break;
				
			case CMD_AUT:
				if(length >=1)
				{
//						AUTCommandDeal(p_data+1,length-1);
				}
				break;
			case CMD_KET:
				if(length >=1)
				{
//						KeyCommandDeal(p_data+1,length-1);
				}
				break;
			case CMD_FAC:
				if(length >=1)
				{
//		    		FACCommandDeal(p_data+1,length-1);
				}
				break;
				
			default:
				dprintf("cmd err ");
				break;
		}
}
