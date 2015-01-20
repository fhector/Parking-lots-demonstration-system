/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #˵��: ������������ӿڶ���
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------����--------------------------------------
	2004-4-26	����

\***************************************************************************/

#ifndef __SERIAL_H__
#define __SERIAL_H__

typedef int (*serial_init_func_t)(int);
typedef int (*serial_read_func_t)(void);
typedef int (*serial_write_func_t)(int);
typedef int (*serial_poll_func_t)(void);	//���ڽ������ݲ�ѯ�������ݵ�ʱ�򷵻�1
typedef int (*serial_flush_input_func_t)(void);
typedef int (*serial_flush_output_func_t)(void);


typedef struct {
	serial_init_func_t init;

	serial_read_func_t read;
	serial_write_func_t write;

	serial_poll_func_t poll;

	serial_flush_input_func_t flush_input;
	serial_flush_output_func_t flush_output;

	int nIsr;		//�жϺ�
} serial_driver_t;

#endif
