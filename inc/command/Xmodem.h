#ifndef __XMODEM_H__
#define __XMODEM_H__

#include "../inc/macro.h"

#define XMODEM_SOH      0x01
#define XMODEM_STX      0x02
#define XMODEM_ETX      0x03
#define XMODEM_EOT      0x04
#define XMODEM_ENQ      0x05
#define XMODEM_ACK      0x06
#define XMODEM_BS       0x08
#define XMODEM_CR       0x0d
#define XMODEM_LF       0x0a
#define XMODEM_DLE      0x10
#define XMODEM_XON      0x11
#define XMODEM_XOFF     0x13
#define XMODEM_NAK      0x15
#define XMODEM_CAN      0x18	//Cancel
#define XMODEM_CTLZ     0x1a
#define XMODEM_ESC      0x1b

#define XMODEM_TXT      0x01
#define XMODEM_DAT      0x02

int calcrc(unsigned char *ptr, int count);

int XReceiveFile(char * filename,int filetype);
int XTransmitFile(char * filename,int filetype);
int XReceive2Mem(unsigned char *pbuffer, unsigned int* n);

#endif
