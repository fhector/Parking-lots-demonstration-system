#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "../ucos-ii/includes.h"               /* uC/OS interface */
#include "../src/GUI/gui.h"
#include "../ucos-ii/add/list.h"

#if USE_MINIGUI==0

#define OSCtrlMemSize	1000
#define OSCtrlblkSize		256

///////////////////////////控件类型/////////////////////
#define CTRLTYPE_LISTCTRL	1	//列表框
#define CTRLTYPE_TEXTCTRL	2	//文本框
#define CTRLTYPE_PICTURECTRL	3	//图片框
#define CTRLTYPE_BUTTONCTRL	4	//按钮
#define CTRLTYPE_WINDOW	100		//窗口

//////////////////////////控件风格/////////////////////
#define CTRL_STYLE_DBFRAME			1	//双重边框
#define CTRL_STYLE_FRAME			2	//单边框
#define CTRL_STYLE_3DUPFRAME		3	//突起3D边框
#define CTRL_STYLE_3DDOWNFRAME		4	//凹陷3D无边框
#define CTRL_STYLE_NOFRAME			5	//无边框

////////////////////////窗口风格////////////////////////
#define WND_STYLE_MODE			0x10000		//有模式窗口
#define WND_STYLE_MODELESS		0x00000		//无模式窗口

#define WND_STYLE_TITLE			0x20000		//有窗口标题

////////////////////////按钮ID/////////////////////////
#define BUTTON_IDOK					1
#define BUTTON_IDCANCEL			2

////////////////////////////////////
typedef struct typeWnd{
	U32 CtrlType;	//控件的类型
	U32 CtrlID;
	structRECT WndRect;	//窗口的位置和大小
	structRECT ClientRect;	//看翱谕户区域
	U32 FontSize;	//窗口的字符大小
	U32 style;		//窗口的的边框风格
	U8 bVisible;	//是否可见
	struct typeWnd* parentWnd;	//控件的父窗口指针
	U8 (*CtrlMsgCallBk)(void*);

	PDC pdc;	//窗口的绘图设备上下文
	U16 Caption[20];	//窗口标题

	List ChildWndList;
	U32 FocusCtrlID;	//子窗口焦点ID
	U32 preParentFocusCtrlID;	//显示窗口之前的父窗口焦点ID
	OS_EVENT* WndDC_Ctrl_mem; //窗口DC控制权
}Wnd, *PWnd;

typedef struct {
	U32 CtrlType;	//控件的类型
	U32 CtrlID;
	structRECT ListCtrlRect;	//控件的位置和大小
	structRECT ClientRect;	//客户区域
	U32 FontSize;	//控件的字符大小
	U32 style;		//控件的的边框风格
	U8 bVisible;	//是否可见
	PWnd parentWnd;	//控件的父窗口指针
	U8 (*CtrlMsgCallBk)(void*);
}OS_Ctrl, *POS_Ctrl;

typedef struct{
	U32 CtrlType;	//控件的类型
	U32 CtrlID;
	structRECT ListCtrlRect;	//列表框的位置和大小
	structRECT ClientRect;	//列表框列表区域
	U32 FontSize;
	U32 style;		//列表框的风格
	U8 bVisible;	//是否可见
	PWnd parentWnd;	//控件的父窗口指针
	U8 (*CtrlMsgCallBk)(void*);

	U16 **pListText;	//列表框所容纳的文本指针
	int ListMaxNum;	//列表框所容纳的最大文本的行数
	int ListNum;		//列表框所容纳的文本的行数
	int ListShowNum;	//列表框所能显示的文本行数
	int CurrentHead;	//列表的表头号
	int CurrentSel;	//当前选中的列表项号
	structRECT ListCtrlRollRect;	//列表框滚动条方框
	structRECT RollBlockRect;	//列表框滚动条滑块方框
}ListCtrl,*PListCtrl;

typedef struct{
	U32 CtrlType;	//控件的类型
	U32 CtrlID;	//控件的ID
	structRECT TextCtrlRect;	//文本框的位置和大小
	structRECT ClientRect;	//客户区域
	U32 FontSize;	//文本框的字符大小
	U32 style;		//文本框的风格
	U8 bVisible;	//是否可见
	PWnd parentWnd;	//控件的父窗口指针
	U8 (*CtrlMsgCallBk)(void*);

	U8 bIsEdit;	//文本框是否处于编辑状态
	char* KeyTable; //文本框的字符映射表
	U16 text[40];	//文本框中的字符块
}TextCtrl,*PTextCtrl;

