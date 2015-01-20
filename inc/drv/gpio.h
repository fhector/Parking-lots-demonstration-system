/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #说明: 对于GPIO控制等相关的宏定义
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------

	2004-8-11	创建

\***************************************************************************/

//GPIO端口的定义
//	8		8		8		8
// | MODE | PULLUP | PORT | OFFSET |

#ifndef __GPIO_H__
#define __GPIO_H__

#define __REG(x)			(*(volatile unsigned int*)(x))

// I/O PORT

#define GPCON(x)		__REG(0x56000000+(x) * 0x10)
#define GPDAT(x)		__REG(0x56000004+(x) * 0x10)
#define GPUP(x)		__REG(0x56000008+(x) * 0x10)

#define GPIO_OFS_SHIFT		0
#define GPIO_PORT_SHIFTT	8
#define GPIO_PULLUP_SHIFT	16 
#define GPIO_MODE_SHIFT		24
#define GPIO_OFS_MASK		0x000000ff
#define GPIO_PORT_MASK		0x0000ff00
#define GPIO_PULLUP_MASK	0x00ff0000
#define GPIO_MODE_MASK		0xff000000
#define GPIO_MODE_IN		(0 << GPIO_MODE_SHIFT)
#define GPIO_MODE_OUT		(1 << GPIO_MODE_SHIFT)
#define GPIO_MODE_ALT0		(2 << GPIO_MODE_SHIFT)
#define GPIO_MODE_ALT1		(3 << GPIO_MODE_SHIFT)
#define GPIO_PULLUP_EN		(0 << GPIO_PULLUP_SHIFT)
#define GPIO_PULLUP_DIS		(1 << GPIO_PULLUP_SHIFT) 

#define PORTA_OFS		0
#define PORTB_OFS		1
#define PORTC_OFS		2
#define PORTD_OFS		3
#define PORTE_OFS		4
#define PORTF_OFS		5
#define PORTG_OFS		6
#define PORTH_OFS		7

#define MAKE_GPIO_NUM(p, o)	((p << GPIO_PORT_SHIFTT) | (o << GPIO_OFS_SHIFT))

#define GRAB_MODE(x)		(((x) & GPIO_MODE_MASK) >> GPIO_MODE_SHIFT)
#define GRAB_PULLUP(x)		(((x) & GPIO_PULLUP_MASK) >> GPIO_PULLUP_SHIFT)
#define GRAB_PORT(x)		(((x) & GPIO_PORT_MASK) >> GPIO_PORT_SHIFTT)
#define GRAB_OFS(x)		(((x) & GPIO_OFS_MASK) >> GPIO_OFS_SHIFT)

#define set_gpio_ctrl(x) \
	do{ GPCON(GRAB_PORT(x)) &= ~(0x3u << (GRAB_OFS(x)*2)); \
	   GPCON(GRAB_PORT(x)) |= (GRAB_MODE(x) << (GRAB_OFS(x)*2)); \
	   GPUP(GRAB_PORT(x)) &= ~(1 << GRAB_OFS(x)); \
	   GPUP(GRAB_PORT(x)) |= (GRAB_PULLUP(x) << GRAB_OFS(x)); }while(0)
#define set_gpio_pullup(x) \
	({ GPUP(GRAB_PORT((x))) &= ~(1 << GRAB_OFS((x))); \
	   GPUP(GRAB_PORT((x))) |= (GRAB_PULLUP((x)) << GRAB_OFS((x))); })
#define set_gpio_pullup_user(x, v) \
	({ GPUP(GRAB_PORT((x))) &= ~(1 << GRAB_OFS((x))); \
	   GPUP(GRAB_PORT((x))) |= ((v) << GRAB_OFS((x))); })
#define set_gpio_mode(x) \
	({ GPCON(GRAB_PORT((x))) &= ~(0x3 << (GRAB_OFS((x))*2)); \
	   GPCON(GRAB_PORT((x))) |= (GRAB_MODE((x)) << (GRAB_OFS((x))*2)); })
#define set_gpio_mode_user(x, v) \
	({ GPCON(GRAB_PORT((x))) & = ~(0x3 << (GRAB_OFS((x))*2)); \
	   GPCON(GRAB_PORT((x))) |= ((v) << (GRAB_OFS((x))*2)); })
