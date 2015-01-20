#include "../inc/macro.h"

#ifndef __TCHSCR_H__
#define __TCHSCR_H__

/////////揖類そ雄釬////////
#define TCHSCR_ACTION_NULL			0	
#define TCHSCR_ACTION_CLICK		1	//揖類そ等僻
#define TCHSCR_ACTION_DBCLICK		2	//揖類そ邧僻
#define TCHSCR_ACTION_DOWN		3	//揖類そ偌狟
#define TCHSCR_ACTION_UP			4	//揖類そ怬れ
#define TCHSCR_ACTION_MOVE		5	//揖類そ痄雄

typedef struct {
	int x;
	int y;
	int action;
}tsdata, *Ptsdata;

void TchScr_GetScrXY(int *x, int *y);
void Touch_Screen_Task(void *Id);		//揖類そ�恄�

#endif //#ifndef __TCHSCR_H__
