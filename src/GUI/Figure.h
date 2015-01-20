#ifndef __FIGURE_STRUCT_H__
#define __FIGURE_STRUCT_H__

#include "../inc/sysconfig.h"
#if USE_MINIGUI==0

#include "../inc/macro.h"

typedef struct {
	int cx;
	int cy;
}structSIZE;

typedef struct {
	int x;
	int y;
}structPOINT;

typedef struct {
	int left;
	int top;
	int right;
	int bottom;
}structRECT;

void CopyRect(structRECT* prect1, structRECT* prect2);
void SetRect(structRECT* prect, int left, int top, int right, int bottom);
void InflateRect(structRECT* prect, int cx,int cy);
void RectOffSet(structRECT* prect, int x,int y);
int GetRectWidth(structRECT* prect);
int GetRectHeight(structRECT* prect);
U8 IsInRect(structRECT *prect, int x, int y);
U8 IsInRect2(structRECT *prect, structPOINT*ppt);

#endif //#if USE_MINIGUI==0

#endif
