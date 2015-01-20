/***************************************************************************\
	Copyright (c) , All rights reserved.
	
\***************************************************************************/
/***************************************************************************\
    #说明: C  main 函数，ucos-ii初始化等定义
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------
	
\***************************************************************************/

#include"../ucos-ii/includes.h"               /* uC/OS interface */
#include "../ucos-ii/add/osaddition.h"
#include "../ucos-ii/arch/os_cpu.h"
//#include "../inc/drivers.h"
#include "../inc/sys/lib.h"
#include "../src/gui/gui.h"
#include <string.h>
#include <stdio.h>
//#include "../ucos-ii/ADD/osmessage.h"

/************************************/
/* 移植时的头文件 */

#include "../inc/car_store_take.h"
#include "../inc/DC_step_motor.h"
#include "../inc/car_AD.h"
/************************************/


#pragma import(__use_no_semihosting_swi)  // ensure no functions that use semihosting 


///******************任务定义***************///

OS_STK Main_Stack[STACKSIZE]={0, };   //Main_Test_Task堆栈
void Main_Task(void *Id);             //Main_Test_Task
#define Main_Task_Prio     12

OS_STK test_Stack[STACKSIZE]={0, };   //test_Test_Task堆栈
void test_Task(void *Id);             //test_Test_Task
#define test_Task_Prio     15

/***********************************************/
//定义每个车位图片在ucos下得存储路径
char pic_path[][30]={"/sys/ucos/0.bmp",
"/sys/ucos/1.bmp","/sys/ucos/2.bmp",
"/sys/ucos/3.bmp","/sys/ucos/4.bmp",
"/sys/ucos/5.bmp","/sys/ucos/6.bmp",
"/sys/ucos/7.bmp","/sys/ucos/8.bmp",
"/sys/ucos/9.bmp"};

//定义小车图片在ucos下得存储路径
char car_path[] = "/sys/ucos/car1.bmp";
char sys_name[] = "/sys/ucos/car0.bmp";
char car_empty_path[] = "/sys/car2.bmp";
int carStatArray[2][5]={0,0,0,0,0,0,0,0,0,0};

//图片位置的计算

#define Start_posi_x (112*4)     			//定义起始x坐标 所有图片以这个作为起始点
#define Start_posi_y (car_row1+145*1)          //(-90)		//定义起始y坐标 所有图片以这个作为起始点

#define pic_weigh		112     //图片的宽
#define pic_high		145		//图片的高度
#define car_row1       0
#define car_row2       145
#define road_line_y1		(car_row1+pic_high*2+20)     //roadline1 的坐标
#define road_line_y2		(road_line_y1+20)	//roadline2 的坐标
#define mv_len      2    //车每次移动长度
#define dly_time    500    //车每次移动停顿的时间
/****************************************************/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PTextCtrl pTextCtrl;//文本框结构控件指针
PTextCtrl pTextCtrl2;
PTextCtrl pTextCtrl3;
#define ID_MainTextCtrl 101//文本框控件ID
#define ID_MainTextCtrl2 102
#define ID_MainTextCtrl3 103
char carpasswd[10][6];

