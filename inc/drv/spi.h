/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2005.2.26
\***************************************************************************/
/***************************************************************************\
    #说明: spi接口驱动程序
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------

	2005-2-26	创建

\***************************************************************************/
#ifndef __ASM_ARCH_SPI_H__
#define __ASM_ARCH_SPI_H__

#define fSPCON_SMOD	Fld(2,5)	/* SPI Mode Select */
#define SPCON_SMOD	FMsk(fSPCON_SMOD)
#define SPCON_SMOD_POLL	FInsrt(0x0, fSPCON_SMOD)	/* polling mode */
#define SPCON_SMOD_INT	FInsrt(0x1, fSPCON_SMOD)	/* interrupt mode */
#define SPCON_SMOD_DMA	FInsrt(0x2, fSPCON_SMOD)	/* DMA mode */
#define SPCON_ENSCK	(1 << 4)	/* Enable SCK */
#define SPCON_MSTR	(1 << 3)	/* Master/Slave select
					   0: slave, 1: master */
#define SPCON_CPOL	(1 << 2)	/* Clock polarity select
					   1: active low, 0: active high */
#define SPCON_CPOL_LOW	(1 << 2)
#define SPCON_CPOL_HIGH	(0 << 2)
#define SPCON_CPHA	(1 << 1)	/* Clock Phase Select
					   0: format A, 1: format B */
#define SPCON_CPHA_FMTA	(0 << 1)
#define SPCON_CPHA_FMTB	(1 << 1)
#define SPCON_TAGD	(1 << 0)	/* Tx auto garbage data mode enable
			in normal mode, you only want to receive data,
					you should tranmit dummy 0xFF data */

#define SPSTA_DCOL	(1 << 2)	/* Data Collision Error */
#define SPSTA_MULF	(1 << 1)	/* Multi Master Error */
#define SPSTA_READY	(1 << 0)	/* data Tx/Rx ready */

#define SPPIN_ENMUL	(1 << 2)	/* Multi Master Error detect Enable */
#define SPPIN_KEEP	(1 << 0)	/* Master Out keep */


void SPISend ( unsigned char val, int channel );
unsigned char SPIRecv ( int channel );
void Set_SIO_mode(int channel, int nSPCON, int nSPPRE, int SPPIN,
		int *poldnSPCON, int *poldnSPPRE, int *poldSPPIN);

void SPI_initIO(int channel);

__inline static unsigned char SendReadData(unsigned char data, int ch)
{
	SPISend(data, ch);
	return SPIRecv(ch);
}


#endif

