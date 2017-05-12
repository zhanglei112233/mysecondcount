




/*串口使用引脚配置*/
#define RX_PIN_NUMBER  30
#define TX_PIN_NUMBER  29
#define CTS_PIN_NUMBER 40
#define RTS_PIN_NUMBER 40

/*电池电压检测引脚配置*/
#define ADC_PIN_NUMBER 2

/*蜂鸣器引脚配置*/
#define BUZZ_PIN       23 

/*电机引脚配置*/
#define MOT_CTL_PIN    13 

/*微动开关引脚配置*/
#define Lock_Open_SW   10 
#define Lock_Close_SW  11 

/*LED引脚配置*/
#define Green_LED_PIN  21 
#define Red_LED_PIN    22 
#define White_LED_PIN  28 

/*按键引脚配置*/
#define password_key1  15 
#define password_key2  16 
#define password_key3  17 
#define password_key4  18 
#define password_keyc  19 

#if 1
#define dprintf printf
#else
#define dprintf void
#endif
