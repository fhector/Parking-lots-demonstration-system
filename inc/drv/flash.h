/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #˵��: Nand Flash�����ȶ���
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------����--------------------------------------

	2004-11-16	Ϊyaffs�ļ�ϵͳ����˸���Ĵ�������ReadSparePage��ReadPage512��
			WriteSparePage��WritePage512�� CheckPageEreased��
			
	2004-5-2	����

\***************************************************************************/
#ifndef __FLASH_H__
#define __FLASH_H__

#include "../inc/macro.h"

typedef struct _flashinfo{
	int totalBlock;
	int PagePerBlock;
	int blocksize; 
	int totalsize;
}flashinfo;

extern flashinfo nand_flashinfo;

/*Nand flash��������*/
#define NandPageSize		512
#define NandPagetotalSize	528
#define NandSparePageSize	16

#define ReadPage(block, page, pPage) ReadPage512(block, page,pPage)
#define WritePage(block, page, pPage) WritePage512(block, page,pPage)

int NandFlash_init(void);//flash init
int Erase_Block(unsigned int block);
int ReadSparePage(unsigned int block,unsigned int page, unsigned char* pPage);
int ReadPage512(unsigned int block,unsigned int page, unsigned char* pPage);
int WriteSparePage(unsigned int block,unsigned int page, const unsigned char *pPage);
int WritePage512(unsigned int block,unsigned int page,const unsigned char *pPage);
BOOL NandFlashOK(void);
int CheckPageEreased(unsigned int block,unsigned int page);

int Flash_Tools(int argc, char *argv[]);

#endif //__FLASH_H__