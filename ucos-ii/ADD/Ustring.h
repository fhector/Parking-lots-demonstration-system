
#include "../inc/sysconfig.h"
#if USE_MINIGUI==0

#include "../inc/macro.h"

//int ��Unicode�ַ�����ת��
void Int2Unicode(int number, U16 str[]);
//Unicode�ַ�����int��ת��
int Unicode2Int(U16 str[]);
//char���Ͱ���GB����,��Unicode�ı���ת��
void strChar2Unicode(U16 ch2[], const char ch1[]);
void UstrCpy(U16 ch1[],U16 ch2[]);

#endif //#if USE_MINIGUI==0

