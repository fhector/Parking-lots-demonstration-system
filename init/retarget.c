/*
** Copyright (C) ARM Limited, 2001. All rights reserved.
*/


/*
** This implements a 'retarget' layer for low-level IO.  Typically, this
** would contain your own target-dependent implementations of fputc(),
** ferror(), etc.
** 
** This example provides implementations of fputc(), ferror(),
** _sys_exit(), _ttywrch() and __user_initial_stackheap().
**
** Here, semihosting SWIs are used to display text onto the console 
** of the host debugger.  This mechanism is portable across ARMulator,
** Angel, Multi-ICE and EmbeddedICE.
**
** Alternatively, to output characters from the serial port of an 
** ARM Integrator Board (see serial.c), use:
**
**     #define USE_SERIAL_PORT
**
** or compile with 
**
**     -DUSE_SERIAL_PORT
*/

#include <stdio.h>
#include <string.h>
#include <rt_misc.h>
#include <time.h>
#include "../inc/sys/lib.h"

#undef DEBUG
//#define DEBUG
#ifdef DEBUG
#define DPRINTF	printf
#else
#define DPRINTF(...)
#endif

#if (USE_YAFFS==1)

struct __FILE { int handle;   /* Add whatever you need here */};

#define yaffs_Map2File(nfile)		((FILE*)(nfile+1))
#define File_Map2yaffs(cfile)		((int)(cfile)-1)

#else

#endif

FILE __stdin, __stdout, __stderr;


extern unsigned int bottom_of_heap;     /* defined in heap.s */

int fputc(int ch, FILE *f)
{
	/* Place your implementation of fputc here     */
	/* e.g. write a character to a UART, or to the */
	/* debugger console with SWI WriteC            */
	if(f == &__stdout)	//for console out put e.g. printf
		CONSOLE_PUTC(ch);

	return ch;
}


int ferror(FILE *f)
{   /* Your implementation of ferror */
    return EOF;
}


void _sys_exit(int return_code)
{
	for(;;);
}


int __raise(int signal, int argument)//void _ttywrch(int ch)
{
	return 0;
}


__value_in_regs struct __initial_stackheap __user_initial_stackheap(
        unsigned R0, unsigned SP, unsigned R2, unsigned SL)
{
    struct __initial_stackheap config;
    
    config.heap_base = (unsigned int)&bottom_of_heap; // defined in heap.s
                                                      // placed by scatterfile   
    config.stack_base = SP;   // inherit SP from the execution environment

    return config;
}

/*
Below is an equivalent example assembler version of __user_initial_stackheap.

It will be entered with the value of the stackpointer in r1 (as set in init.s), 
this does not need to be changed and so can be passed unmodified out of the 
function. 

    IMPORT bottom_of_heap
    EXPORT __user_initial_stackheap

__user_initial_stackheap    
    LDR   r0,=bottom_of_heap
    MOV   pc,lr
*/

int fclose(FILE * stream)
{
#if (USE_YAFFS==1)
	yaffs_close(File_Map2yaffs(stream));
	return 0;
#else
	CloseOSFile(stream);
	return 0;
#endif
}

