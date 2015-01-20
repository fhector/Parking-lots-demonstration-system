#include "DC_step_motor.h"
#include "../inc/EXIO.h"
int stepdata[]={0x10,0x30,0x20,0x60,0x40,0xc0,0x80,0x90};


void init_MotorPort()
{   
    rGPBCON=rGPBCON&0x3ffff0|0xa;
	//Dead Zone=24, PreScalero1=2;
	rTCFG0=(0<<16)|2;

	//divider timer0=1/2;
	rTCFG1=0;

	rTCNTB0= MOTOR_CONT;
	rTCMPB0= MOTOR_MID;
		
	rTCON|=0x2;		//update mode for TCNTB0 and TCMPB0.
	rTCON|=0x19;		//timer0 = auto reload, start. Dead Zone
	rTCON&=~0x02;
}

void SetPWM(int value)
{
	rTCMPB0= MOTOR_MID+value;
	
}

void Step_motor_forward(void) 
	 {   
	     int i=0,j=0;
		 for(j=0;j<32/8;j++)
			{   
				for(i=0;i<=7;i++)
					{
						SETEXIOBITMASK(stepdata[i], 0xf0);
						hudelay(20);
					}
			}
	 }
	
	void Step_motor_negative(void) 
	 {
	     int i=0,j=0;
		 for(j=0;j<32/8;j++)
			{
				for(i=7;i>=0;i--)
					{
						SETEXIOBITMASK(stepdata[i], 0xf0);
						hudelay(20);
					}
			}
	 }
	 
void DCmotor_forward(void)
{
 	SetPWM((900-512)*MOTOR_CONT/1024);
 	//hudelay(10000*time);
 	//SetPWM(0);
}
void DCmotor_stop(void)
{
   SetPWM(0);
}
	 
void DCmotor_negative(void)
{
 	SetPWM((100-512)*MOTOR_CONT/1024);
 	//hudelay(10000*time);
 	//SetPWM(0);
}	 

void store_motor_last(int time)
{
	DCmotor_forward();
	Step_motor_forward();
	hudelay(10000);
	Step_motor_negative(); 
	DCmotor_negative();  
	
}

void take_motor_last1(void) 
{
	DCmotor_forward( );
	Step_motor_forward();
	hudelay(10000);
	Step_motor_negative(); 
	DCmotor_negative( ); 
}

void take_motor_last2(void) 
{
	Step_motor_forward();
	hudelay(10000);
	Step_motor_negative(); 
}