#define set_gpioA_mode(x) \
	({ GPCON(GRAB_PORT((x))) &= ~(0x1 << GRAB_OFS((x))); \
	   GPCON(GRAB_PORT((x))) |= (GRAB_MODE((x)) << GRAB_OFS((x))); })
#define read_gpio_bit(x)	((GPDAT(GRAB_PORT((x))) & (1<<GRAB_OFS((x)))) >> GRAB_OFS((x)))
#define read_gpio_reg(x)	(GPDAT(GRAB_PORT((x)))
#define write_gpio_bit(x, v) \
	do{ GPDAT(GRAB_PORT(x)) &= ~(0x1 << GRAB_OFS(x)); \
	   GPDAT(GRAB_PORT(x)) |= ((v) << GRAB_OFS(x)); }while(0)
#define write_gpio_reg(x, v)	GPDAT(GRAB_PORT(x)) = (v)
	

#define GPIO_A0				MAKE_GPIO_NUM(PORTA_OFS, 0)
#define GPIO_A1				MAKE_GPIO_NUM(PORTA_OFS, 1)
#define GPIO_A2				MAKE_GPIO_NUM(PORTA_OFS, 2)
#define GPIO_A3				MAKE_GPIO_NUM(PORTA_OFS, 3)
#define GPIO_A4				MAKE_GPIO_NUM(PORTA_OFS, 4)
#define GPIO_A5				MAKE_GPIO_NUM(PORTA_OFS, 5)
#define GPIO_A6				MAKE_GPIO_NUM(PORTA_OFS, 6)
#define GPIO_A7				MAKE_GPIO_NUM(PORTA_OFS, 7)
#define GPIO_A8				MAKE_GPIO_NUM(PORTA_OFS, 8)
#define GPIO_A9				MAKE_GPIO_NUM(PORTA_OFS, 9)
#define GPIO_A10			MAKE_GPIO_NUM(PORTA_OFS, 10)
#define GPIO_A11			MAKE_GPIO_NUM(PORTA_OFS, 11)
#define GPIO_A12			MAKE_GPIO_NUM(PORTA_OFS, 12)
#define GPIO_A13			MAKE_GPIO_NUM(PORTA_OFS, 13)
#define GPIO_A14			MAKE_GPIO_NUM(PORTA_OFS, 14)
#define GPIO_A15			MAKE_GPIO_NUM(PORTA_OFS, 15)
#define GPIO_A16			MAKE_GPIO_NUM(PORTA_OFS, 16)
#define GPIO_A17			MAKE_GPIO_NUM(PORTA_OFS, 17)
#define GPIO_A18			MAKE_GPIO_NUM(PORTA_OFS, 18)
#define GPIO_A19			MAKE_GPIO_NUM(PORTA_OFS, 19)
#define GPIO_A20			MAKE_GPIO_NUM(PORTA_OFS, 20)
#define GPIO_A21			MAKE_GPIO_NUM(PORTA_OFS, 21)
#define GPIO_A22			MAKE_GPIO_NUM(PORTA_OFS, 22)

#define GPIO_B0				MAKE_GPIO_NUM(PORTB_OFS, 0)
#define GPIO_B1				MAKE_GPIO_NUM(PORTB_OFS, 1)
#define GPIO_B2				MAKE_GPIO_NUM(PORTB_OFS, 2)
#define GPIO_B3				MAKE_GPIO_NUM(PORTB_OFS, 3)
#define GPIO_B4				MAKE_GPIO_NUM(PORTB_OFS, 4)
#define GPIO_B5				MAKE_GPIO_NUM(PORTB_OFS, 5)
#define GPIO_B6				MAKE_GPIO_NUM(PORTB_OFS, 6)
#define GPIO_B7				MAKE_GPIO_NUM(PORTB_OFS, 7)
#define GPIO_B8				MAKE_GPIO_NUM(PORTB_OFS, 8)
#define GPIO_B9				MAKE_GPIO_NUM(PORTB_OFS, 9)
#define GPIO_B10			MAKE_GPIO_NUM(PORTB_OFS, 10)

