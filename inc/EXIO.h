#ifndef __EXIO_H__
#define __EXIO_H__

#define EXIOADDR		(*(volatile unsigned short*)0x08000100)		//bank1

extern unsigned short int EXIOReg;

#define SETEXIOBIT(bit)		do{EXIOReg|=bit; 	EXIOADDR=EXIOReg;}while(0)
#define CLREXIOBIT(bit)		do{EXIOReg&=(~bit); 	EXIOADDR=EXIOReg;}while(0)
#define SETEXIOBITMASK(bit,mask)	do{EXIOReg&=(~mask); EXIOReg|=bit; 	EXIOADDR=EXIOReg;}while(0)
#endif
