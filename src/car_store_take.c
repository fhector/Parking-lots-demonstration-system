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
    if(j<10)                                    //������ʾ�泵�ĳ���
    {  
        printf("�泵����Ϊ��%d\n",garage[j].garage_num);
        printf("�泵����ţ�%d\n",garage[j].garage_take_car_num);
    }
    else 
    {
        printf("garage is full\n");
    } 
     /* �����λΪ6-9���򷵻��²㳵��Ҫ�ƶ���λ�ø���*/    
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
    /*������ⲻΪ�գ���ʾȡ������Ϣ*/
    if((j<10)&&(j>0)&&(k==0)) 
    {
        
        printf("ȡ������Ϊ��%d\n",garage[j].garage_num);
        printf("ȡ������ţ�%d\n",garage[j].garage_take_car_num);
    }
    
    /*�����������Ϊ�գ���ʾ�������û�д˳�*/
    else if((j<10)&&(j>0)&&(k==1))
    {
    	return (3);
    }
    /*��ʾ������󣬳�����Χ*/
    else 
    {
    	return (0);
    }
    
    
    /*ȡ�ϲ㳵��ĳ�*/
    
    /* ������ⲻΪ�գ����Ϊ�գ������²㳵λ�ƶ�һ��λ�� */
    if((j>4)&&(j<10)&&(k==0))
    {
            garage[j].garage_null=1;
         	return (1);
    }
        
    /*�������Ϊ�գ����Ϊ�գ������²㳵λ����Ҫ�ƶ�*/
    else if((j>4)&&(j<10)&&(k==1))
    {
        	return (2);
    }   
    
    /*ȡ�²㳵*/
    /*�������Ϊ�գ���ʾ�������*/
    else if((j>0)&&(j<5)&&(k==1))
    {
       		return (3);
    }
       /*������ⲻΪ��,��ճ���*/
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
