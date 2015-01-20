#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "../inc/macro.h"

#define OS_KeyBoard_Scan_Task		1

#define KEY_DOWN			(1ul<<31)

void Key_init(void);
int KeyBoard_Read(int ndev, BOOL isBlock);

#endif
