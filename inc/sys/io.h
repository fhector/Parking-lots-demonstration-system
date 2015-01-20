/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #说明: 标准输入输出函数
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------
	2004-4-26	创建

\***************************************************************************/
#ifndef __IO_H__
#define __IO_H__

#define _outb(addr, data)		*((volatile unsigned char*)(addr))=(data)
#define _outw(addr, data)		*((volatile unsigned short*)(addr))=(data)
#define _outl(addr, data)		*((volatile unsigned long*)(addr))=(data)

#define _inb(addr)		(*(volatile unsigned char*)(addr))
#define _inw(addr)		(*(volatile unsigned short*)(addr))
#define _inl(addr)		(*(volatile unsigned long*)(addr))

#endif
