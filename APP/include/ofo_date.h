
#ifndef RTC_H
#define RTC_H

extern unsigned int TimeStamp;

#define INIT_TIME            1483228800		        	//��ʼʱ����2017/1/1 8:0:0

#define INIT_TIME_TEST       (INIT_TIME+60*10)			//��ʼʱ����2017/1/1 8:0:0
#define BSP_RTC_TIMEOUT_MS   (1000)

extern unsigned int TimeStamp;  		  //ʱ��� ���ж��������  ��ʼʱ����2017/1/1 8:0:0
extern unsigned int time_second;		  //ʱ��� ���������������
extern unsigned int time_plus;			  //����ʱ��

void AppRtcInit(void);
unsigned char SecondTimeDeal(void);
void SetTimeStamp(unsigned int time);

#endif
