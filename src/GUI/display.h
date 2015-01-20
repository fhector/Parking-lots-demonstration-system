#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define DIRECT_DISPLAY			0

#include "../inc/sysconfig.h"
#if USE_MINIGUI==0

#include "figure.h"


#define FONTSIZE_SMALL		1
#define FONTSIZE_MIDDLE		2
#define FONTSIZE_BIG		3

#define FONT_TRANSPARENT	4	//͸������
#define FONT_BLACKBK		8	//�ڵװ���

#define GRAPH_MODE_NORMAL		0x00	//��ͨ��ͼģʽ
#define GRAPH_MODE_OR			0x10	//��ͼģʽ ��
#define GRAPH_MODE_AND		0x20	//��ͼģʽ ��
#define GRAPH_MODE_XOR		0x30	//��ͼģʽ ���
#define GRAPH_MODE_NOR		0x40	//��ͼģʽ ���

#define COLOR_BLACK			0			//��ɫǰ��ɫ
#define COLOR_WHITE			0xffffffff	//��ɫǰ��ɫ

//#define COLOR_BLACK			       0x0000000f			//��ɫǰ��ɫ
//#define COLOR_WHITE			0	//��ɫǰ��ɫ

#define GRAPH_ARC_BACKWARD	0	//��ʱ�뻭Բ
#define GRAPH_ARC_FORWARD		1	//˳ʱ�뻭Բ

#define GRAPH_3D_UP			0	//ͻ���3D���ο�
#define GRAPH_3D_DOWN			1	//���ݵ�3D���ο�

//***********************************************/
#define TEXTOUT_MID_X			1
#define TEXTOUT_MID_Y			2

typedef struct tagBITMAPFILEHEADER {
	U32 bfSize;
	U32 bfReserved12;
	U32 bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	U32 biSize;
	U32 biWidth;
	U32 biHeight;
	U16 biPlanes;
	U16 biBitCount;
	U32 biCompression;
	U32 biSizeImage;
	U32 biXPelsPerMeter;
	U32 biYPelsPerMeter;
	U32 biClrUsed;
	U32 biClrImportant;
} BITMAPINFOHEADER;

typedef U32 COLORREF;

//�����ͼ�豸�ṹ
typedef struct{
	int DrawPointx;
	int DrawPointy; //��ͼ��ʹ�õ������
	int PenWidth;	//���ʿ��
	U32 PenMode; //����ģʽ
	COLORREF PenColor;	//���ʵ���ɫ

	int DrawOrgx;	//��ͼ������ԭ��λ��
	int DrawOrgy;

	int WndOrgx;	//��ͼ�Ĵ�������λ��
	int WndOrgy;

	int DrawRangex;	//��ͼ������Χ
	int DrawRangey;

	structRECT DrawRect;//��ͼ����Ч��Χ

	U8 bUpdataBuffer;	//�Ƿ���º�̨����������ʾ
	U32 Fontcolor; //�ַ���ɫ
}DC,*PDC;

#define RGB(r,g,b)	(((b)<<16)|((g)<<8)|(r))


#if  DIRECT_DISPLAY==0

#define SetPixel(pdc, x, y, color)	  Buffer_SetPixel(pdc, x, y, color) 
#define ClearScreen()                        Buffer_ClearScreen()
#define MoveTo( pdc,  x,  y)              Buffer_MoveTo( pdc, x,  y)
#define LineTo( pdc,x,  y)                  Buffer_LineTo( pdc,x,  y)
#define DrawSBresenham_Line( pdc,  x1,  y1, x2,  y2)                  Buffer_DrawSBresenham_Line( pdc,  x1,  y1, x2,  y2)

#define  FillRect(pdc, left,top , right,  bottom,DrawMode, color)   Buffer_FillRect(pdc, left,top , right,  bottom,DrawMode, color)
#define  FillRect2( pdc, rect,DrawMode,color)                                Buffer_FillRect2( pdc, rect,DrawMode,color)
#define  Circle( pdc,x0,y0, r)                                                           Buffer_Circle( pdc,x0,y0, r)
#define  CharactorOut( pdc, x, y, ch, bunicode,  fnt)                      Buffer_CharactorOut( pdc, x, y, ch, bunicode,  fnt)
#define  CharactorOutRect( pdc, x, y, prect, ch, bunicode,  fnt)     Buffer_CharactorOutRect( pdc, x, y, prect, ch, bunicode,  fnt)
#define  TextOut(pdc, x,  y,  ch,  bunicode,  fnt)                             Buffer_TextOut(pdc, x,  y,  ch,  bunicode,  fnt)
#define  DrawRectFrame( pdc, left, top , right,  bottom)                Buffer_DrawRectFrame( pdc, left, top , right,  bottom)
#define  DrawRectFrame2(pdc, rect)                                              Buffer_DrawRectFrame2(pdc, rect)
#define  Draw3DRect( pdc, left, top, right,bottom,color1,color2)                Buffer_Draw3DRect( pdc, left, top, right,bottom,color1,color2)
#define  ArcTo1(pdc,  x1, y1, R)                                                      Buffer_ArcTo1(pdc,  x1, y1, R)
#define  ArcTo2(pdc,  x1, y1, R)                                                      Buffer_ArcTo2(pdc,  x1, y1, R)
#define  ArcTo(pdc, x1,  y1,  arctype,  R)                                        Buffer_ArcTo(pdc, x1,  y1,  arctype,  R)         

