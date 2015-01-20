/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #说明: s3c2410 寄存器定义
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------
	2004-4-26	创建

\***************************************************************************/
#ifndef __REG2410_H__
#define __REG2410_H__

#include "../inc/macro.h"
#include "gpio.h"
#include "cpu.h"

#define SDRAM_BASE		0x30000000
#define SDRAM_SIZE		(64*SIZE_1MB)

//串口地址定义
#define UART_CTL_BASE		0x50000000
#define UART0_CTL_BASE		UART_CTL_BASE
#define UART1_CTL_BASE		UART_CTL_BASE + 0x4000
#define UART2_CTL_BASE		UART_CTL_BASE + 0x8000
#define bUART(x, Nb)		__REG(UART_CTL_BASE + (x)*0x4000 + (Nb))
/* Offset */
#define oULCON			0x00	/* R/W, UART line control register */
#define oUCON			0x04	/* R/W, UART control register */
#define oUFCON			0x08	/* R/W, UART FIFO control register */
#define oUMCON			0x0C	/* R/W, UART modem control register */
#define oUTRSTAT		0x10	/* R  , UART Tx/Rx status register */
#define oUERSTAT		0x14	/* R  , UART Rx error status register */
#define oUFSTAT			0x18	/* R  , UART FIFO status register */
#define oUMSTAT			0x1C	/* R  , UART Modem status register */
#define oUTXHL			0x20	/*   W, UART transmit(little-end) buffer */
#define oUTXHB			0x23	/*   W, UART transmit(big-end) buffer */
#define oURXHL			0x24	/* R  , UART receive(little-end) buffer */
#define oURXHB			0x27	/* R  , UART receive(big-end) buffer */
#define oUBRDIV			0x28	/* R/W, Baud rate divisor register */

//时钟
#define CLK_CTL_BASE	0x4C000000
#define bCLKCTL(Nb)		__REG(CLK_CTL_BASE + (Nb))
/* Offset */
#define oLOCKTIME		0x00	/* R/W, PLL lock time count register */
#define oMPLLCON		0x04	/* R/W, MPLL configuration register */
#define oUPLLCON		0x08	/* R/W, UPLL configuration register */
#define oCLKCON			0x0C	/* R/W, Clock generator control reg. */
#define oCLKSLOW		0x10	/* R/W, Slow clock control register */
#define oCLKDIVN		0x14	/* R/W, Clock divider control */
/* Registers */
#define rLOCKTIME		bCLKCTL(oLOCKTIME)
#define rMPLLCON			bCLKCTL(oMPLLCON)
#define rUPLLCON			bCLKCTL(oUPLLCON)
#define rCLKCON			bCLKCTL(oCLKCON)
#define rCLKSLOW			bCLKCTL(oCLKSLOW)
#define rCLKDIVN			bCLKCTL(oCLKDIVN)
/* Fields */
#define fPLL_MDIV		Fld(8,12)
#define fPLL_PDIV		Fld(6,4)
#define fPLL_SDIV		Fld(2,0)
/* bits */
#define CLKCON_SPI		(1<<18)
#define CLKCON_IIS		(1<<17)
#define CLKCON_IIC		(1<<16)
#define CLKCON_ADC		(1<<15)
#define CLKCON_RTC		(1<<14)
#define CLKCON_GPIO		(1<<13)
#define CLKCON_UART2		(1<<12)
#define CLKCON_UART1		(1<<11)
#define CLKCON_UART0		(1<<10)
#define CLKCON_SDI		(1<<9)
#define CLKCON_PWM		(1<<8)
#define CLKCON_USBD		(1<<7)
#define CLKCON_USBH		(1<<6)
#define CLKCON_LCDC		(1<<5)
#define CLKCON_NAND		(1<<4)
#define CLKCON_POWEROFF		(1<<3)
#define CLKCON_IDLE		(1<<2)