typedef struct{
	U32 CtrlType;	//控件的类型
	U32 CtrlID;
	structRECT PictureCtrlRect;	//图片框的位置和大小
	structRECT ClientRect;	//客户区域
	U32 FontSize;	//图片框的字符大小
	U32 style;		//图片框的风格
	U8 bVisible;	//是否可见
	PWnd parentWnd;	//控件的父窗口指针
	U8 (*CtrlMsgCallBk)(void*);

	char picfilename[12]; //图片文件名
}PictureCtrl,*PPictureCtrl;

typedef struct {
	U32 CtrlType;	//控件的类型
	U32 CtrlID;
	structRECT ButtonCtrlRect;	//控件的位置和大小
	structRECT ClientRect;	//客户区域
	U32 FontSize;	//控件的字符大小
	U32 style;		//控件的的边框风格
	U8 bVisible;	//是否可见
	PWnd parentWnd;	//控件的父窗口指针
	U8 (*CtrlMsgCallBk)(void*);

	U16 Caption[10];	//按纽标题
}ButtonCtrl, *PButtonCtrl;

void initOSCtrl(void);
U32 SetWndCtrlFocus(PWnd pWnd, U32 CtrlID);	//设置窗口中控件的焦点
U32 GetWndCtrlFocus(PWnd pWnd);

void ReDrawOSCtrl(void);	//绘制所有的操作系统的控件
OS_Ctrl* GetCtrlfromID(PWnd pWnd, U32 ctrlID);
OS_Ctrl* CreateOSCtrl(U32 CtrlID, U32 CtrlType, structRECT* prect, U32 FontSize, U32 style, PWnd parentWnd);
void SetCtrlMessageCallBk(POS_Ctrl pOSCtrl, U8(*CtrlMsgCallBk)(void*));
void OSOnSysMessage(void* pMsg);
void ShowCtrl(OS_Ctrl *pCtrl, U8 bVisible);


PListCtrl CreateListCtrl(U32 CtrlID, structRECT* prect, int MaxNum, U32 FontSize, U32 style, PWnd parentWnd);
void DestoryListCtrl(PListCtrl plistCtrl);
U8 AddStringListCtrl(PListCtrl pListCtrl, U16 string[]);
void ListCtrlReMoveAll(PListCtrl pListCtrl);
void ReLoadListCtrl(PListCtrl pListCtrl,U16* string[],int nstr);
void DrawListCtrl(PListCtrl pListCtrl);
void ListCtrlSelMove(PListCtrl pListCtrl, int moveNum, U8 Redraw);	//列表框高亮度条移，正数下移，负数上移
void ListCtrlOnTchScr(PListCtrl pListCtrl, int x, int y, U32 tchaction);

PTextCtrl CreateTextCtrl(U32 CtrlID, structRECT* prect,  U32 FontSize, U32 style,char* KeyTable, PWnd parentWnd);
void DestoryTextCtrl(PTextCtrl pTextCtrl);
void SetTextCtrlText(PTextCtrl pTextCtrl, U16 *pch, U8 IsRedraw);
U16* GetTextCtrlText(PTextCtrl pTextCtrl);
void DrawTextCtrl(PTextCtrl pTextCtrl);
void AppendChar2TextCtrl(PTextCtrl pTextCtrl, U16 ch, U8 IsReDraw);

void TextCtrlDeleteChar(PTextCtrl pTextCtrl,U8 IsReDraw);
void SetTextCtrlEdit(PTextCtrl pTextCtrl, U8 bIsEdit);
void TextCtrlOnTchScr(PTextCtrl pListCtrl, int x, int y, U32 tchaction);


PPictureCtrl CreatePictureCtrl(U32 CtrlID, structRECT* prect,  char filename[], U32 style, PWnd parentWnd);
void DestoryPictureCtrl(PPictureCtrl pPictureCtrl);
void DrawPictureCtrl(PPictureCtrl pPictureCtrl);

PButtonCtrl CreateButton(U32 CtrlID, structRECT* prect,  U32 FontSize, U32 style, U16 Caption[], PWnd parentWnd);
void DestoryButton(PButtonCtrl pButton);
void DrawButton(PButtonCtrl pButton);
void ButtonOnTchScr(PButtonCtrl pButtonCtrl, int x, int y, U32 tchaction);


PWnd CreateWindow(U32 CtrlID, structRECT* prect,  U32 FontSize, U32 style, U16 Caption[], PWnd parentWnd);
void DestoryWindow(PWnd pWnd);
void ShowWindow(PWnd pwnd, BOOLEAN isShow);
void DrawWindow(PWnd pwnd);
void WndOnTchScr(PWnd pCtrl, int x,int y, U32 tchaction);

#endif //#if USE_MINIGUI==0

#endif
