
#ifndef RTC_H
#define RTC_H

extern unsigned int TimeStamp;

#define INIT_TIME            1483228800		        	//初始时间是2017/1/1 8:0:0

#define INIT_TIME_TEST       (INIT_TIME+60*10)			//初始时间是2017/1/1 8:0:0
#define BSP_RTC_TIMEOUT_MS   (1000)

extern unsigned int TimeStamp;  		  //时间戳 在中断里面更新  初始时间是2017/1/1 8:0:0
extern unsigned int time_second;		  //时间戳 在主程序里面更新
extern unsigned int time_plus;			  //心跳时间

void AppRtcInit(void);
unsigned char SecondTimeDeal(void);
void SetTimeStamp(unsigned int time);

#endif