#define GPIO_C0				MAKE_GPIO_NUM(PORTC_OFS, 0)
#define GPIO_C1				MAKE_GPIO_NUM(PORTC_OFS, 1)
#define GPIO_C2				MAKE_GPIO_NUM(PORTC_OFS, 2)
#define GPIO_C3				MAKE_GPIO_NUM(PORTC_OFS, 3)
#define GPIO_C4				MAKE_GPIO_NUM(PORTC_OFS, 4)
#define GPIO_C5				MAKE_GPIO_NUM(PORTC_OFS, 5)
#define GPIO_C6				MAKE_GPIO_NUM(PORTC_OFS, 6)
#define GPIO_C7				MAKE_GPIO_NUM(PORTC_OFS, 7)
#define GPIO_C8				MAKE_GPIO_NUM(PORTC_OFS, 8)
#define GPIO_C9				MAKE_GPIO_NUM(PORTC_OFS, 9)
#define GPIO_C10			MAKE_GPIO_NUM(PORTC_OFS, 10)
#define GPIO_C11			MAKE_GPIO_NUM(PORTC_OFS, 11)
#define GPIO_C12			MAKE_GPIO_NUM(PORTC_OFS, 12)
#define GPIO_C13			MAKE_GPIO_NUM(PORTC_OFS, 13)
#define GPIO_C14			MAKE_GPIO_NUM(PORTC_OFS, 14)
#define GPIO_C15			MAKE_GPIO_NUM(PORTC_OFS, 15)

#define GPIO_D0				MAKE_GPIO_NUM(PORTD_OFS, 0)
#define GPIO_D1				MAKE_GPIO_NUM(PORTD_OFS, 1)
#define GPIO_D2				MAKE_GPIO_NUM(PORTD_OFS, 2)
#define GPIO_D3				MAKE_GPIO_NUM(PORTD_OFS, 3)
#define GPIO_D4				MAKE_GPIO_NUM(PORTD_OFS, 4)
#define GPIO_D5				MAKE_GPIO_NUM(PORTD_OFS, 5)
#define GPIO_D6				MAKE_GPIO_NUM(PORTD_OFS, 6)
#define GPIO_D7				MAKE_GPIO_NUM(PORTD_OFS, 7)
#define GPIO_D8				MAKE_GPIO_NUM(PORTD_OFS, 8)
#define GPIO_D9				MAKE_GPIO_NUM(PORTD_OFS, 9)
#define GPIO_D10			MAKE_GPIO_NUM(PORTD_OFS, 10)
#define GPIO_D11			MAKE_GPIO_NUM(PORTD_OFS, 11)
#define GPIO_D12			MAKE_GPIO_NUM(PORTD_OFS, 12)
#define GPIO_D13			MAKE_GPIO_NUM(PORTD_OFS, 13)
#define GPIO_D14			MAKE_GPIO_NUM(PORTD_OFS, 14)
#define GPIO_D15			MAKE_GPIO_NUM(PORTD_OFS, 15)

#define GPIO_E0				MAKE_GPIO_NUM(PORTE_OFS, 0)
#define GPIO_E1				MAKE_GPIO_NUM(PORTE_OFS, 1)
#define GPIO_E2				MAKE_GPIO_NUM(PORTE_OFS, 2)
#define GPIO_E3				MAKE_GPIO_NUM(PORTE_OFS, 3)
#define GPIO_E4				MAKE_GPIO_NUM(PORTE_OFS, 4)
#define GPIO_E5				MAKE_GPIO_NUM(PORTE_OFS, 5)
#define GPIO_E6				MAKE_GPIO_NUM(PORTE_OFS, 6)
#define GPIO_E7				MAKE_GPIO_NUM(PORTE_OFS, 7)
#define GPIO_E8				MAKE_GPIO_NUM(PORTE_OFS, 8)
#define GPIO_E9				MAKE_GPIO_NUM(PORTE_OFS, 9)
#define GPIO_E10			MAKE_GPIO_NUM(PORTE_OFS, 10)
#define GPIO_E11			MAKE_GPIO_NUM(PORTE_OFS, 11)
#define GPIO_E12			MAKE_GPIO_NUM(PORTE_OFS, 12)
#define GPIO_E13			MAKE_GPIO_NUM(PORTE_OFS, 13)
#define GPIO_E14			MAKE_GPIO_NUM(PORTE_OFS, 14)
#define GPIO_E15			MAKE_GPIO_NUM(PORTE_OFS, 15)