U16 str_num[20];
U16 str0[50]={0x76F4,0x6D41,0x7535,0x673A};       //
U16 str1[50]={0x76F4,0x6D41,0x7535,0x673A,0x505C,0x6B62};
U16 str2[50]={0x8F93,0x5165,0x786E,0x5B9A,0x952E,0x7ed3,0x675f};
U16 str3[50]={0x8BF7,0x8F93,0x5165,0x5BC6,0x7801};
U16 str4[50]={0x8BF7,0x8F93,0x5165,0x5B58,0x8F66,0x2F,0x53D6,0x8F66,0x6307,0x4EE4};
U16 str5[50]={0x8F66,0x79F0,0x91CD,0x672A,0x901A,0x8FC7,0x2C,0x4E0D,0x80FD,0x505C,0x8F66};
U16 str6[50]={0x8F66,0x79F0,0x91CD,0x901A,0x8FC7,0x20,0x8F93,0x5165,0x8F66,0x53F7,0x3A};
U16 str7[50]={0x6B64,0x5904,0x6709,0x8F66};//此处有车
U16 str17[50]={0x6B64,0x5904,0x65E0,0x8F66};//此处无车
U16 str8[50]={0x8F93,0x5165,0x975E,0x6CD5};
U16 str9[50]={0x8F93,0x5165,0x5BC6,0x7801};
U16 str10[50]={0x5BC6,0x7801,0x9519,0x8BEF,0xFF01};
U16 str11[50]={0x6307,0x4EE4,0x975E,0x6CD5,0xFF0C,0x8BF7,0x8F93,0x5165,0x5B58,0x8F66,0x2F,0x53D6,0x8F66,0x6307,0x4EE4};
U16 str12[50]={0x8F93,0x5165,0x8F66,0x53F7,0x3A};
//U16 str13[50]={0x5218,0x7389,0x5764,0x20,0x20,0x674E,0x56FD,0x6770,0x20,0x20,0x5F20,0x6CFD,0x5C27,0x20,0x20,0x5218,0x5A77,0x20,0x20,0x9648,0x68EE,0x68EE,0x20,0x20,0x20};
U16 str14[50]={0x6b63,0x5728,0x5b58,0x8f66,0x8bf7,0x7a0d,0x540e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e};  //正在存车请稍后******
U16 str15[50]={0x6b63,0x5728,0x53d6,0x8f66,0x8bf7,0x7a0d,0x540e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e};  //正在取车请稍后******
U16 str16[50]={0x20};  //******
void CreateText(U16 STR[])
{
	structRECT rect;//定义矩形框结构  
	SetRect(&rect, 100,380,300,420);//设置PID参数轴1P的文本框
	pTextCtrl=CreateTextCtrl(ID_MainTextCtrl, &rect, FONTSIZE_MIDDLE,CTRL_STYLE_NOFRAME, NULL, NULL);//创建文本框
	SetWndCtrlFocus(NULL, ID_MainTextCtrl);//将焦点移到文本框中
	SetTextCtrlText(pTextCtrl, STR,TRUE);//设置文本框内容
}
///////////////////////////////////////////////////////////////////////////////////////////////
void CreateText2(U16 STR[])
{
	structRECT rect2;//定义矩形框结构  
	SetRect(&rect2, 300,380,400,420);//设置PID参数轴1P的文本框
	pTextCtrl2=CreateTextCtrl(ID_MainTextCtrl2, &rect2, FONTSIZE_MIDDLE,CTRL_STYLE_NOFRAME, NULL, NULL);//创建文本框
	SetWndCtrlFocus(NULL, ID_MainTextCtrl2);//将焦点移到文本框中
	SetTextCtrlText(pTextCtrl2, STR,TRUE);//设置文本框内容
}
void CreateText3(U16 STR[])
{
	structRECT rect3;//定义矩形框结构  
	SetRect(&rect3, 100,420,400,480);//设置PID参数轴1P的文本框
	pTextCtrl3=CreateTextCtrl(ID_MainTextCtrl3, &rect3, FONTSIZE_MIDDLE,CTRL_STYLE_NOFRAME, NULL, NULL);//创建文本框
	SetWndCtrlFocus(NULL, ID_MainTextCtrl3);//将焦点移到文本框中
	SetTextCtrlText(pTextCtrl3, STR,TRUE);//设置文本框内容
}
/**************已经定义的OS任务*************
#define SYS_Task_Prio				1
#define Touch_Screen_Task_Prio		9
#define Main_Task_Prio     12
#define Key_Scan_Task_Prio      58
#define Lcd_Fresh_prio           59
#define Led_Flash_Prio           60

*********************************************

int car_flag;

/*****************事件定义*****************/



////********************************************
//显示单个车位图像
void DrawPhoto(PDC pdc,int i,int j)
{
	int x,y;
	x = i;
	y = j;
	ShowBmp(pdc, pic_path[i*5+j], Start_posi_x-pic_weigh*j, Start_posi_y-pic_high*i );//显示没有车的图片
	
}
//显示车库图像
void FillPhoto(PDC pdc)
{
	int i,j,x,y;
	//int oldx,oldy;//保存原来坐标系位置
	for( i=0; i<2; i++)
	{
		for( j=0; j<5;j++)
		{
			x = i;
			y = j;
			if( carStatArray[i][j]==0 )
			{
				DrawPhoto( pdc, i, j);//显示没有车的图片
			}
			else
			{

				DrawPhoto( pdc, i, j);
				ShowBmp(pdc, car_path, Start_posi_x-pic_weigh*y, Start_posi_y-pic_high*x );//显示有车的图片
			}
		}
	}
}

