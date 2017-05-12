#include "ofo_date.h"
#include "app_timer.h"
#include "nordic_common.h"

#define   DATE_TIMER_PERIOD      APP_TIMER_TICKS(1000, 0)

APP_TIMER_DEF(RTC_timer_id);

unsigned int TimeStamp   = INIT_TIME; 		//时间戳 在中断里面更新  初始时间是2017/1/1 8:0:0
unsigned int time_second = INIT_TIME;		  //时间戳 在主程序里面更新
unsigned int time_plus   = INIT_TIME;			//心跳时间

uint8_t SecondTimeDeal(void)
{
		if(TimeStamp > time_second)
		{
			time_second = TimeStamp;
			return 1;	
		}
		else
		{
			return 0;
		}
}

uint8_t IfTestTime(void)
{
	static unsigned char ret = 1;
	if(ret)
	{
			if(TimeStamp>INIT_TIME_TEST)
		{
					ret = 0;
		}
		else
		{
					ret = 1;
		}
	}
	return ret;
}

static void date_timer_handler(void * p_context)
{
	UNUSED_PARAMETER(p_context);
	TimeStamp ++;
	if(time_plus == TimeStamp)
	{
//			heartbeat =1;
	}	
}

void SetTimeStamp(uint32_t time)
{
	TimeStamp = time;
}

//初始化实时时钟
void AppRtcInit(void)
{
    uint32_t           err_code;		
    err_code = app_timer_create(&RTC_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                date_timer_handler);
		err_code = app_timer_start(RTC_timer_id, DATE_TIMER_PERIOD, NULL);
    if (err_code == NRF_SUCCESS)
    {
         
    }
		SetTimeStamp(INIT_TIME);
}


//大小端模式转换
uint32_t end_trans(uint32_t data)
{
	typedef union { 
	 unsigned int int_data; 				//
	 struct{ 
					 unsigned char byte0; 
					 unsigned char byte1; 
					 unsigned char byte2; 
					 unsigned char byte3; 
		}byte_data; 
	} END_TRANS_UNION; 
	
	END_TRANS_UNION in;				//输入
	END_TRANS_UNION out;			//输出
	in.int_data = data;
	out.byte_data.byte0= in.byte_data.byte3;
	out.byte_data.byte1= in.byte_data.byte2;
	out.byte_data.byte2= in.byte_data.byte1;
	out.byte_data.byte3= in.byte_data.byte0;
	return out.int_data;
}
//(void)app_timer_stop(RTC_timer_id);
