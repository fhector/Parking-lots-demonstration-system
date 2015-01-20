#ifndef __LIST_H__
#define __LIST_H__

#include "../inc/sysconfig.h"
#if USE_MINIGUI==0

#define OSListMemNum	1000

typedef struct typeList{	//系统控件的链表
	struct typeList* pNextList;
	struct typeList* pPreList;
	void *pData;
}List,*PList;

void initOSList(void);
void AddListNode(PList plist, void* pNode);
void DeleteListNode(PList pList);
PList GetLastList(PList pList);

#endif //#if USE_MINIGUI==0

#endif