//显示道路的函数
void draw_car_road1(PDC pdc)
{
	int oldx,oldy;//保存原来坐标系位置
	SetDrawOrg(pdc, 0,road_line_y1, &oldx, &oldy); //设置绘图原点为road_line1的起点
	LineTo(pdc,pic_weigh*5, 0);//画线
	MoveTo(pdc, 0, 60);//移动
	LineTo(pdc, pic_weigh*5, 60);//画线
	SetDrawOrg(pdc, 0,0, &oldx, &oldy); //设置绘图原点为road_line1的起点
	
}

void draw_car_road(PDC pdc)
{
	int oldx,oldy;//保存原来坐标系位置
	//SetDrawOrg(pdc, 0,road_line_y1, &oldx, &oldy); //设置绘图原点为road_line1的起点
	MoveTo(pdc, 0, road_line_y1);//移动
	LineTo(pdc,pic_weigh*5, road_line_y1);//画线
	SetDrawOrg(pdc, 0,0, &oldx, &oldy); //设置绘图原点为road_line1的起点
	
}

//存车函数
void save_car(PDC pdc,int car_num)
{
	//int car_num_sum=0;  //现在存的总的车数量
	int car_num_tmp;
	int i;
	/*for( i=0; i<2; i++)
	{
		for( j=0; j<5;j++)
		{
			car_num_sum+=carStatArray[i][j];		//计算现在存的总的车数量
		}
	}
	if(car_num_sum==9)
		return 0;*/
		//printf("go in savecar:ok!");
		printf("in savecar in");
	if(car_num<=4)
		movecarin(pdc,car_num);                       //车号小于4直接存车
	else
	{
		printf("in savecar in1");
		car_num_tmp=car_num-5;
		if(!carStatArray[0][car_num_tmp])        //判断对应底层是否为空
		{	movecarin(pdc,car_num_tmp); 
			mvcarup(pdc,car_num_tmp);    //车上升
		}
		else
		{
			for(i=1;i<=4;i++)     //移出底层空车位
			{
				if((!carStatArray[0][car_num_tmp+i])&&((car_num_tmp+i)<=4))  //判断左边第一个车位是否为空
				{	
					mvcarleftn(pdc,car_num_tmp,i);//左移
					movecarin(pdc,car_num_tmp);
					printf("in savecar in2");
					mvcarup(pdc,car_num_tmp);    //车上升
					mvcarrightn(pdc,car_num_tmp+i,i);//车右移
					break;
				}
				else if((!carStatArray[0][car_num_tmp-i])&&((car_num_tmp-i)>=0))//判断右边第一个车位是否为空
				{	
					mvcarrightn(pdc,car_num_tmp,i);		//车右移
					movecarin(pdc,car_num_tmp);
					mvcarup(pdc,car_num_tmp);          //车上升
					mvcarleftn(pdc,car_num_tmp-i,i);		//左移
					break;
				}
			}
		}
		//mvcarup(car_num_tmp);          
	}
	
}

//取车函数
int take_car(PDC pdc,int car_num)
{
	
	int car_num_tmp;
	int i;
	
	if(car_num<=4)
		movecarout(pdc,car_num);                       //车号小于4直接取车
	else
	{
		car_num_tmp=car_num-5;
		if(!carStatArray[0][car_num_tmp])        //判断对应底层是否为空
		{	 
			mvcardown(pdc,car_num_tmp);    //车下降
			movecarout(pdc,car_num_tmp);
		}
		else
		{
			for(i=1;i<=4;i++)     //移出底层空车位
			{
				if((!carStatArray[0][car_num_tmp+i])&&((car_num_tmp+i)<=4))  //判断左边第一个车位是否为空
				{	
					mvcarleftn(pdc,car_num_tmp,i);//左移
					
					mvcardown(pdc,car_num_tmp);    //车下降
					movecarout(pdc,car_num_tmp);
					mvcarrightn(pdc,car_num_tmp+i,i);//车右移
					break;
				}
				else if((!carStatArray[0][car_num_tmp-i])&&((car_num_tmp-i)>=0))//判断右边第一个车位是否为空
				{	
					mvcarrightn(pdc,car_num_tmp,i);		//车右移
					
					mvcardown(pdc,car_num_tmp);          //车下降
					movecarout(pdc,car_num_tmp);
					mvcarleftn(pdc,car_num_tmp-i,i);		//左移
					break;
				}
			}
		}
		//mvcarup(car_num_tmp);          
	}
	
}

