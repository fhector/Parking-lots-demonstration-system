   #include "../inc/car_store_take.h" 
    #include <stdio.h>
   Garage garage[10];
    void init_garage(void)
    {
       	int i=0;
     	for(i=0;i<5;i++)
        {
        	garage[i].garage_num=i;
        	garage[i].garage_null=1;
        	garage[i].garage_take_car_num=i;
        	garage[i].car_passward=0;                 
        }
     
    	for(i=5;i<10;i++)
    	{
        	garage[i].garage_num=i;
        	garage[i].garage_null=1;
        	garage[i].garage_take_car_num=i-5;
        	garage[i].car_passward=0;              
     	}
	}  
int car_store(void)
{
    int j=0,k=0;
    for(j=1;j<10;j++)
    {
        if(garage[j].garage_null==1)
        {
           garage[j].garage_null=0;
           break;
        }                
    }
    if(j<10)                                    //用于显示存车的车号
    {  
        printf("存车车号为：%d\n",garage[j].garage_num);
        printf("存车车库号：%d\n",garage[j].garage_take_car_num);
    }
    else 
    {
        printf("garage is full\n");
    } 
     /* 如果车位为6-9，则返回下层车需要移动的位置个数*/    
   // if((j<10)&&(j>5)) 
    //{
        switch(j)
        {
            case 6:k=j-5;break;      
            case 7:k=j-5;break;   
            case 8:k=j-5;break;   
            case 9:k=j-5;break;
            default:k=0 ;break;                                   
        } 
      return (k);   
 
                  
}
  
int car_take(int st_car)
{
    int j=0,k=0;
    printf("take_car_num=%d\n",st_car);
    j=st_car;
    k=garage[j].garage_null;
    /*如果车库不为空，显示取车的信息*/
    if((j<10)&&(j>0)&&(k==0)) 
    {
        
        printf("取车车号为：%d\n",garage[j].garage_num);
        printf("取车车库号：%d\n",garage[j].garage_take_car_num);
    }
    
    /*否则，如果车库为空，显示输入错误，没有此车*/
    else if((j<10)&&(j>0)&&(k==1))
    {
    	return (3);
    }
    /*显示输入错误，超出范围*/
    else 
    {
    	return (0);
    }
    
    
    /*取上层车库的车*/
    
    /* 如果车库不为空，令车库为空，返回下层车位移动一个位置 */
    if((j>4)&&(j<10)&&(k==0))
    {
            garage[j].garage_null=1;
         	return (1);
    }
        
    /*如果车库为空，令车库为空，返回下层车位不需要移动*/
    else if((j>4)&&(j<10)&&(k==1))
    {
        	return (2);
    }   
    
    /*取下层车*/
    /*如果车库为空，显示输入错误*/
    else if((j>0)&&(j<5)&&(k==1))
    {
       		return (3);
    }
       /*如果车库不为空,清空车库*/
	else if((j>0)&&(j<5)&&(k==0))
    {
	        garage[j].garage_null=1;
		    return (4);
    }
    else 
    {
    		return (0);
    }  
	 
}  
