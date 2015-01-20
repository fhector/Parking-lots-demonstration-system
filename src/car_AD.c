#include "../inc/car_AD.h"

void init_ADdevice(void)                       /* A/Dת����ʼ�� */
{
	
	
	rADCCON=(PRSCVL|ADCCON_ENABLE_START|STDBM|PRSCEN);/*����ģʽ����Ƶ50����1����*/
}

int GetADresult(void)
{   
	
	  
	  rADCCON=ADCCON_ENABLE_START_BYREAD|(1<<3)|PRSCEN|PRSCVL;  /* 3-5λΪģ��ͨ��ѡ��λ ����3-5λ�� */
	
	hudelay(10);
	while(!(rADCCON&ADCCON_FLAG));         /*  ת������ */
	
	return (0x3ff&rADCDAT0);               /* ���ز���ֵ,S32410����10λ��A/D�� */
	
}

float car_AD(void)
{
    float d=0.0;
    int j=0;
 	for(j=0;j<=2;j++)
	{
		d+=GetADresult()*3.3/1023; // ���� �ɼ�������
    }
    d/=3;
   return (d);			
}