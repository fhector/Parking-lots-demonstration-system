/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #说明:系统配置定义
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------
	2004-5-9	创建

\***************************************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

//使用minigui
#define USE_MINIGUI				0
#define USE_YAFFS				1

#define TOTAL_SIZE				2048*1024

#if 0
#define BOOTLOADER_ADDRESS		0
#define BOOTLOADER_SIZE			(128*1024)
#define PARAM_ADDRESS			(BOOTLOADER_ADDRESS+BOOTLOADER_SIZE)
#define PARAM_MAGIC				(0x134dfae)
#define PARAM_SIZE				(64*1024)
#define SYSTEM_ADDRESS		(PARAM_ADDRESS+PARAM_SIZE)  //128+64
#define SYSTEM_SIZE			(TOTAL_SIZE-BOOTLOADER_SIZE-PARAM_SIZE)

#define _RAM_STARTADDRESS		0x40000000
#endif

#define _USE_OWN_MALLOC	1
#define __UCOSII__			1
//#define __ADSONLY__


#ifdef _USE_OWN_MALLOC

#define HEAPEND  0x40700000

#define USE_DL_PREFIX

#include "own_malloc.h"

/* wrappers for malloc functions */
#define calloc      dlcalloc
#define free        dlfree
#define malloc      dlmalloc
#define memalign    dlmemalign
#define realloc     dlrealloc
#define valloc      dlvalloc

#endif //_USE_OWN_MALLOC


#endif
