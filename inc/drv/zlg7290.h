/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2005.2.26
\***************************************************************************/
	

/***************************************************************************\
    #说明: zlg7290驱动程序头文件,只包括led显示部分，
    			键盘扫描部分在keyboard.c中
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------
	2005-2-26	创建

\***************************************************************************/
#ifndef __ZLG7290_H__
#define __ZLG7290_H__


#include "../inc/drv/iic.h"

#define ZLG7290_ADDR 0x70
#define ZLG7290_SystemReg 0x00
#define ZLG7290_Key 0x01
#define ZLG7290_RepeatCnt 0x02
#define ZLG7290_FunctionKey 0x03
#define ZLG7290_CmdBuf0 0x07
#define ZLG7290_CmdBuf1 0x08
#define ZLG7290_FlashOnOff 0x0C
#define ZLG7290_ScanNum 0x0D
#define ZLG7290_DpRam0 0x10
#define ZLG7290_DpRam1 0x11
#define ZLG7290_DpRam2 0x12
#define ZLG7290_DpRam3 0x13
#define ZLG7290_DpRam4 0x14
#define ZLG7290_DpRam5 0x15
#define ZLG7290_DpRam6 0x16
#define ZLG7290_DpRam7 0x17

#define ZLG7289_IICCON		(IICCON_ACKEN |IICCON_CLK512 | IICCON_INTR | IICCON_CLKPRE(0x3))


__inline void ZLG7290_SetLED(int index,char letter)
{
	IIC_MasterTxStart(ZLG7290_ADDR);
	IIC_MasterTx(ZLG7290_DpRam0+index);
	IIC_MasterTx(letter);
	IIC_MasterTxStop();
}

__inline void ZLG7290_SetLEDS(char letter[6])
{
	IIC_MasterTxStart(ZLG7290_ADDR);
	IIC_MasterTx(ZLG7290_DpRam0);
	IIC_MasterTx(letter[0]);
	IIC_MasterTx(letter[1]);
	IIC_MasterTx(letter[2]);
	IIC_MasterTx(letter[3]);
	IIC_MasterTx(letter[4]);
	IIC_MasterTx(letter[5]);
	IIC_MasterTx(letter[6]);
	IIC_MasterTx(letter[7]);
	IIC_MasterTxStop();
}

#endif
