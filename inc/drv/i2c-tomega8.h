#ifndef __I2C_TOMEGA8_H_
#define __I2C_TOMEGA8_H_

#define I2COWNER_ADDRESS		(0x10>>1)
#define MEGA8_I2CADDRESS		(0x60)

typedef __packed struct{
	unsigned char cmd;	//(command|(dev_type<<4))
	unsigned char ctrl;
}I2C_control;

#define	ICCARD_COUNT_TYPESEL_OFFSET	2

typedef __packed struct{
	unsigned char cmd;	//(command|(dev_type<<4))
	unsigned char key;
}I2C_kbd;

typedef __packed struct{
	unsigned char cmd;	//(command|(dev_type<<4))
	unsigned char ps2data;
}I2C_PS2;

#define	ICCARD_COUNT_FAILED_OFFSET	2
typedef	unsigned char ICCardErrorCode;

#define ICCARD_COUNT_OFFSET	4	//ic card frame count offset
#define MAX_ICCARD_RWBUFFER		128
typedef __packed struct tagICCardRWBuffer{
	unsigned short address;
	unsigned char cnt;
	unsigned char buffer[MAX_ICCARD_RWBUFFER];
}ICCARD_data;

#define	ICCARD_COUNT_PWD_OFFSET		2
#define	MAX_ICCARD_PWDBUFFER		128

typedef	__packed struct tagICCardPwdBuffer{
	unsigned char cnt;
	unsigned char buffer[MAX_ICCARD_PWDBUFFER];
}ICCARD_PWDDATA;


__packed union tagI2C_ICCard_unionBUF{
	ICCARD_data _ICCardRWBuffer;
	ICCARD_PWDDATA _ICCardPwdBuffer;
	ICCardErrorCode _errorcode;
};

typedef __packed struct{
	unsigned char cmd;	//(command|(dev_type<<4))
	union tagI2C_ICCard_unionBUF _I2C_ICCard_unionBUF;
}I2C_ICCard;
#define	iccard_addr		_I2C_ICCard_unionBUF._ICCardRWBuffer.address
#define	iccard_cnt		_I2C_ICCard_unionBUF._ICCardRWBuffer.cnt
#define	iccard_buf		_I2C_ICCard_unionBUF._ICCardRWBuffer.buffer
#define	iccard_pwdcnt		_I2C_ICCard_unionBUF._ICCardPwdBuffer.cnt
#define	iccard_pwdbuf		_I2C_ICCard_unionBUF._ICCardPwdBuffer.buffer
#define	iccard_errcode	_I2C_ICCard_unionBUF._errorcode

typedef	union {
	unsigned char m_cmd;

	I2C_ICCard m_iccard;
	I2C_kbd	m_kbd;
	I2C_PS2 m_ps2;
	unsigned char m_buffer[1];
}I2C_MEGA8_BUFFER;

#define	BUFFER_TYPE_LEN	(sizeof(unsigned char))


#define GetI2CCmd(cmd)		(cmd&0xf)
#define GetI2C_Devtype(cmd)	(cmd>>4)
#define MakeCmd(type, cmd)	(cmd|(type<<4))

// Device type 
#define DTYPE_ALL			0	//Ð¾Æ¬¿ØÖÆÃüÁî
#define DTYPE_SECURITY		1	//¼ÓÃÜÃüÁî
#define DTYPE_ICCARD		2	//IC¿¨¶ÁÐ´ÃüÁî
#define DTYPE_MKEYB			3	//¾ØÕó¼üÅÌÉ¨ÃèÃüÁî
#define DTYPE_PS2_0			4	//PS2½Ó¿Ú0ÃüÁî
#define DTYPE_PS2_1			5	//PS2½Ó¿Ú2ÃüÁî

// Commands
#define CMD_CTRL_BASE		0x0
#define CMD_CTRL			(CMD_CTRL_BASE+0)	//¿ØÖÆ×Ö
#define CMD_MST_ADDR		(CMD_CTRL_BASE+1)	//Ö÷¿Ø¶ËµØÖ·
#define CMD_GET_MKEY		(CMD_CTRL_BASE+2)	//¶ÁÈ¡É¨Ãè¼üÅÌÂë
#define CMD_GET_TEST1		(CMD_CTRL_BASE+0xa)	//¶ÁÈ¡²âÊÔ¼Ä´æÆ÷

#define CMD_SEC_BASE		0x10
#define CMD_SEC_PASS		(CMD_SEC_BASE+0)
#define CMD_SEC_PASSACK	(CMD_SEC_BASE+1)

#define CMD_ICC_BASE		0x20
#define CMD_ICC_TYPESEL		(CMD_ICC_BASE+0)
#define CMD_ICC_READ		(CMD_ICC_BASE+1)
#define CMD_ICC_WRITE		(CMD_ICC_BASE+2)
#define CMD_ICC_VERIFY		(CMD_ICC_BASE+3)
#define CMD_ICC_FAILED		(CMD_ICC_BASE+4)

#define CMD_MKEYB		0x30
#define CMD_PS2_0		0x40
#define CMD_PS2_1		0x50

#define ICC_FAILED_NULL			0	//Ã»ÓÐ´íÎó
#define ICC_FAILED_NOCARD		1	//IC ¿¨Ã»ÓÐ²åÈë
#define ICC_FAILED_ERRTYPE		2	//´íÎóµÄIC ¿¨ÀàÐÍ
#define ICC_FAILED_BUSY			3	//IC ¿¨Ã¦
#define ICC_FAILED_NOSEL		4	//Î´Ñ¡ÔñIC¿¨ÀàÐÍ
#define ICC_FAILED_READERR		5	//IC ¿¨¶ÁÈ¡´íÎó
#define ICC_FAILED_WRITEERR		6	//IC ¿¨Ð´Èë´íÎó
#define ICC_FAILED_VERIFYERR		7	//IC ¿¨Ð£Ñé´íÎó
#define ICC_FAILED_WAITING		0xff	//IC ¿¨Í¨Ñ¶×´Ì¬µÈ´ý

//ic card type define
#define ICCARD_COMPTYPE_ATMEL		(1<<4)
#define ICCARD_COMPTYPE_SIEMENS	(2<<4)

//atmel 24cxx ic card
#define ICCARD_TYPE_AT24C02		(ICCARD_COMPTYPE_ATMEL|1)
#define ICCARD_TYPE_AT24C04		(ICCARD_COMPTYPE_ATMEL|2)
#define ICCARD_TYPE_AT24C08		(ICCARD_COMPTYPE_ATMEL|3)
#define ICCARD_TYPE_AT24C16		(ICCARD_COMPTYPE_ATMEL|4)
#define ICCARD_TYPE_AT24C32		(ICCARD_COMPTYPE_ATMEL|5)
#define ICCARD_TYPE_AT24C64		(ICCARD_COMPTYPE_ATMEL|6)
#define ICCARD_TYPE_SLE4442		(ICCARD_COMPTYPE_SIEMENS|1)

#define ICCARD_IOCTL_LASTERR		1
#define ICCARD_IOCTL_SELCARD		2
#define	ICCARD_IOCTL_4442VERIFY		3

#define CTRL_MKEn		(1<<3)	//É¨Ãè¼üÅÌ¿ªÆô
#define CTRL_ICEn		(1<<2)	//ic card¿ØÖÆ¿ªÆô
#define CTRL_PS1En		(1<<1)	//ps2 1½Ó¿Ú¿ªÆô
#define CTRL_PS0En		(1)		//ps2 0½Ó¿Ú¿ªÆô

#endif /*#ifndef __I2C_TOMEGA8_H_*/