// PWM Timer
#define TIMER_BASE		0x51000000
#define rTCFG0			__REG(TIMER_BASE) //Timer 0 configuration
#define rTCFG1			__REG(TIMER_BASE+0x4) //Timer 1 configuration
#define rTCON			__REG(TIMER_BASE+0x8) //Timer control
#define rTCNTB0			__REG(TIMER_BASE+0xc) //Timer count buffer 0
#define rTCMPB0			__REG(TIMER_BASE+0x10) //Timer compare buffer 0
#define rTCNTO0			__REG(TIMER_BASE+0x14) //Timer count observation 0
#define rTCNTB1			__REG(TIMER_BASE+0x18) //Timer count buffer 1
#define rTCMPB1			__REG(TIMER_BASE+0x1c) //Timer compare buffer 1
#define rTCNTO1			__REG(TIMER_BASE+0x20) //Timer count observation 1
#define rTCNTB2			__REG(TIMER_BASE+0x24) //Timer count buffer 2
#define rTCMPB2			__REG(TIMER_BASE+0x28) //Timer compare buffer 2
#define rTCNTO2			__REG(TIMER_BASE+0x2c) //Timer count observation 2
#define rTCNTB3			__REG(TIMER_BASE+0x30) //Timer count buffer 3
#define rTCMPB3			__REG(TIMER_BASE+0x34) //Timer compare buffer 3
#define rTCNTO3			__REG(TIMER_BASE+0x38) //Timer count observation 3
#define rTCNTB4			__REG(TIMER_BASE+0x3c) //Timer count buffer 4
#define rTCNTO4			__REG(TIMER_BASE+0x40) //Timer count observation 4

#define TCON_4_AUTO		(1 << 22)	/* auto reload on/off for Timer 4 */
#define TCON_4_UPDATE		(1 << 21)	/* manual Update TCNTB4 */
#define TCON_4_ONOFF		(1 << 20)	/* 0: Stop, 1: start Timer 4 */
#define TCON_3_AUTO     (1 << 19)       /* auto reload on/off for Timer 3 */
#define TCON_3_INVERT   (1 << 18)       /* 1: Inverter on for TOUT3 */
#define TCON_3_MAN      (1 << 17)       /* manual Update TCNTB3,TCMPB3 */
#define TCON_3_ONOFF    (1 << 16)       /* 0: Stop, 1: start Timer 3 */
#define TCON_2_AUTO     (1 << 15)       /* auto reload on/off for Timer 3 */
#define TCON_2_INVERT   (1 << 14)       /* 1: Inverter on for TOUT3 */
#define TCON_2_MAN      (1 << 13)       /* manual Update TCNTB3,TCMPB3 */
#define TCON_2_ONOFF    (1 << 12)       /* 0: Stop, 1: start Timer 3 */
#define TCON_1_AUTO     (1 << 11)       /* auto reload on/off for Timer 3 */
#define TCON_1_INVERT   (1 << 10)       /* 1: Inverter on for TOUT3 */
#define TCON_1_MAN      (1 << 9)       /* manual Update TCNTB3,TCMPB3 */
#define TCON_1_ONOFF    (1 << 8)       /* 0: Stop, 1: start Timer 3 */
#define TCON_0_AUTO     (1 << 3)       /* auto reload on/off for Timer 3 */
#define TCON_0_INVERT   (1 << 2)       /* 1: Inverter on for TOUT3 */
#define TCON_0_MAN      (1 << 1)       /* manual Update TCNTB3,TCMPB3 */
#define TCON_0_ONOFF    (1 << 0)       /* 0: Stop, 1: start Timer 3 */

// WATCH DOG TIMER
#define WATCHDOG_BASE			0x53000000
#define rWTCON					__REG(WATCHDOG_BASE) //Watch-dog timer mode
#define rWTDAT					__REG(WATCHDOG_BASE+4) //Watch-dog timer data
#define rWTCNT					__REG(WATCHDOG_BASE+8) //Eatch-dog timer count