//直接把车存到底层函数,car_num表示底层车位
int movecarin(PDC pdc,int car_num)
{
	//int oldx,oldy;//保存原来坐标系位置
	//int i,j;
	int car_x=0;
	int car_y=road_line_y1+5;
    ///printf("go in movecarin111:ok!");
	ShowBmp(pdc, car_path, 0, car_y);    //显示开始时车第一张图片
	//printf("go in movecarin222:ok!");
	while(car_x<=(Start_posi_x-pic_weigh*car_num))
	{
		ShowBmp(pdc, car_empty_path, car_x, car_y );  //清除车上次图片
		car_x=car_x+mv_len;
		ShowBmp(pdc, car_path, car_x, car_y);   //显示车新的位置图片
		OSTimeDly(dly_time);
	}
	while(car_y>=car_row2)                         //底层y的初始位置
	{
		//FillPhoto();                            //重新画车库
		DrawPhoto( pdc, 0, car_num);
		//draw_car_road(pdc);                         //重新画车道
		       
		//draw_car_road(pdc);                         //重新画车道
		ShowBmp(pdc, car_empty_path, car_x, car_y);  //清除车上次图片
		car_y=car_y-mv_len;
		ShowBmp(pdc, car_path, car_x, car_y );   //显示车新的位置图片
		OSTimeDly(dly_time);
		//draw_car_road(pdc);                         //重新画车道
	}
	carStatArray[0][car_num]=1;              //标志位添加
	FillPhoto(pdc);	
	OSTimeDly(dly_time);
}

//直接把车从底层开出函数,car_num表示底层车位
int movecarout(PDC pdc,int car_num)
{
	//int oldx,oldy;//保存原来坐标系位置
	//int i,j;draw_car_road(PDC pdc)
	int car_x=Start_posi_x-pic_weigh*car_num;
	int car_y=car_row2;
	
	while(car_y<=road_line_y1+5)                         //底层y的初始位置
	{
		//FillPhoto();                            //重新画车库       
		DrawPhoto( pdc, 0, car_num);
		draw_car_road(pdc);                         //重新画车道
		
		ShowBmp(pdc, car_empty_path, car_x, car_y);  //清除车上次图片
		car_y=car_y+mv_len;
		ShowBmp(pdc, car_path, car_x, car_y );   //显示车新的位置图片
		OSTimeDly(dly_time);
		//draw_car_road(pdc);                         //重新画车道
	}
	carStatArray[0][car_num]=0;              //标志位添加
	FillPhoto(pdc);
    while(car_x>=0)
	{
		ShowBmp(pdc, car_empty_path, car_x, car_y );  //清除车上次图片
		car_x=car_x-mv_len;
		ShowBmp(pdc, car_path, car_x, car_y);   //显示车新的位置图片
		OSTimeDly(dly_time);
	}
	ShowBmp(pdc, car_empty_path, car_x, car_y);
		
}

//车辆左移n个车位，car_num代表移动的车号，n代表需移动几个车
int mvcarleftn(PDC pdc,int car_num,int n)
{
	int i;
	for(i=1;i<=n;i++)
	{
		mvcarleft1(pdc, car_num+n-i,+1);
	}
}
//车辆右移n个车位
int mvcarrightn(PDC pdc,int car_num,int n)
{
	int i;
	for(i=1;i<=n;i++)
	{
		mvcarleft1( pdc,car_num-(n-i),-1);
	}
}

