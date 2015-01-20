#include "../inc/macro.h"

#ifndef __TCHSCR_H__
#define __TCHSCR_H__

/////////����������////////
#define TCHSCR_ACTION_NULL			0	
#define TCHSCR_ACTION_CLICK		1	//����������
#define TCHSCR_ACTION_DBCLICK		2	//������˫��
#define TCHSCR_ACTION_DOWN		3	//����������
#define TCHSCR_ACTION_UP			4	//������̧��
#define TCHSCR_ACTION_MOVE		5	//�������ƶ�

typedef struct {
	int x;
	int y;
	int action;
}tsdata, *Ptsdata;

void TchScr_GetScrXY(int *x, int *y);
void Touch_Screen_Task(void *Id);		//����������

#endif //#ifndef __TCHSCR_H__
