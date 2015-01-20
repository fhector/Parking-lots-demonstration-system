/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/

/***************************************************************************\
    #˵��: C�⺯������ͷ�ļ�
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------����--------------------------------------
	2004-5-2	1��Ϊ���Ժ��ں˵���������TRACE��printk�궨��
				2������mdelay�꣬���뼶��ʱ
				3����Ӱ汾�ŵĶ���MAJOR, MINOR, BUILD VERSION

	2004-4-30	1�����CONSOLE�궨�壬���Զ��崮������Ŀ���̨
				2������CONSOLE_PUTC�꣬��Ϊ��׼����̨����ꡣ
					printf ʱ��fputc����
				3�����Uart_SendChar�������������'\n'���Զ�����'\r'��
					�ʺ��ڿ���̨���

	2004-4-26	����

\***************************************************************************/
#ifndef __LIB_H__
#define __LIB_H__

#include	"io.h"
#include	"sysdrv.h"		//���������ͷ�ļ�
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
//�ӿ���̨���ڵĴ���,���������ַ���
//#define GetCommand(string)	Uart_GetString(CONSOLE, string);
//�����׼����̨�������
#define CONSOLE_PUTC(ch)	Uart_SendChar(CONSOLE, (ch))
//�����׼����̨���뺯��
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
