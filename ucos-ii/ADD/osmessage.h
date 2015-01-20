#ifndef __OSMESSAGE_H__
#define __OSMESSAGE_H__

#include "../inc/sysconfig.h"
#if USE_MINIGUI==0

#include "../inc/macro.h"
#include "../ucos-ii/add/control.h"

#define OSMessageQSize		20

///////////////////////////Message struct////////////////////////////

typedef struct {
	POS_Ctrl pOSCtrl;	//��Ϣ�������Ĵ���(�ؼ�)
	U32 Message;
	U32 WParam;
	U32 LParam;
}OSMSG, *POSMSG;

#define OSM_KEY								1		//������Ϣ
#define OSM_TOUCH_SCREEN					2		//��������Ϣ

#define OSM_SERIAL							100		//�����յ����ݵ���Ϣ

#define OSM_LISTCTRL_SELCHANGE			1001		//�б���ѡ�񱻸ı����Ϣ
#define OSM_LISTCTRL_SELDBCLICK			1002		//�б���ѡ��˫����Ϣ
#define OSM_BUTTON_CLICK					1003		//������ť��Ϣ

POSMSG OSCreateMessage(POS_Ctrl pOSCtrl, U32 Message, U32 wparam, U32 lparam);
U8 SendMessage(POSMSG pmsg);
POSMSG WaitMessage(INT16U timeout);
void DeleteMessage(POSMSG pMsg);
void initOSMessage(void);

#endif //#if USE_MINIGUI==0

#endif
