#include "../inc/car_AD.h"

void init_ADdevice(void)                       /* A/D转换初始化 */
{
	
	
	rADCCON=(PRSCVL|ADCCON_ENABLE_START|STDBM|PRSCEN);/*正常模式，分频50，置1启动*/
}

int GetADresult(void)
{   
	
	  
	  rADCCON=ADCCON_ENABLE_START_BYREAD|(1<<3)|PRSCEN|PRSCVL;  /* 3-5位为模拟通道选择位 （第3-5位） */
	
	hudelay(10);
	while(!(rADCCON&ADCCON_FLAG));         /*  转换结束 */
	
	return (0x3ff&rADCDAT0);               /* 返回采样值,S32410中是10位的A/D器 */
	
}

float car_AD(void)
{
    float d=0.0;
    int j=0;
 	for(j=0;j<=2;j++)
	{
		d+=GetADresult()*3.3/1023; // 数据 采集，处理
    }
    d/=3;
   return (d);			
}