FILE *fopen(const char * filename, const char * mode)
{

#if (USE_YAFFS==1)
#define FILE_FLAG_W		1
#define FILE_FLAG_R		2
#define FILE_FLAG_A		4
#define FILE_FLAG_PLUS	8

	const static unsigned int fileoflagTAB[]={	0xff, // 0	xx
		O_WRONLY|O_CREAT|O_TRUNC, // 1->"w"
		O_RDONLY, // 2->"r"
		0xff, // 3->"wr"	xx
		O_WRONLY|O_CREAT|O_APPEND, // 4->"a"
		0xff, // 5->"aw"	xx
		0xff, // 6->"ar"	xx
		0xff, // 7->"awr"	xx
		0xff, // 8->"+"	xx
		O_RDWR|O_CREAT|O_TRUNC, // 9->"w+"
		O_RDWR, // 10->"r+"
		0xff, // 11->"wr+"	xx
		O_RDWR|O_CREAT|O_APPEND, // 12->"a+"
		0xff, // 13->"aw+"	xx
		0xff, // 14->"ar+"	xx
		0xff, // 15->"awr+"	xx
	};

	unsigned int filestatus=0, fileoflag;
	const char *p=mode;
	int ret;
	
	while(*p){
		if(*p=='w')
			filestatus|=FILE_FLAG_W;
		if(*p=='r')
			filestatus|=FILE_FLAG_R;
		if(*p=='a')
			filestatus|=FILE_FLAG_A;
		if(*p=='+')
			filestatus|=FILE_FLAG_PLUS;
		p++;
	}

	fileoflag=fileoflagTAB[filestatus];
	DPRINTF("fopen: %s, Flag: 0x%x\n", filename, fileoflag);

	if(fileoflag==0xff)
		return NULL;

	if((ret=yaffs_open(filename, fileoflag, S_IWRITE|S_IREAD))<0){
		DPRINTF("Open file: %s failed!\n", filename);
		return NULL;
	}
	else{
		DPRINTF("Open file: %s success!\n", filename);
	}
	return yaffs_Map2File(ret);
	
#else	//#if (USE_YAFFS==1)

#ifdef DEBUG
	FILE *ret;
#endif

	//we only support read only mode.
	if(strcmp(mode, "rb")!=0 || mode[0]!='r')
		return NULL;

	DPRINTF("fopen: %s\n", filename);

#ifdef DEBUG
	ret=OpenOSFile(filename , FILEMODE_READ);
	if(ret==NULL)
		DPRINTF("fopen: %s failed\n", filename);
	return ret;
#else
	return OpenOSFile((char*)filename , FILEMODE_READ);
#endif

#endif	//#if (USE_YAFFS==1)
}

FILE *freopen(const char * filename, const char * mode,
		FILE * stream)
{
	DPRINTF("freopen: %s\n", filename);
	fclose(stream);
	return fopen(filename, mode);
}

int fflush(FILE * stream)
{
	DPRINTF("fflush:\n");

	return 0;
}

int fseek(FILE * stream, long int offset, int whence)
{
#if (USE_YAFFS==1)
	return yaffs_lseek(File_Map2yaffs(stream), offset, whence);
	
#else
	if(whence==SEEK_CUR)
		offset+=stream->fileCurpos;
	else if(whence==SEEK_END)
		offset+=stream->filesize;

	DPRINTF("seek: 0x%x\n", offset);

	if(SeekOSFile(stream, offset)!=offset){
		DPRINTF("seek: failed");
		return -1;
	}

	return 0;
#endif	//#if (USE_YAFFS==1)
}

FILE *tmpfile(void)
{
	DPRINTF("tmpfile:\n");
	return NULL;
}

void rewind(FILE * stream)
{
#if (USE_YAFFS==1)
	yaffs_lseek(File_Map2yaffs(stream), 0, SEEK_SET);
#endif
}

int fgetc(FILE * stream)
{
	unsigned char c;

	if(stream == &__stdin)	//for console out put e.g. printf
		return CONSOLE_GETC();


	DPRINTF("fgetc:\n");
	if(fread(&c, 1, 1, stream)!=1)
		return 0;

	return c;
}

size_t fread(void * ptr,size_t size, size_t nmemb, FILE * stream)
{
	int nbyte=size*nmemb;

	DPRINTF("fread: %d byte", nbyte);
#if (USE_YAFFS==1)
	return yaffs_read(File_Map2yaffs(stream), ptr, nbyte);
#else
	return ReadOSFile(stream, ptr, nbyte);
#endif
}

size_t fwrite(const void * ptr,size_t size, size_t nmemb, FILE * stream)
{
#if (USE_YAFFS==1)
	int nbyte=size*nmemb;

	DPRINTF("fread: %d byte", nbyte);
	return yaffs_write(File_Map2yaffs(stream), ptr, nbyte);
#else
	return 0;
#endif
}

long int ftell(FILE * stream)
{
	return 0;
}

int ungetc(int c, FILE * stream)
{
	return 0;
}

time_t time(time_t * timer)
{
	return NULL;
}
