#ifndef LOCK_H
#define LOCK_H
#include <stdint.h>

//锁状态的结构体
typedef struct 
{
		unsigned  char Locker;			// 0:位(0 锁关闭  1锁打开 )1位:
		unsigned  char Vot;					//电池电压
		unsigned  char err; 				//
	  unsigned  char Opening;			//是否在开锁过程中
} LockSt;

void OpenLockTime(void);
void lock_set_init(void);
uint8_t GetLockSt(void);
uint8_t GetLockPos(void);
#endif
