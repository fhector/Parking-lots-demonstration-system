/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #˵��: �����ͺ궨��
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------����--------------------------------------
	2004-4-26	����

\***************************************************************************/
#ifndef __MARCO_H__
#define __MARCO_H__

#include "bitfield.h"

#define U32 unsigned int
#define U16 unsigned short
#define S32 int
#define S16 short int
#define U8  unsigned char
#define S8  char
//#define BOOL int
typedef int BOOL;

#define TRUE 	1
#define FALSE 	0
#define OK		0
#define FAIL		-1
#define NULL		0

#define SIZE_1KB		1024ul
#define SIZE_1MB	(SIZE_1KB*SIZE_1KB)
#define SIZE_1GB		(SIZE_1MB*SIZE_1KB)


#define NumberOfArray(array)	(sizeof(array)/sizeof(array[0]))
#define min(x1,x2)	((x1<x2)? x1:x2)
#define max(x1,x2)	((x1>x2)? x1:x2)
#ifndef	ABS
#define ABS(a)		((a)>=0?(a):(-(a)))
#endif

//���number�����λ��1��λ�ã�ͨ��n����
#define GetPosOfFirstOne(number, n)	do{unsigned int tmp=1; for(n=1;(number|tmp)!=number;n++,tmp<<=1);}while(0)

#endif
