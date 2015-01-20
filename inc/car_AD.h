#define ADCCON_FLAG		(0x1<<15)            /* A/D转化器的状态标志：0：A/D转化中；1：A/D转换结束 （第15位） */

#define ADCCON_ENABLE_START_BYREAD	(0x1<<1) /* A/D转换通过读来启动；0：通过读来关闭；1：通过读来开始 （第1位）*/

#define rADCCON		(*(volatile unsigned *)0x58000000)
#define rADCDAT0	(*(volatile unsigned *)0x5800000C)
#define PRSCVL (49<<6)                     /* A/D转换器分频因子为49+1=50；最大值为1-255；（第6-13位）*/
#define ADCCON_ENABLE_START (0x1)          /* A/D转换通过该位置1开始；若READ_START=0该位有效,否则该位无效 （第0位） */
#define STDBM (0x0<<2)                     /* 0：正常模式，1：旁路模式 (第2位) */
#define PRSCEN (0x1<<14)                   /*  A/D转换器预分频因子使能端 0：禁止；1：使能 （第14位） */ 
int GetADresult(void);
float car_AD(void);
void init_ADdevice(void);  