#define  ShowBmp( pdc,  filename, x,  y)                                        Buffer_ShowBmp( pdc,  filename, x,  y)

#endif /*#if  DIRECT_DISPLAY==0*/

/**********************���豸��صĻ�ͼ����**********************/
void Buffer_SetPixel(PDC pdc, int x, int y, COLORREF color);
void Buffer_ClearScreen(void);
void Buffer_MoveTo(PDC pdc, int x, int y);
void Buffer_LineTo(PDC pdc, int x, int y);
void Buffer_DrawSBresenham_Line(PDC pdc, int x1, int y1,int x2, int y2);
void Buffer_FillRect(PDC pdc, int left,int top ,int right, int bottom,U32 DrawMode, U32 color);
void Buffer_FillRect2(PDC pdc, structRECT *rect,U32 DrawMode, U32 color);
void Buffer_Circle(PDC pdc, int x0, int y0, int r);
void Buffer_CharactorOut(PDC pdc, int* x, int* y, U16 ch, U8 bunicode, U8 fnt); //��ʾ�����ַ�
void Buffer_CharactorOutRect(PDC pdc, int* x, int* y, structRECT* prect ,U16 ch, U8 bunicode, U8 fnt); //��ָ�����εķ�Χ����ʾ�����ַ�
void Buffer_TextOut(PDC pdc,int x, int y, U16 *ch, U8 bunicode, U8 fnt);		//��ʾ����
void Buffer_DrawRectFrame(PDC pdc, int left,int top ,int right, int bottom);
void Buffer_DrawRectFrame2(PDC pdc, structRECT *rect);
void Buffer_Draw3DRect(PDC pdc, int left,int top, int right, int botton, COLORREF color1, COLORREF color2);
void Buffer_ArcTo1(PDC pdc, int x1, int y1, int R);
void Buffer_ArcTo2(PDC pdc, int x1, int y1, int R);
void Buffer_ArcTo(PDC pdc, int x1, int y1, U8 arctype, int R);
void Buffer_ShowBmp(PDC pdc, char filename[], int x, int y);
/*******************************************************************************/


void initOSDC(void);
PDC CreateDC(void);
void DestoryDC(PDC pdc);

void SetPixelOR(PDC pdc,int x, int y, COLORREF color);
void SetPixelAND(PDC pdc,int x, int y, COLORREF color);
void SetPixelXOR(PDC pdc, int x, int y, COLORREF color);


int GetFontHeight(U8 fnt);
void TextOutRect(PDC pdc, structRECT* prect, U16* ch, U8 bunicode, U8 fnt, U32 outMode);	//��ָ�����εķ�Χ����ʾ����

U8 SetPenWidth(PDC pdc, U8 width);
U32 SetPenMode(PDC pdc, U32 mode);

int Getdelta1(int x0,int y0, int R);
int Getdelta2(int x0,int y0, int R);

U8 SetLCDUpdata(PDC pdc, U8 isUpdata);
void Draw3DRect2(PDC pdc, structRECT *rect, COLORREF color1, COLORREF color2);
U8 GetPenWidth(PDC pdc);
U32 GetPenMode(PDC pdc);
U32 SetPenColor(PDC pdc, U32 color);
U32 GetPenColor(PDC pdc);
void GetBmpSize(char filename[], int* Width, int *Height);
void SetDrawOrg(PDC pdc, int x,int y, int* oldx, int *oldy);//���û�ͼ��ԭ��
void SetDrawRange(PDC pdc, int x,int y, int* oldx, int *oldy);//���û�ͼ�ķ�Χ

////////////////////����ʱ��ͼ/////////////////
void LineToDelay(PDC pdc, int x, int y, int ticks);
void ArcToDelay(PDC pdc, int x1, int y1, U8 arctype, int R, int ticks);

#endif	//#if USE_MINIGUI==0

#endif