//车辆平移1个车位，car_num代表移动的车号,car_direction表示移动方向+1为左移，-1为右移
int mvcarleft1(PDC pdc,int car_num,int car_direction)
{
	//int oldx,oldy;//保存原来坐标系位置
	//int i,j;
	int car_x=Start_posi_x-pic_weigh*car_num;
	int car_y=car_row2;
	
	carStatArray[0][car_num]=0;      //标志位清除
	//DCmotor_negative();//DCmotor_forward();DCmotor_stop();
	if(car_direction==1)
	{	
		printf("in savecar dc");
	    DCmotor_negative();
	    printf("in savecar dc2");
	    
	    while(car_x>=(Start_posi_x-pic_weigh*(car_num+car_direction)))
		{
			DrawPhoto( pdc, 0, car_num);
			DrawPhoto( pdc, 0, car_num+1);
			ShowBmp(pdc, car_empty_path, car_x, car_y );  //清除车上次图片
			car_x=car_x-mv_len;
			ShowBmp(pdc, car_path, car_x, car_y);   //显示车新的位置图片
			OSTimeDly(dly_time);
			//FillPhoto();                            //重新画车库
		}
	}
	else
	{	printf("in savecar dd1\n");
	    DCmotor_forward();
	    CreateText(str0);
	    printf("in savecar dd2\n");
	   // hudelay(100000);
	   // DCmotor_stop();
	    printf("in savecar dd3\n");
	    while(car_x<=(Start_posi_x-pic_weigh*(car_num+car_direction)))
		{
			DrawPhoto( pdc, 0, car_num);
			DrawPhoto( pdc, 0, car_num-1);
			printf("in show dd3\n");
			ShowBmp(pdc, car_empty_path, car_x, car_y );  //清除车上次图片
			printf("in show dd4\n");
			car_x=car_x+mv_len;
			ShowBmp(pdc, car_path, car_x, car_y);   //显示车新的位置图片
			printf("in show dd5\n");
			OSTimeDly(dly_time);
			//hudelay(dly_time*1000);
			printf("in show dd6\n");
			//FillPhoto();                            //重新画车库
			printf("in savecar dd4\n");
		}
	}
	carStatArray[0][car_num+car_direction]=1;              //标志位添加
	FillPhoto(pdc);	
	printf("in savecar dd5\n");
	//printf("DC电机停止\n");
	DCmotor_stop();
	CreateText(str1);
}

//车辆上移
int mvcarup(PDC pdc,int car_num)
{
	//int oldx,oldy;//保存原来坐标系位置
	//int i,j;
	int car_x=Start_posi_x-pic_weigh*car_num;
	int car_y=car_row2;
	
	carStatArray[0][car_num]=0;      //标志位清除
	while(car_y>=car_row1)
	{
		//FillPhoto();                            //重新画车库
		DrawPhoto( pdc, 0, car_num);
		DrawPhoto( pdc, 1, car_num);
		ShowBmp(pdc, car_empty_path, car_x, car_y );  //清除车上次图片
		car_y=car_y-mv_len;
		ShowBmp(pdc, car_path, car_x, car_y);   //显示车新的位置图片
		Step_motor_forward();
		OSTimeDly(dly_time);
	}
	carStatArray[1][car_num]=1;              //标志位添加
	FillPhoto(pdc);
}

//车辆下移
int mvcardown(PDC pdc,int car_num)
{
	//int oldx,oldy;//保存原来坐标系位置
	int car_x=Start_posi_x-pic_weigh*car_num;
	int car_y=car_row1;
	
	carStatArray[1][car_num]=0;      //标志位清除
	while(car_y<=car_row2)
	{
		//FillPhoto();                            //重新画车库
		DrawPhoto( pdc, 0, car_num);
		DrawPhoto( pdc, 1, car_num);
		ShowBmp(pdc, car_empty_path, car_x, car_y );  //清除车上次图片
		car_y=car_y+mv_len;
		ShowBmp(pdc, car_path, car_x, car_y);   //显示车新的位置图片
		Step_motor_negative();
		OSTimeDly(dly_time);
	}
	carStatArray[0][car_num]=1;              //标志位添加
	FillPhoto(pdc);
}

U8 car_stat(U8 num)
{
   U8 car_num_sum;
   int i=num/5;
   int j=num%5;
   if((num>=1)&&(num<=9))
   	return (carStatArray[i][j]);    //0，1代表无车和有车
   else
    return 2;             //表示输入非法

}
/////////////////////////////////////////////////////
//                  Main function.                //
////////////////////////////////////////////////////
int main(void)
{

	ARMTargetInit();        // do target (uHAL based ARM system) initialisation //
	OSInit();               // needed by uC/OS-II //
	OSInitUart();
	initOSFile();
	
	/*******************/
	/* 移植时的初始化 */
	
	init_garage();
	init_MotorPort();
	init_ADdevice();
	/******************/
	
#if USE_MINIGUI==0
	initOSMessage();
	initOSList();
	initOSDC();
	initOSCtrl();
	LoadFont();
#endif

	loadsystemParam();
	
	// create the tasks in uC/OS and assign increasing //
	// priorities to them so that Task3 at the end of  //
	// the pipeline has the highest priority.          //
	LCD_printf("Create task on uCOS-II...\n");
	OSTaskCreate(Main_Task,  (void *)0,  (OS_STK *)&Main_Stack[STACKSIZE-1],  Main_Task_Prio);
//	OSTaskCreate(test_Task,  (void *)0,  (OS_STK *)&test_Stack[STACKSIZE-1],  test_Task_Prio);

	OSAddTask_Init(1);
  
	LCD_printf("Starting uCOS-II...\n");
	LCD_printf("Entering graph mode...\n");
	LCD_ChangeMode(DspGraMode);

	OSStart();              // start the OS //

	// never reached //
	return 0;
}//main

