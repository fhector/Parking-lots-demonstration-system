#ifndef __OSMESSAGE_H__
#define __OSMESSAGE_H__

#include "../inc/sysconfig.h"
#if USE_MINIGUI==0

#include "../inc/macro.h"
#include "../ucos-ii/add/control.h"

#define OSMessageQSize		20

///////////////////////////Message struct////////////////////////////

typedef struct {
	POS_Ctrl pOSCtrl;	//消息所发到的窗口(控件)
	U32 Message;
	U32 WParam;
	U32 LParam;
}OSMSG, *POSMSG;

#define OSM_KEY								1		//键盘消息
#define OSM_TOUCH_SCREEN					2		//触摸屏消息

#define OSM_SERIAL							100		//串口收到数据的消息

#define OSM_LISTCTRL_SELCHANGE			1001		//列表框的选择被改变的消息
#define OSM_LISTCTRL_SELDBCLICK			1002		//列表框的选择双击消息
#define OSM_BUTTON_CLICK					1003		//单击按钮消息

POSMSG OSCreateMessage(POS_Ctrl pOSCtrl, U32 Message, U32 wparam, U32 lparam);
U8 SendMessage(POSMSG pmsg);
POSMSG WaitMessage(INT16U timeout);
void DeleteMessage(POSMSG pMsg);
void initOSMessage(void);

#endif //#if USE_MINIGUI==0

#endif