#define GPIO_F0				MAKE_GPIO_NUM(PORTF_OFS, 0)
#define GPIO_F1				MAKE_GPIO_NUM(PORTF_OFS, 1)
#define GPIO_F2				MAKE_GPIO_NUM(PORTF_OFS, 2)
#define GPIO_F3				MAKE_GPIO_NUM(PORTF_OFS, 3)
#define GPIO_F4				MAKE_GPIO_NUM(PORTF_OFS, 4)
#define GPIO_F5				MAKE_GPIO_NUM(PORTF_OFS, 5)
#define GPIO_F6				MAKE_GPIO_NUM(PORTF_OFS, 6)
#define GPIO_F7				MAKE_GPIO_NUM(PORTF_OFS, 7)

#define GPIO_G0				MAKE_GPIO_NUM(PORTG_OFS, 0)
#define GPIO_G1				MAKE_GPIO_NUM(PORTG_OFS, 1)
#define GPIO_G2				MAKE_GPIO_NUM(PORTG_OFS, 2)
#define GPIO_G3				MAKE_GPIO_NUM(PORTG_OFS, 3)
#define GPIO_G4				MAKE_GPIO_NUM(PORTG_OFS, 4)
#define GPIO_G5				MAKE_GPIO_NUM(PORTG_OFS, 5)
#define GPIO_G6				MAKE_GPIO_NUM(PORTG_OFS, 6)
#define GPIO_G7				MAKE_GPIO_NUM(PORTG_OFS, 7)
#define GPIO_G8				MAKE_GPIO_NUM(PORTG_OFS, 8)
#define GPIO_G9				MAKE_GPIO_NUM(PORTG_OFS, 9)
#define GPIO_G10			MAKE_GPIO_NUM(PORTG_OFS, 10)
#define GPIO_G11			MAKE_GPIO_NUM(PORTG_OFS, 11)
#define GPIO_G12			MAKE_GPIO_NUM(PORTG_OFS, 12)
#define GPIO_G13			MAKE_GPIO_NUM(PORTG_OFS, 13)
#define GPIO_G14			MAKE_GPIO_NUM(PORTG_OFS, 14)
#define GPIO_G15			MAKE_GPIO_NUM(PORTG_OFS, 15)

#define GPIO_H0				MAKE_GPIO_NUM(PORTH_OFS, 0)
#define GPIO_H1				MAKE_GPIO_NUM(PORTH_OFS, 1)
#define GPIO_H2				MAKE_GPIO_NUM(PORTH_OFS, 2)
#define GPIO_H3				MAKE_GPIO_NUM(PORTH_OFS, 3)
#define GPIO_H4				MAKE_GPIO_NUM(PORTH_OFS, 4)
#define GPIO_H5				MAKE_GPIO_NUM(PORTH_OFS, 5)
#define GPIO_H6				MAKE_GPIO_NUM(PORTH_OFS, 6)
#define GPIO_H7				MAKE_GPIO_NUM(PORTH_OFS, 7)
#define GPIO_H8				MAKE_GPIO_NUM(PORTH_OFS, 8)
#define GPIO_H9				MAKE_GPIO_NUM(PORTH_OFS, 9)
#define GPIO_H10			MAKE_GPIO_NUM(PORTH_OFS, 10)

