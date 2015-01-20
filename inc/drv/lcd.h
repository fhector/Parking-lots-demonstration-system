/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #说明: 
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------
	2004-4-26	创建

\***************************************************************************/
#ifndef __LCD_H__
#define __LCD_H__

//n: LCD 类型编号， w,h:LCD宽度,高度，b: b+1=LCD颜色位数，
//dw: LCD扫描总线宽度4/8/16/24...
//									2bit			10bit,		10bit,	5bit,		5bit
#define LCDINFO(n,w,h,b, dw)			(((dw)<<30)|((w)<<20)|((h)<<10)|((n)<<5)|((b)-1))

//LCD颜色位数
#define MONO					1u
#define GRAY16					4u
#define COLOR256				8u
#define COLOR64K				16u

//LCD扫描总线宽度
#define LCDDBW4					0u
#define LCDDBW8					1u
#define LCDDBW16				2u
#define LCDDBW24				3u

////////////////定义LCD的类型/////////////
#define LCDTYPE_320x240xMONO			LCDINFO(0, 320, 240, MONO, LCDDBW4)
#define LCDTYPE_320x240x16GRAY		LCDINFO(0, 320, 240, GRAY16, LCDDBW4)
#define LCDTYPE_320x240x256COLOR		LCDINFO(0, 320, 240, COLOR256,LCDDBW8)
#define LCDTYPE_640x480x256COLOR		LCDINFO(0, 640, 480, COLOR256,LCDDBW8)
#define LCDTYPE_640x480x64KCOLOR		LCDINFO(0, 640u, 480u, COLOR64K,LCDDBW16)

#define LCDDATA_SWAPW		1	//高低字交换
#define LCDDATA_SWAPB		2	//高低字节交换
#define LCDDATA_SWAPH		3	////高低半字节交换
#define LCDDATA_ORDER		LCDDATA_SWAPW

#define LCDTYPE		LCDTYPE_640x480x64KCOLOR

#define LCDWIDTH		((LCDTYPE>>20)&0x3ff)
#define LCDHEIGHT		((LCDTYPE>>10)&0x3ff)
#define LCDCOLOR		((LCDTYPE&0x1f)+1)
#define LCDBPP			LCDCOLOR
#define LCDDBWIDTH		((LCDTYPE>>30)&0x3)	//LCD扫描总线宽度4/8/16/24...
#define LCDBOARDNUMBER	((LCDTYPE>>5)&0x1f)	//LCD板编号
#define LCDFBSIZE		(LCDWIDTH*LCDHEIGHT*LCDCOLOR/8)

#define LCD_RLEN		(LCDWIDTH*LCDBPP/8)	//每行像素所占的字节数

#define DspTxtMode		0
#define DspGraMode		1

void LCD_Cls(void); //文本模式下清除屏幕
void LCD_printf(const char *format,...);
void LCD_ChangeMode(int mode);
void LCD_Refresh(void);
unsigned int* LCD_Init(void);
void LCD_TestShow(void);

//各个LCD驱动中定义
void LCDBkLight(int isOpen);
void LCDDisplayOpen(int isOpen);
void LCDLib_Init(unsigned int*pbuffer);

#endif
