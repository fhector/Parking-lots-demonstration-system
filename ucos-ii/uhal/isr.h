/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.5.12
\***************************************************************************/
/***************************************************************************\
    #说明: 中断注册相关函数定义
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------

	2004-5-12	移植

\***************************************************************************/

#ifndef __ISR_H__
#define __ISR_H__

///////////interrupt offset/////////////////////
/* Interrupt Controller */
#define IRQ_EINT0		0	/* External interrupt 0 */
#define IRQ_EINT1		1	/* External interrupt 1 */
#define IRQ_EINT2		2	/* External interrupt 2 */
#define IRQ_EINT3		3	/* External interrupt 3 */
#define IRQ_EINT4_7		4	/* External interrupt 4 ~ 7 */
#define IRQ_EINT8_23		5	/* External interrupt 8 ~ 23 */
#define IRQ_RESERVED6		6	/* Reserved for future use */
#define IRQ_BAT_FLT		7
#define IRQ_TICK		8	/* RTC time tick interrupt  */
#define IRQ_WDT			9	/* Watch-Dog timer interrupt */
#define IRQ_TIMER0		10	/* Timer 0 interrupt */
#define IRQ_TIMER1		11	/* Timer 1 interrupt */
#define IRQ_TIMER2		12	/* Timer 2 interrupt */
#define IRQ_TIMER3		13	/* Timer 3 interrupt */
#define IRQ_TIMER4		14	/* Timer 4 interrupt */
#define IRQ_UART2		15	/* UART 2 interrupt  */
#define IRQ_LCD			16	/* reserved for future use */
#define IRQ_DMA0		17	/* DMA channel 0 interrupt */
#define IRQ_DMA1		18	/* DMA channel 1 interrupt */
#define IRQ_DMA2		19	/* DMA channel 2 interrupt */
#define IRQ_DMA3		20	/* DMA channel 3 interrupt */
#define IRQ_SDI			21	/* SD Interface interrupt */
#define IRQ_SPI0		22	/* SPI interrupt */
#define IRQ_UART1		23	/* UART1 receive interrupt */
#define IRQ_RESERVED24		24
#define IRQ_USBD		25	/* USB device interrupt */
#define IRQ_USBH		26	/* USB host interrupt */
#define IRQ_IIC			27	/* IIC interrupt */
#define IRQ_UART0		28	/* UART0 transmit interrupt */
#define IRQ_SPI1		29	/* UART1 transmit interrupt */
#define IRQ_RTC			30	/* RTC alarm interrupt */
#define IRQ_ADCTC		31	/* ADC EOC interrupt */
#define NORMAL_IRQ_OFFSET	32

/* External Interrupt */
#define IRQ_EINT4		(0 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT5		(1 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT6		(2 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT7		(3 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT8		(4 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT9		(5 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT10		(6 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT11		(7 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT12		(8 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT13		(9 +NORMAL_IRQ_OFFSET) 
#define IRQ_EINT14		(10 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT15		(11 +NORMAL_IRQ_OFFSET)
#define IRQ_EINT16		(12 +NORMAL_IRQ_OFFSET) 
#define IRQ_EINT17		(13 +NORMAL_IRQ_OFFSET) 
#define IRQ_EINT18		(14 +NORMAL_IRQ_OFFSET) 
#define IRQ_EINT19		(15 +NORMAL_IRQ_OFFSET) 
#define IRQ_EINT20		(16 +NORMAL_IRQ_OFFSET) 
#define IRQ_EINT21		(17 +NORMAL_IRQ_OFFSET) 
#define IRQ_EINT22		(18 +NORMAL_IRQ_OFFSET) 
#define IRQ_EINT23		(19 +NORMAL_IRQ_OFFSET)	/* 51 */
#define SHIFT_EINT4_7		IRQ_EINT4_7
#define SHIFT_EINT8_23		IRQ_EINT8_23
#define EXT_IRQ_OFFSET		(20 +NORMAL_IRQ_OFFSET)

/* sub Interrupt */
#define IRQ_RXD0		(0 +EXT_IRQ_OFFSET)
#define IRQ_TXD0		(1 +EXT_IRQ_OFFSET)
#define IRQ_ERR0		(2 +EXT_IRQ_OFFSET)
#define IRQ_RXD1		(3 +EXT_IRQ_OFFSET)
#define IRQ_TXD1		(4 +EXT_IRQ_OFFSET) 
#define IRQ_ERR1		(5 +EXT_IRQ_OFFSET)
#define IRQ_RXD2		(6 +EXT_IRQ_OFFSET)
#define IRQ_TXD2		(7 +EXT_IRQ_OFFSET)
#define IRQ_ERR2		(8 +EXT_IRQ_OFFSET) 
#define IRQ_TC			(9 +EXT_IRQ_OFFSET)  
#define IRQ_ADC_DONE		(10 +EXT_IRQ_OFFSET)	/* 62 */
#define SUB_IRQ_OFFSET		(11 +EXT_IRQ_OFFSET)

#define IRQ_UNKNOWN		SUB_IRQ_OFFSET
#define NR_IRQS			SUB_IRQ_OFFSET	// Maximum # of interrupt  handlers

#define BIT_ALLMSK     	0xffffffff
#define BIT_SUB_ALLMSK	0x7ff

typedef void (*Interrupt_func_t)(int, void*);

void ISR_Init(void);
int SetISR_Interrupt(int vector, void (*handler)(int, void*), void* data);
void ISR_IrqHandler(void);
int set_external_irq(int irq, int edge, int pullup);

void Enable_Irq(int vector);
void Disable_Irq(int vector);

#endif	 //#ifndef __ISR_H__
