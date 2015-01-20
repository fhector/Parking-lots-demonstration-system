#ifndef __CAN_H__
#define __CAN_H__

#include "includes.h"
#include "../inc/macro.h"

//CAN poll 函数的返回值
#define CANPOLL_Rev			1	//接收到数据
#define CANPOLL_SendEnd	2	//发送完毕

typedef enum{
	BandRate_125kbps,
	BandRate_250kbps,
	BandRate_500kbps,
	BandRate_1Mbps
}CanBandRate;

typedef struct {
	unsigned int id;	//CAN总线ID
	unsigned char data[8];		//CAN总线数据
	unsigned int dlc;		//数据长度
	BOOL IsExt; 	//是否是扩展总线
	BOOL rxRTR;	//是否是远程帧
}CanData, *PCanData;

/*********************************************************************\
	CAN设备设置接收过滤器结构体
	参数:	IdMask，Mask
			IdFilter，Filter
	是否接收数据按照如下规律:
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
	BOOL IsExt;	//是否是扩展ID
}CanFilter,*PCanFilter;



#define CAN_REVBUFFER_SIZE		100

typedef struct{
	CanData buffer[CAN_REVBUFFER_SIZE];
	OS_EVENT *Rev_mbox;                   //receive mail box
	int nCanRevpos;					//接收缓冲区位置
	int nCanReadpos;					//读取缓冲区位置
}struct_CAN_Buffer;


/*********************************************************************\
	CAN设备初始化函数
	参数:	bandrate，CAN波特率
			LoopBack，是否是LoopBack模式
			pfilter，CAN过滤器结构体指针，
					如果为NULL，则接受所有数据
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