// INTERRUPT
#define INTERRUPT_BASE			0x4a000000
#define rSRCPND					__REG(INTERRUPT_BASE) //Interrupt request status
#define rINTMOD					__REG(INTERRUPT_BASE+0x4) //Interrupt mode control
#define rINTMSK					__REG(INTERRUPT_BASE+0x8) //Interrupt mask control
#define rPRIORITY				__REG(INTERRUPT_BASE+0xc) //IRQ priority control
#define rINTPND					__REG(INTERRUPT_BASE+0x10) //Interrupt request status
#define rINTOFFSET				__REG(INTERRUPT_BASE+0x14) //Interruot request source offset
#define rSUBSRCPND				__REG(INTERRUPT_BASE+0x18) //Sub source pending
#define rINTSUBMSK				__REG(INTERRUPT_BASE+0x1c) //Interrupt sub mask

//LCD
#define bLCD_CTL(Nb)				__REG(0x4d000000 + (Nb))
#define rLCDCON1				bLCD_CTL(0x00)
#define rLCDCON2				bLCD_CTL(0x04)
#define rLCDCON3				bLCD_CTL(0x08)
#define rLCDCON4				bLCD_CTL(0x0c)
#define rLCDCON5				bLCD_CTL(0x10)
#define rLCDADDR1				bLCD_CTL(0x14)
#define rLCDADDR2				bLCD_CTL(0x18)
#define rLCDADDR3				bLCD_CTL(0x1c)
#define rREDLUT					bLCD_CTL(0x20)
#define rGREENLUT				bLCD_CTL(0x24)
#define rBLUELUT					bLCD_CTL(0x28)
#define rDITHMODE				bLCD_CTL(0x4c)
#define rTPAL					bLCD_CTL(0x50)
#define rLCDINTPND				bLCD_CTL(0x54)
#define rLCDSRCPND				bLCD_CTL(0x58)
#define rLCDINTMSK				bLCD_CTL(0x5c)
#define rLCDLPCSEL				bLCD_CTL(0x60)

//nand flash
#define bNAND_CTL(Nb)			__REG(0x4e000000 + (Nb))
#define rNFCONF					(*(volatile unsigned *)0x4e000000)      //NAND Flash configuration
#define rNFCMD					(*(volatile U8 *)0x4e000004)            //NADD Flash command
#define rNFADDR					(*(volatile U8 *)0x4e000008)            //NAND Flash address
#define rNFDATA					(*(volatile U8 *)0x4e00000c)            //NAND Flash data
#define rNFSTAT					(*(volatile unsigned *)0x4e000010)      //NAND Flash operation status
#define rNFECC					(*(volatile unsigned *)0x4e000014)      //NAND Flash ECC
#define rNFECC0					(*(volatile U8  *)0x4e000014)
#define rNFECC1					(*(volatile U8  *)0x4e000015)
#define rNFECC2					(*(volatile U8  *)0x4e000016)

/****************************************************************\
	iic register
\****************************************************************/
#define bIIC(Nb)					__REG(0x54000000 + (Nb))
#define rIICCON					bIIC(0x00)	//IIC control
#define rIICSTAT					bIIC(0x04)	//IIC status
#define rIICADD					bIIC(0x08)	//IIC address
#define rIICDS					bIIC(0x0c)	//IIC data shift

/****************************************************************\
	spi register
\****************************************************************/
#define bSPI(Nb)					__REG(0x59000000 + (Nb))
#define rSPCON0					bSPI(0x00)
#define rSPSTA0					bSPI(0x04)
#define rSPPIN0					bSPI(0x08)
#define rSPPRE0					bSPI(0x0c)
#define rSPTDAT0				bSPI(0x10)
#define rSPRDAT0				bSPI(0x14)
#define rSPCON1					bSPI(0x20 + 0x00)
#define rSPSTA1					bSPI(0x20 + 0x04)
#define rSPPIN1					bSPI(0x20 + 0x08)
#define rSPPRE1					bSPI(0x20 + 0x0c)
#define rSPTDAT1				bSPI(0x20 + 0x10)
#define rSPRDAT1				bSPI(0x20 + 0x14)

#endif //#ifndef __REG2410_H__