//////////////////////////////////////////////////////////////////////////
void input_passwd(POSMSG pMsg,int car_num)
{	
	int i=0;
//	U8 ch;
	 while(i<6)
	 {
	  //  pMsg=WaitMessage(0);
	    if(pMsg->Message==OSM_KEY)
	    {
del_car_pass1: DeleteMessage(pMsg);
	   	       pMsg=WaitMessage(0);
	   	     if(pMsg->Message==OSM_KEY)
	   	     {
	   	        if(pMsg->WParam==0x2e)
	   	        {
	   	        	if(i==0)
	   	        	{
	   	        		str_num[i]='\0';
	   	        		//str_num[i+1]='\0';
	   	        		i=0;
	   	        	}
	   	        	else
	   	        	{
	   	        		str_num[i-1]='\0';
	   	        		//carpasswd[car_num][i-1]=pMsg->WParam;
	   	        		i=i-1;
	   	        	}
	   	        }
	   	       else
	   	       {
	                carpasswd[car_num][i]=pMsg->WParam;
	                str_num[i]=0x2a;
	                str_num[i+1]='\0';
	                i=i+1;
	           }
	            DeleteMessage(pMsg);
	            CreateText2(str_num); /* 显示输入的密码 */ 
	           if(i<6)
	           {   
	            //DeleteMessage(pMsg);
	            pMsg=WaitMessage(0);
	           }
	            //pMsg=WaitMessage(0);
	            
	            printf("%c",carpasswd[car_num][i]);
	        }
	        /*
	        if(i=6)
	        {   
	            DeleteMessage(pMsg);
	            pMsg=WaitMessage(0);
	        }
	        */
	    }
	 }
	 CreateText(str2);  /*  请输入确定键 */
	// DeleteMessage(pMsg);
	 pMsg=WaitMessage(0);
	 DeleteMessage(pMsg);
	 pMsg=WaitMessage(0);
	// printf("1");
	 if(pMsg->Message==OSM_KEY)
	 {
	    if(pMsg->WParam==0x2e)
		{
			str_num[i-1]='\0';
	   	    i=i-1;
			CreateText2(str_num);
			DeleteMessage(pMsg);
			pMsg=WaitMessage(0);
			goto del_car_pass1;
	    }	    
	     //printf("2");
	 	while(pMsg->WParam!=13)
	 	  {
	 	   //  printf("3");
	 	    DeleteMessage(pMsg);
	 	    // printf("4");
	 	    pMsg=WaitMessage(0);
	 	   }
	 	   // printf("6");
	 }
	 CreateText2(str16);      //清除密码
	 DeleteMessage(pMsg);
	 
}
////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int check_passwd(POSMSG pMsg,int car_num)
{	
	 int i=0;
	 char carpasswdtmp[10][6];
	 CreateText(str3);
	
	while(i<6)
	 {
	    // pMsg=WaitMessage(0);
	    if(pMsg->Message==OSM_KEY)
	    {
del_car_pass2: DeleteMessage(pMsg);
               pMsg=WaitMessage(0);
	   	       if(pMsg->Message==OSM_KEY)
	   	       {
	   	         if(pMsg->WParam==0x2e)
	   	         {
	   	        	if(i==0)
	   	        	{
	   	        		str_num[i]='\0';
	   	        		//str_num[i+1]='\0';
	   	        		i=0;
	   	        	}
	   	        	else
	   	        	{
	   	        		str_num[i-1]='\0';
	   	        		//carpasswd[car_num][i-1]=pMsg->WParam;
	   	        		i=i-1;
	   	        	}
	   	        }
	   	       else
	   	       {
	            	carpasswdtmp[car_num][i]=pMsg->WParam;
	            	str_num[i]=0x2a;
	            	str_num[i+1]='\0';
	            	i=i+1;
	           }
	            DeleteMessage(pMsg);
	            CreateText2(str_num);  /* 输出输入的密码 */
	            printf("%c",carpasswd[car_num][i]);
	           if(i<6)
	           {   
	            //DeleteMessage(pMsg);
	            pMsg=WaitMessage(0);
	           }

	        }
	      /*
	        if(i<6)
	        {   
	            DeleteMessage(pMsg);
	            pMsg=WaitMessage(0);
	        }
	        */
	    }
	 }
	 CreateText(str2);      //确定
	// DeleteMessage(pMsg);
	 pMsg=WaitMessage(0);
	 DeleteMessage(pMsg);
	 pMsg=WaitMessage(0);
	 //printf("1");
	 if(pMsg->Message==OSM_KEY) //等待ENTER
	 {
        if(pMsg->WParam==0x2e)
		{
			str_num[i-1]='\0';
	   	    i=i-1;
			CreateText2(str_num);
			DeleteMessage(pMsg);
			pMsg=WaitMessage(0);
			goto del_car_pass2;
	    }	    
	   //  printf("2");
	 	while(pMsg->WParam!=13)
	 	  {
	 	 //    printf("3");
	 	    DeleteMessage(pMsg);
	 	    // printf("4");
	 	    pMsg=WaitMessage(0);
	 	    // printf("5");
	 	   }
	 	    //printf("6");
	 	    DeleteMessage(pMsg);
	 }
	CreateText2(str16);      //清除密码
	for(i=0;i<6;i++)
	{
		if(carpasswdtmp[car_num][i]!=carpasswd[car_num][i])
		{
			//printf("t%c\n",carpasswdtmp[car_num][i]);
			//printf("%c\n",carpasswd[car_num][i]);
			return (0);
		}
	}
	
	return 1;
}





