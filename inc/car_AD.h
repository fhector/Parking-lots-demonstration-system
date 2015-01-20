#define ADCCON_FLAG		(0x1<<15)            /* A/Dת������״̬��־��0��A/Dת���У�1��A/Dת������ ����15λ�� */

#define ADCCON_ENABLE_START_BYREAD	(0x1<<1) /* A/Dת��ͨ������������0��ͨ�������رգ�1��ͨ��������ʼ ����1λ��*/

#define rADCCON		(*(volatile unsigned *)0x58000000)
#define rADCDAT0	(*(volatile unsigned *)0x5800000C)
#define PRSCVL (49<<6)                     /* A/Dת������Ƶ����Ϊ49+1=50�����ֵΪ1-255������6-13λ��*/
#define ADCCON_ENABLE_START (0x1)          /* A/Dת��ͨ����λ��1��ʼ����READ_START=0��λ��Ч,�����λ��Ч ����0λ�� */
#define STDBM (0x0<<2)                     /* 0������ģʽ��1����·ģʽ (��2λ) */
#define PRSCEN (0x1<<14)                   /*  A/Dת����Ԥ��Ƶ����ʹ�ܶ� 0����ֹ��1��ʹ�� ����14λ�� */ 
int GetADresult(void);
float car_AD(void);
void init_ADdevice(void);  