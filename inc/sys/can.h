#ifndef __CAN_H__
#define __CAN_H__

#include "includes.h"
#include "../inc/macro.h"

//CAN poll �����ķ���ֵ
#define CANPOLL_Rev			1	//���յ�����
#define CANPOLL_SendEnd	2	//�������

typedef enum{
	BandRate_125kbps,
	BandRate_250kbps,
	BandRate_500kbps,
	BandRate_1Mbps
}CanBandRate;

typedef struct {
	unsigned int id;	//CAN����ID
	unsigned char data[8];		//CAN��������
	unsigned int dlc;		//���ݳ���
	BOOL IsExt; 	//�Ƿ�����չ����
	BOOL rxRTR;	//�Ƿ���Զ��֡
}CanData, *PCanData;

/*********************************************************************\
	CAN�豸���ý��չ������ṹ��
	����:	IdMask��Mask
			IdFilter��Filter
	�Ƿ�������ݰ������¹���:
	Mask	Filter	RevID	Receive
	0		x		x		yes
	1		0		0		yes
	1		0		1		no
	1		1		0		no
	1		1		1		yes
	
\*********************************************************************/
typedef struct{
	unsigned int Mask;
	unsigned int Filter;
	BOOL IsExt;	//�Ƿ�����չID
}CanFilter,*PCanFilter;



#define CAN_REVBUFFER_SIZE		100

typedef struct{
	CanData buffer[CAN_REVBUFFER_SIZE];
	OS_EVENT *Rev_mbox;                   //receive mail box
	int nCanRevpos;					//���ջ�����λ��
	int nCanReadpos;					//��ȡ������λ��
}struct_CAN_Buffer;


/*********************************************************************\
	CAN�豸��ʼ������
	����:	bandrate��CAN������
			LoopBack���Ƿ���LoopBackģʽ
			pfilter��CAN�������ṹ��ָ�룬
					���ΪNULL���������������
\*********************************************************************/
typedef int (*can_init_func_t)(CanBandRate bandrate, BOOL LoopBack, PCanFilter pfilter);

typedef void (*can_Open_func_t)(void);
typedef void (*can_Close_func_t)(void);
typedef int (*can_Poll_func_t)(void);
typedef int (*can_read_func_t)(PCanData data);
typedef int (*can_write_func_t)(PCanData data);
typedef int (*can_flush_input_func_t)(void);
typedef int (*can_flush_output_func_t)(void);


typedef struct {
	can_init_func_t init;
	can_Open_func_t Open;
	can_Close_func_t Close;

	can_read_func_t read;
	can_write_func_t write;
	can_Poll_func_t poll;

	can_flush_input_func_t flush_input;
	can_flush_output_func_t flush_output;

	int nIsr;
} can_driver_t;

void Init_Can(int ndev, CanBandRate bandrate, PCanFilter pfilter);
void Open_Can(int ndev);
void Close_Can(int ndev);

BOOL CanRead(int ndev, PCanData data, int ntimeout);
void CanSend(int ndev, PCanData data);

#endif