#define GPIO_MODE_TOUT			GPIO_MODE_ALT0
#define GPIO_MODE_nXBACK		GPIO_MODE_ALT0
#define GPIO_MODE_nXBREQ		GPIO_MODE_ALT0
#define GPIO_MODE_nXDACK		GPIO_MODE_ALT0
#define GPIO_MODE_nXDREQ		GPIO_MODE_ALT0
#define GPIO_MODE_LEND			GPIO_MODE_ALT0
#define GPIO_MODE_VCLK			GPIO_MODE_ALT0
#define GPIO_MODE_VLINE			GPIO_MODE_ALT0
#define GPIO_MODE_VFRAME		GPIO_MODE_ALT0
#define GPIO_MODE_VM			GPIO_MODE_ALT0
#define GPIO_MODE_LCDVF			GPIO_MODE_ALT0
#define GPIO_MODE_VD			GPIO_MODE_ALT0
#define GPIO_MODE_IICSDA		GPIO_MODE_ALT0
#define GPIO_MODE_IICSCL		GPIO_MODE_ALT0
#define GPIO_MODE_SPICLK		GPIO_MODE_ALT0
#define GPIO_MODE_SPIMOSI		GPIO_MODE_ALT0
#define GPIO_MODE_SPIMISO		GPIO_MODE_ALT0
#define GPIO_MODE_SDDAT			GPIO_MODE_ALT0
#define GPIO_MODE_SDCMD			GPIO_MODE_ALT0
#define GPIO_MODE_SDCLK			GPIO_MODE_ALT0
#define GPIO_MODE_I2SSDO		GPIO_MODE_ALT0
#define GPIO_MODE_I2SSDI		GPIO_MODE_ALT0
#define GPIO_MODE_CDCLK			GPIO_MODE_ALT0
#define GPIO_MODE_I2SSCLK		GPIO_MODE_ALT0
#define GPIO_MODE_I2SLRCK		GPIO_MODE_ALT0
#define GPIO_MODE_I2SSDI_ABNORMAL	GPIO_MODE_ALT1
#define GPIO_MODE_nSS			GPIO_MODE_ALT1
#define GPIO_MODE_EINT			GPIO_MODE_ALT0
#define GPIO_MODE_nYPON			GPIO_MODE_ALT1
#define GPIO_MODE_YMON			GPIO_MODE_ALT1
#define GPIO_MODE_nXPON			GPIO_MODE_ALT1
#define GPIO_MODE_XMON			GPIO_MODE_ALT1
#define GPIO_MODE_UART			GPIO_MODE_ALT0	
#define GPIO_MODE_TCLK_ABNORMAL		GPIO_MODE_ALT1
#define GPIO_MODE_SPICLK_ABNORMAL	GPIO_MODE_ALT1
#define GPIO_MODE_SPIMOSI_ABNORMAL	GPIO_MODE_ALT1
#define GPIO_MODE_SPIMISO_ABNORMAL	GPIO_MODE_ALT1
#define GPIO_MODE_LCD_PWRDN		GPIO_MODE_ALT1

#define GPIO_CTL_BASE		0x56000000
#define bGPIO(p)				__REG(GPIO_CTL_BASE + (p))
#define rMISCCR				bGPIO(0x80)
#define rDCLKCON			bGPIO(0x84)
#define rEXTINT0				bGPIO(0x88)
#define rEXTINT1				bGPIO(0x8c)
#define rEXTINT2				bGPIO(0x90)
#define rEINTFLT0			bGPIO(0x94)
#define rEINTFLT1			bGPIO(0x98)
#define rEINTFLT2			bGPIO(0x9c)
#define rEINTFLT3			bGPIO(0xa0)
#define rEINTMASK			bGPIO(0xa4)
#define rEINTPEND			bGPIO(0xa8)
#define rGSTATUS0			bGPIO(0xac)
#define rGSTATUS1			bGPIO(0xb0)

#define rGSTATUS2			bGPIO(0xb4)
#define rGSTATUS3			bGPIO(0xb8)
#define rGSTATUS4			bGPIO(0xbc)

#define rGPACON				bGPIO(0x00)
#define rGPADAT				bGPIO(0x04)
//#define rGPBCON				bGPIO(0x10)
//#define rGPBDAT				bGPIO(0x14)
//#define rGPBUP				bGPIO(0x18)
#define rGPCCON				bGPIO(0x20)
#define rGPCDAT				bGPIO(0x24)
#define rGPCUP				bGPIO(0x28)
#define rGPDCON				bGPIO(0x30)
#define rGPDDAT				bGPIO(0x34)
#define rGPDUP				bGPIO(0x38)
#define rGPECON				bGPIO(0x40)
#define rGPEDAT				bGPIO(0x44)
#define rGPEUP				bGPIO(0x48)
#define rGPFCON				bGPIO(0x50)
#define rGPFDAT				bGPIO(0x54)
#define rGPFUP				bGPIO(0x58)
#define rGPGCON				bGPIO(0x60)
#define rGPGDAT				bGPIO(0x64)
#define rGPGUP				bGPIO(0x68)
#define rGPHCON				bGPIO(0x70)
#define rGPHDAT				bGPIO(0x74)
#define rGPHUP				bGPIO(0x78)

/*
 * S3C2410 GPIO edge detection for IRQs:
 * IRQs are generated on Falling-Edge, Rising-Edge, both, low level or higg level.
 * This must be called *before* the corresponding IRQ is registered.
 */
#define EXT_LOWLEVEL		0
#define EXT_HIGHLEVEL		1
#define EXT_FALLING_EDGE	2
#define EXT_RISING_EDGE		4
#define EXT_BOTH_EDGES		6

#endif
