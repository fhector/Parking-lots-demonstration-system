/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2005.2.26
\***************************************************************************/
/***************************************************************************\
    #说明: iic接口驱动程序头文件
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------

	2005-2-26	创建

\***************************************************************************/

#ifndef __ASM_ARCH_IIC_H__
#define __ASM_ARCH_IIC_H__

#define IICCON_ACKEN			(1<<7)	//IIC-bus acknowledge enable bit.
#define IICCON_CLK512			(1<<6)	// 1 = IICCLK = fPCLK /512
#define IICCON_INTR				(1<<5)	// IIC-Bus Tx/Rx interrupt enable/disable bit.
#define IICCON_INTPEND			(1<<4)	// IIC-bus Tx/Rx interrupt pending flag.
#define IICCON_CLKPRE(x)			FInsrt((x), Fld(4, 0))
#define IICSTAT_MODE_SR		(0<<6)	//Slave receive mode
#define IICSTAT_MODE_ST		(1<<6)	//Slave transmit mode
#define IICSTAT_MODE_MR		(2<<6)	//Master receive mode
#define IICSTAT_MODE_MT		(3<<6)	//Master transmit mode
#define IICSTAT_MODE_MSK		(3<<6)
#define IICSTAT_BUSY			(1<<5)	//IIC-Bus busy signal status bit.(read)
#define IICSTAT_START			(1<<5)	//START signal generation.(write)
#define IICSTAT_OUTEN			(1<<4)	//IIC-bus data output enable
#define IICSTAT_ARBFAILED		(1<<3)	//Bus arbitration failed during serial I/O
#define IICSTAT_SLAVEADDR		(1<<2)	//IIC slave address match
#define IICSTAT_ACK				(1)


void Set_IIC_mode(int nIICCON, int *poldIICCON);
void IIC_init(void);
void IIC_MasterTxStart(char data);
void IIC_MasterTx(char data);
char IIC_MasterRx(int isACK);
void IIC_MasterRxStart(char address);
void IIC_MasterTxStop(void);
void IIC_MasterRxStop(void);
unsigned char IIC_Read(char devaddr, char address);
void IIC_Write(char devaddr, char address, unsigned char data);
void IIC_ReadSerial(char devaddr, char address, unsigned char* pdata, int n);
void IIC_WriteSerial(char devaddr, char address, unsigned char* pdata, int n);
void IIC_Send(char devaddr, const char* pdata, int n);

#endif

