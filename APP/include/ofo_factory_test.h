#ifndef COMMAND_H
#define COMMAND_H

#define CMD_SET 				'+'			//设置指令
#define CMD_OPEN 				'J'			//开锁
#define CMD_SET_TIME		'T'			//设置锁时间
#define CMD_SET_Finish	'F'			//交易结束
#define CMD_SET_NO			'n'			//设置锁序列号
#define CMD_SET_NAME		'N'			//设置锁名称
#define CMD_SET_Code		'C'			//设置密钥

#define CMD_UPDATA_Code	'U'			//产品升级



#define CMD_GET 			'?'			//查询指令
#define CMD_LK_ST 		' '			//获取锁的状态
#define CMD_GET_TIME	't'			//获取锁时间
#define CMD_GET_BAT		'B'			//获取锁电量
#define CMD_GET_Ver		'V'			//获取软件版本
#define CMD_GET_Soft_Time		'a'	//获取软件时间
#define CMD_GET_NO		'n'			//获取序列号
#define CMD_GET_NAME	'N'			//获取设备名称
#define CMD_GET_ID		'I'			//获取芯片的UUID
#define CMD_GET_Code	'C'			//获取密钥
#define CMD_GET_Csq		'c'			//获取CSQ
#define CMD_GET_Imsi	'i'			//获取imsi
#define CMD_GET_Gps		'g'			//获取imsi


#define CMD_AUT 			'#'			//设备认证



#define CMD_KET 			'$'			//按键模拟



#define CMD_FAC 			'T'			//厂测指令
#define CMD_Motor 		'0'			//测试电机
#define CMD_LIS3DH_ID '1'			//加速度计LIS3DH ID测试
#define CMD_LIS3DH_DT '2'			//加速度计LIS3DH数据测试
#define CMD_GSM_SIG		'3'			//GSM信号强度测试
#define CMD_GSM_GPS		'4'			//GSM的GPS数据测试
#define CMD_Flash_ADV	'5'			//读写广播名称测试
#define CMD_Flash_HW	'6'	    //读写硬件版本号测试
#define CMD_Flash_SW	'7'			//读写软件版本号测试
#define CMD_Flash_NM	'8'			//读写锁序列号测试
#define CMD_KEY_Test	'9'			//按键测试
#define CMD_LED_ON	  ':'			//LED全亮测试
#define CMD_LED_OFF 	';'			//LED全暗测试
#define CMD_Buzzer  	'<'			//蜂鸣器测试
#define CMD_Lock1     '='     //打开开锁闭锁微动开关检测
#define CMD_Lock2     '>'     //关闭开锁闭锁微动开关检测
#define CMD_GSM_SIM   '?'     //SIM卡IMSI信息
#define CMD_BAT_V     '@'     //电源电压测试
#define CMD_LOCK_SN   'A'     //读写锁的序列号

#define CMD_Sleep     'C'     //进入低功耗

#endif
