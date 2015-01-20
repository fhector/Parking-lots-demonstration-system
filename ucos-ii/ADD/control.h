#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "../ucos-ii/includes.h"               /* uC/OS interface */
#include "../src/GUI/gui.h"
#include "../ucos-ii/add/list.h"

#if USE_MINIGUI==0

#define OSCtrlMemSize	1000
#define OSCtrlblkSize		256

///////////////////////////�ؼ�����/////////////////////
#define CTRLTYPE_LISTCTRL	1	//�б��
#define CTRLTYPE_TEXTCTRL	2	//�ı���
#define CTRLTYPE_PICTURECTRL	3	//ͼƬ��
#define CTRLTYPE_BUTTONCTRL	4	//��ť
#define CTRLTYPE_WINDOW	100		//����

//////////////////////////�ؼ����/////////////////////
#define CTRL_STYLE_DBFRAME			1	//˫�ر߿�
#define CTRL_STYLE_FRAME			2	//���߿�
#define CTRL_STYLE_3DUPFRAME		3	//ͻ��3D�߿�
#define CTRL_STYLE_3DDOWNFRAME		4	//����3D�ޱ߿�
#define CTRL_STYLE_NOFRAME			5	//�ޱ߿�

////////////////////////���ڷ��////////////////////////
#define WND_STYLE_MODE			0x10000		//��ģʽ����
#define WND_STYLE_MODELESS		0x00000		//��ģʽ����

#define WND_STYLE_TITLE			0x20000		//�д��ڱ���

////////////////////////��ťID/////////////////////////
#define BUTTON_IDOK					1
#define BUTTON_IDCANCEL			2

////////////////////////////////////
typedef struct typeWnd{
	U32 CtrlType;	//�ؼ�������
	U32 CtrlID;
	structRECT WndRect;	//���ڵ�λ�úʹ�С
	structRECT ClientRect;	//�����ͻ�����
	U32 FontSize;	//���ڵ��ַ���С
	U32 style;		//���ڵĵı߿���
	U8 bVisible;	//�Ƿ�ɼ�
	struct typeWnd* parentWnd;	//�ؼ��ĸ�����ָ��
	U8 (*CtrlMsgCallBk)(void*);

	PDC pdc;	//���ڵĻ�ͼ�豸������
	U16 Caption[20];	//���ڱ���

	List ChildWndList;
	U32 FocusCtrlID;	//�Ӵ��ڽ���ID
	U32 preParentFocusCtrlID;	//��ʾ����֮ǰ�ĸ����ڽ���ID
	OS_EVENT* WndDC_Ctrl_mem; //����DC����Ȩ
}Wnd, *PWnd;

typedef struct {
	U32 CtrlType;	//�ؼ�������
	U32 CtrlID;
	structRECT ListCtrlRect;	//�ؼ���λ�úʹ�С
	structRECT ClientRect;	//�ͻ�����
	U32 FontSize;	//�ؼ����ַ���С
	U32 style;		//�ؼ��ĵı߿���
	U8 bVisible;	//�Ƿ�ɼ�
	PWnd parentWnd;	//�ؼ��ĸ�����ָ��
	U8 (*CtrlMsgCallBk)(void*);
}OS_Ctrl, *POS_Ctrl;

typedef struct{
	U32 CtrlType;	//�ؼ�������
	U32 CtrlID;
	structRECT ListCtrlRect;	//�б���λ�úʹ�С
	structRECT ClientRect;	//�б���б�����
	U32 FontSize;
	U32 style;		//�б��ķ��
	U8 bVisible;	//�Ƿ�ɼ�
	PWnd parentWnd;	//�ؼ��ĸ�����ָ��
	U8 (*CtrlMsgCallBk)(void*);

	U16 **pListText;	//�б�������ɵ��ı�ָ��
	int ListMaxNum;	//�б�������ɵ�����ı�������
	int ListNum;		//�б�������ɵ��ı�������
	int ListShowNum;	//�б��������ʾ���ı�����
	int CurrentHead;	//�б�ı�ͷ��
	int CurrentSel;	//��ǰѡ�е��б����
	structRECT ListCtrlRollRect;	//�б�����������
	structRECT RollBlockRect;	//�б����������鷽��
}ListCtrl,*PListCtrl;

typedef struct{
	U32 CtrlType;	//�ؼ�������
	U32 CtrlID;	//�ؼ���ID
	structRECT TextCtrlRect;	//�ı����λ�úʹ�С
	structRECT ClientRect;	//�ͻ�����
	U32 FontSize;	//�ı�����ַ���С
	U32 style;		//�ı���ķ��
	U8 bVisible;	//�Ƿ�ɼ�
	PWnd parentWnd;	//�ؼ��ĸ�����ָ��
	U8 (*CtrlMsgCallBk)(void*);

	U8 bIsEdit;	//�ı����Ƿ��ڱ༭״̬
	char* KeyTable; //�ı�����ַ�ӳ���
	U16 text[40];	//�ı����е��ַ���
}TextCtrl,*PTextCtrl;

typedef struct{
	U32 CtrlType;	//�ؼ�������
	U32 CtrlID;
	structRECT PictureCtrlRect;	//ͼƬ���λ�úʹ�С
	structRECT ClientRect;	//�ͻ�����
	U32 FontSize;	//ͼƬ����ַ���С
	U32 style;		//ͼƬ��ķ��
	U8 bVisible;	//�Ƿ�ɼ�
	PWnd parentWnd;	//�ؼ��ĸ�����ָ��
	U8 (*CtrlMsgCallBk)(void*);

	char picfilename[12]; //ͼƬ�ļ���
}PictureCtrl,*PPictureCtrl;

typedef struct {
	U32 CtrlType;	//�ؼ�������
	U32 CtrlID;
	structRECT ButtonCtrlRect;	//�ؼ���λ�úʹ�С
	structRECT ClientRect;	//�ͻ�����
	U32 FontSize;	//�ؼ����ַ���С
	U32 style;		//�ؼ��ĵı߿���
	U8 bVisible;	//�Ƿ�ɼ�
	PWnd parentWnd;	//�ؼ��ĸ�����ָ��
	U8 (*CtrlMsgCallBk)(void*);

	U16 Caption[10];	//��Ŧ����
}ButtonCtrl, *PButtonCtrl;

void initOSCtrl(void);
U32 SetWndCtrlFocus(PWnd pWnd, U32 CtrlID);	//���ô����пؼ��Ľ���
U32 GetWndCtrlFocus(PWnd pWnd);

void ReDrawOSCtrl(void);	//�������еĲ���ϵͳ�Ŀؼ�
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
void ListCtrlSelMove(PListCtrl pListCtrl, int moveNum, U8 Redraw);	//�б����������ƣ��������ƣ���������
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