////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Main_Task(void *Id)             //Main_Test_Task
{

   /*************************/
   /* 移植时定义的变量 */
	POSMSG pMsg=0;//创建消息结构
    unsigned int motor_delay_time;
    unsigned char car_num;
    float car_AD_result;
   /************************/
   
    /*************************/
    int oldx,oldy;//保存原来坐标系位置
	PDC pdc;//定义绘图设备上下文结构
	ClearScreen();//清屏
	pdc=CreateDC();//创建绘图设备上下文
	SetDrawOrg(pdc, 0,0, &oldx, & oldy); //设置绘图原点为屏幕中心
   /*************************************/
   
    OSTaskDel(9);    //touch screen
    OSTaskDel(60);    //led
    
    printf("ok");
    OSTimeDly(100);
    FillPhoto(pdc);
    ShowBmp(pdc, sys_name, pic_weigh*5, 0);//显示系统名字的图片
    //draw_car_road1(pdc);
    OSTimeDly(300);
    printf("please input commend\n");
    // CreateText3(str13);
	//消息循环
	for(;;)
	{
	    CreateText(str4);
	    DeleteMessage(pMsg);
		pMsg=WaitMessage(0); //等待消息
		DeleteMessage(pMsg);
		pMsg=WaitMessage(0); 
		if(pMsg->Message==OSM_KEY)
		  {
		     switch(pMsg->WParam)
		            {
		            	case '+':
		                     /*进行AD转换 判断*/
		            	     car_AD_result=car_AD();
		            	     printf("车重=%2.1f\n",car_AD_result);
		            	     if(car_AD_result>0.8)
		            	     {
		            	     	CreateText(str5); 
		            	     	//CreateText(str0); //创建文本框
		            	     	OSTimeDly(10000);
		            	     	break;
		            	     }
		            	     CreateText(str6);  /* 称重已通过 请输入存车车号 */
		        del_car_num1:CreateText(str12);
		            	     DeleteMessage(pMsg);
		            	     pMsg=WaitMessage(0);
		            	     DeleteMessage(pMsg);
		            	     pMsg=WaitMessage(0);
		            	     if(pMsg->Message==OSM_KEY)
		            	     {
		            	         str_num[0]=pMsg->WParam;
				           		 str_num[1]='\0';
				           		 car_num=pMsg->WParam-48;
				           		 CreateText2(str_num);  /* 显示输入的存车车号 */
				           		 CreateText(str2);     /* 请输入确定键 */
								 DeleteMessage(pMsg);
								 pMsg=WaitMessage(0);
								 DeleteMessage(pMsg);
								 pMsg=WaitMessage(0);
								 if(pMsg->Message==OSM_KEY)
								 {
								     if(pMsg->WParam==0x2e)
								     {
								     	str_num[0]=0x20;
								     	str_num[1]='\0';
								     	CreateText2(str_num);
								     	DeleteMessage(pMsg);
								     	goto del_car_num1;
								     }
									 while(pMsg->WParam!=13)
									 {
									    DeleteMessage(pMsg);
									 	pMsg=WaitMessage(0);
									 }
								 }
								 CreateText2(str16);
				           		 //DeleteMessage(pMsg);
		            	        // printf("num=%d\n",car_num);
		            	         switch(car_stat(car_num))
		            	         {
		            	           case 1:
		            	             	CreateText2(str7);
		            	             	break;
		            	           case 2:
		            	             	CreateText2(str8);
		            	             	break;
		            	           case 0:
		            	                printf("in savecar\n");
		            	                DeleteMessage(pMsg);
		            	                CreateText(str9);   /*输入密码*/
		            	                pMsg=WaitMessage(0);
		            	                if(pMsg->Message==OSM_KEY)
		            	                {
		            	                  input_passwd(pMsg,car_num);
		            	                }
		            	                OSTaskSuspend(58);
		            	                CreateText(str14);   /* 正在存车请稍后...... */   
		            	                save_car(pdc,car_num);
		            	                OSTaskResume(58);
		            	                CreateText(str1); //创建文本框
		            	                //printf("out savecar\n");
		            	             	break;
		            	           default:
					            		 break;
		            	             	}
		            	     		 DeleteMessage(pMsg);
					   	 		}
					   	 		break;
					     case '-':
	         del_car_num2: CreateText(str12);        /* 请输入车号 */
						   DeleteMessage(pMsg);
						   pMsg=WaitMessage(0);
						   DeleteMessage(pMsg);
						   pMsg=WaitMessage(0);
						   if(pMsg->Message==OSM_KEY)
						    {
						        //DeleteMessage(pMsg);
						        //pMsg=WaitMessage(0);
						        if(pMsg->Message==OSM_KEY)
						        str_num[0]=pMsg->WParam;
				           		str_num[1]='\0';
				           		CreateText2(str_num);    /* 输出输入的车号 */
								car_num=pMsg->WParam-48;
								CreateText(str2);        /* 请输入确定键 */
								DeleteMessage(pMsg);
								pMsg=WaitMessage(0);
								DeleteMessage(pMsg);
								pMsg=WaitMessage(0);
								if(pMsg->Message==OSM_KEY)
								{
								    if(pMsg->WParam==0x2e)
								    {
								     	str_num[0]=0x20;
								     	str_num[1]='\0';
								     	CreateText2(str_num);
								     	DeleteMessage(pMsg);
								     	goto del_car_num2;
								    }
									while(pMsg->WParam!=13)
									{
									   DeleteMessage(pMsg);
									   pMsg=WaitMessage(0);
									}
								}
								CreateText2(str16);
	            	            printf("num=%d\n",car_num);    	
	            	            switch(car_stat(car_num))
		            	         {
		            	           case 0:
		            	             	CreateText2(str17);
		            	             	break;
		            	           case 2:
		            	             	CreateText2(str8);
		            	             	break;
		            	           case 1:
		            	                DeleteMessage(pMsg);
		            	                CreateText(str9);   /*  请输入密码 */
		            	                pMsg=WaitMessage(0);
		            	                printf("in savecar\n");
		            	                if(!check_passwd(pMsg,car_num))
		            	                {
		            	                    printf("错误密码");
		            	                	CreateText2(str10);
		            	                	break;
		            	                }
		            	                printf("正确密码");
		            	                OSTaskSuspend(58);
		            	                CreateText(str15);   /* 正在取车请稍后...... */
		            	                take_car(pdc,car_num);
		            	                OSTaskResume(58);
		            	                printf("out savecar\n");
		            	                CreateText(str2); //创建文本框
		            	             	break;
		            	           default:
					            		 break;
		            	          }
								 DeleteMessage(pMsg);
							
						   	 }
						  break;
		 	              default:
		 	              	CreateText(str11);
					        break;
		               }	       
	
	     
	
		  DeleteMessage(pMsg);//删除消息,释放资源
       } /*if end*/
	
    }/*for循环 end*/
    
 }/*main_task end*/
