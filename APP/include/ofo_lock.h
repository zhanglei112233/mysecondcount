#ifndef LOCK_H
#define LOCK_H
#include <stdint.h>

//��״̬�Ľṹ��
typedef struct 
{
		unsigned  char Locker;			// 0:λ(0 ���ر�  1���� )1λ:
		unsigned  char Vot;					//��ص�ѹ
		unsigned  char err; 				//
	  unsigned  char Opening;			//�Ƿ��ڿ���������
} LockSt;

void OpenLockTime(void);
void lock_set_init(void);
uint8_t GetLockSt(void);
uint8_t GetLockPos(void);
#endif
