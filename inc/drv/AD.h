/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #说明: s3c2410 AD函数头文件定义
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  ----------------------------------

	----------------------------------修正--------------------------------------
	2004-11-4	创建，测试通过

	----------------------------------使用说明--------------------------------

\***************************************************************************/
#ifndef __AD_H__
#define __AD_H__

#include "../inc/drv/reg2410.h"

#define ADCCR_ACCPD			0x80
#define ADCCR_DIRECTC		0x40
#define ADCCR_WAIT2CLK		(0x1<<2)
#define ADCCR_WAIT4CLK		(0x2<<2)
#define ADCCR_EDGE			(0x3<<2)
#define ADCCR_SOP			0x2
#define ADCCR_LONGCAL		1

#define ADCDIRCR_AIOSTOP	(1<<7)
#define ADCDIRCR_ADIN(n)		(1<<n)

#define init_ADdevice()	do{rADCCR=ADCCR_DIRECTC;}while(0)
int AD_GetResult(int channel);
void AD_test(void);

#endif //#define __AD_H__

