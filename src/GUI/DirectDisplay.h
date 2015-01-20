#ifndef __DIRECTDISPLAY_H__
#define __DIRECTDISPLAY_H__

#include "../inc/sysconfig.h"

#if USE_MINIGUI==0

#include "figure.h"
#include "display.h"

#if  DIRECT_DISPLAY==1


#define  COLORDEPTH_GRAY             0
//#define COLORDEPTH_256
//#define COLORDEPTH_16

#define SetPixel(pdc, x, y, color)	  Direct_SetPixel(pdc, x, y, color) 
#define ClearScreen()                        Direct_ClearScreen()
#define MoveTo( pdc,  x,  y)              Direct_MoveTo( pdc, x,  y)
#define LineTo( pdc,x,  y)                  Direct_LineTo( pdc,x,  y)
#define DrawSBresenham_Line( pdc,  x1,  y1, x2,  y2)                  Direct_DrawSBresenham_Line( pdc,  x1,  y1, x2,  y2)

#define  FillRect(pdc, left,top , right,  bottom,DrawMode, color)   Direct_FillRect(pdc, left,top , right,  bottom,DrawMode, color)
#define  FillRect2( pdc, rect,DrawMode,color)                                Direct_FillRect2( pdc, rect,DrawMode,color)
#define  Circle( pdc,x0,y0, r)                                                           Direct_Circle( pdc,x0,y0, r)
#define  CharactorOut( pdc, x, y, ch, bunicode,  fnt)                      Direct_CharactorOut( pdc, x, y, ch, bunicode,  fnt)
#define  CharactorOutRect( pdc, x, y, prect, ch, bunicode,  fnt)     Direct_CharactorOutRect( pdc, x, y, prect, ch, bunicode,  fnt)
#define  TextOut(pdc, x,  y,  ch,  bunicode,  fnt)                             Direct_TextOut(pdc, x,  y,  ch,  bunicode,  fnt)
#define  DrawRectFrame( pdc, left, top , right,  bottom)                Direct_DrawRectFrame( pdc, left, top , right,  bottom)
#define  DrawRectFrame2(pdc, rect)                                              Direct_DrawRectFrame2(pdc, rect)
#define  Draw3DRect( pdc, left, top, right,bottom,color1,color2)                Direct_Draw3DRect( pdc, left, top, right,bottom,color1,color2)
#define  ArcTo1(pdc,  x1, y1, R)                                                      Direct_ArcTo1(pdc,  x1, y1, R)
#define  ArcTo2(pdc,  x1, y1, R)                                                      Direct_ArcTo2(pdc,  x1, y1, R)
#define  ArcTo(pdc, x1,  y1,  arctype,  R)                                        Direct_ArcTo(pdc, x1,  y1,  arctype,  R)         

#define  ShowBmp( pdc,  filename, x,  y)                                        Direct_ShowBmp( pdc,  filename, x,  y)



void Direct_SetPixel(PDC pdc, int x, int y, COLORREF color);
void Direct_ClearScreen();
void Direct_SetPixelOR(PDC pdc, int x, int y, COLORREF color);
void Direct_SetPixelAND(PDC pdc, int x, int y, COLORREF color);
void Direct_SetPixelXOR(PDC pdc, int x, int y, COLORREF color);
void Direct_MoveTo(PDC pdc, int x, int y);
void Direct_LineTo(PDC pdc, int x, int y);
void Direct_DrawSBresenham_Line(PDC pdc, int x1, int y1,int x2, int y2);


void Direct_FillRect(PDC pdc, int left,int top ,int right, int bottom,U32 DrawMode, U32 color);
void Direct_FillRect2(PDC pdc, structRECT *rect,U32 DrawMode, U32 color);
void Direct_Circle(PDC pdc,int x0,int y0,int r);


void Direct_CharactorOut(PDC pdc, int* x, int* y, U16 ch, U8 bunicode, U8 fnt);
void Direct_CharactorOutRect(PDC pdc,int * x,int* y,structRECT* prect,U16 ch,U8 bunicode, U8 fnt);
void Direct_TextOut(PDC pdc, int x, int y, U16* ch, U8 bunicode, U8 fnt);

void Direct_DrawRectFrame(PDC pdc, int left,int top ,int right, int bottom);
void Direct_DrawRectFrame2(PDC pdc, structRECT *rect);
void Direct_Draw3DRect(PDC pdc, int left, int top, int right, int bottom,COLORREF color1,COLORREF color2);

void Direct_ArcTo1(PDC pdc, int x1, int y1, int R);
void Direct_ArcTo2(PDC pdc, int x1, int y1, int R);
void Direct_ArcTo(PDC pdc, int x1, int y1, U8 arctype, int R);

void Direct_ShowBmp(PDC pdc, char filename[], int x, int y);
void Direct_Bmpcopy(U32 *pbmp,int width,int length);
#endif

#endif //#if USE_MINIGUI==0


#endif
