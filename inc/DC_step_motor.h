#define PCLK (50700000)
#define MOTOR_SEVER_FRE		1000		//20kHz

#define MOTOR_CONT				(PCLK/2/2/MOTOR_SEVER_FRE)
#define MOTOR_MID				(MOTOR_CONT/2)

#pragma import(__use_no_semihosting_swi)

#define rTCFG0  (*(volatile unsigned *)0x51000000)
#define rTCFG1  (*(volatile unsigned *)0x51000004)
#define rTCNTB0  (*(volatile unsigned *)0x5100000C)
#define rTCMPB0  (*(volatile unsigned *)0x51000010)
#define rTCON  (*(volatile unsigned *)0x51000008)
#define rGPBCON  (*(volatile unsigned *)0x56000010)
#define rGPBUP  (*(volatile unsigned *)0x56000018)
#define rGPBDAT  (*(volatile unsigned *)0x56000014)


void init_MotorPort(void);
void SetPWM(int value);
void Step_motor_forward(void);
void Step_motor_negative(void);
void DCmotor_forward(void);
void DCmotor_negative(void);
void DCmotor_stop(void);
void take_motor_last1(void);
void take_motor_last2(void);
void store_motor_last(int time);