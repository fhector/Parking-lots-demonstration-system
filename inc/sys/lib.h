/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/

/***************************************************************************\
    #说明: C库函数定义头文件
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------
	2004-5-2	1、为调试和内核的输出，添加TRACE和printk宏定义
				2、定义mdelay宏，毫秒级延时
				3、添加版本号的定义MAJOR, MINOR, BUILD VERSION

	2004-4-30	1、添加CONSOLE宏定义，可以定义串口输出的控制台
				2、定义CONSOLE_PUTC宏，作为标准控制台输出宏。
					printf 时被fputc调用
				3、添加Uart_SendChar函数，如果发送'\n'则自动发送'\r'，
					适合于控制台输出

	2004-4-26	创建

\***************************************************************************/
#ifndef __LIB_H__
#define __LIB_H__

#include	"io.h"
#include	"sysdrv.h"		//驱动抽象层头文件
#include	"../inc/macro.h"
#include	"../src/fs/osfile.h"
#include "loadfile.h"

/***********************Version define***************************************/
#define MAJOR_VERSION		1
#define MINOR_VERSION		0
#define BUILD_VERSION		1

#define VERSION		((MAJOR_VERSION)|(MINOR_VERSION<<8)|(BUILD_VERSION<<16))
#define VERSION_STR			"Build Version %d.%d.%4.4d\n", MAJOR_VERSION,MINOR_VERSION,BUILD_VERSION

/***********************console define***************************************/
#define CONSOLE		0
//for debug
#define TRACE		printf
//for kernel information output
#define printk		printf

void printfNULL(char *fmt, ...);

#define getchartimeout(buffer, n, timeout)	Uart_GetchTimeout(CONSOLE, (char*)buffer, n, timeout*30)
#define Uart_SendChar(nUart, ch)	do{if((ch)=='\n')	Uart_SendByte((nUart), '\r');	\
									Uart_SendByte((nUart), (ch));	}while(0)
//从控制台所在的串口,获得输入的字符串
//#define GetCommand(string)	Uart_GetString(CONSOLE, string);
//定义标准控制台输出函数
#define CONSOLE_PUTC(ch)	Uart_SendChar(CONSOLE, (ch))
//定义标准控制台输入函数
#define CONSOLE_GETC()	Uart_Getch(CONSOLE)

/***********************System define***************************************/
extern unsigned int PCLK, HCLK, FCLK;

/***********************System param define*********************************/
struct struct_system_param{
	unsigned int magic;
	calibrate_MATRIX  calibrate_matrix;
};

extern struct struct_system_param system_param;

/***********************macro define***************************************/
#define mdelay(n)	hudelay(n*10)

/***********************function define***************************************/
typedef void (*serial_loop_func_t)(void);

/***********************arm define***************************************/
#define FlushCache()		__asm{mcr p15, 0, r0, c7, c7, 0}

/*lib.c*/
void hudelay(int time); //Watchdog Timer is used.

void Port_Init(void);

int GetCommand(char *command, int len);
int Uart_Init(int whichUart,int baud);
void Uart_RxEmpty(int whichUart);
void Uart_TxEmpty(int whichUart);
int Set_UartLoopFunc(serial_loop_func_t func);
int Clear_UartLoopFunc(int index);
char Uart_Getch(int whichUart);
int Uart_GetchTimeout(int whichUart, char* pbuffer, int n, int timeout);
int Uart_Poll(int whichUart);
int Uart_SendByte(int whichUart, int data);
void Uart_GetString(int whichUart, char *string);
int  Uart_GetIntNum(int whichUart);
void Uart_Printf(int whichUart, char *fmt,...);
void Uart_SendString(int whichUart, char *pt);

int Set_UartLoopFunc(serial_loop_func_t func);
int Clear_UartLoopFunc(int index);
void loadsystemParam(void);


#endif
