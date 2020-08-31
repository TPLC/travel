/**
  ******************************************************************************
  * @file    GM_code.c
  * @author  MRT.ZHONG
  * @version V1.0
  * @date    2015-5-12
  * @brief   光敏巡线函数整合   Main_switch-跳出方式整合
  ******************************************************************************
  * @attention
  *
  * 实验平台：c8051f340-IDE
  *
  * 地点：机器人实验室
  *
  ******************************************************************************
*/


#include"All_Include.h"

extern bit JUMP;                             //跳出标志位
extern int JUMPCHOOSE;                         //跳出选择变量
extern unsigned int t;
extern int m;
uint u=0;
extern unsigned int LLL;
extern int k;
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////************   GM巡线
//////////////////////////////////////////////////////////////////////////////////////////////////

void GM_forward_SE(int n,int JC)                     
{
  //uint u=0;
  t=0;
	FORWARD; //前进
	JUMPCHOOSE=JC;
 m=n;
 speedr=n; 
 speedl=m;
if(n<=200)
  {  
	while(1)
	 {  
///////////////////////////right/////////
 if((L1==0)&&(L2==1))	
	{
	 speedr=n+8;
	 speedl=m-8;
	}
	else if((L2==0)&&(L3==1))
	{
	 speedr=n+15;
	 speedl=m-15;
	}
	else if(L3==0)
	{
	 speedr=n+30;
	 speedl=m-30;
	}
    else if(L4==0)
	{
	 speedr=n+50;
	 speedl=n-50;
	}
/////////////////////////left///////////
	else if((R1==0)&&(R2==1))	
	{
	 speedr=n-8;
	 speedl=m+8;
	}
	else if((R2==0)&&(R3==1))
	{
	 speedr=n-15;
	 speedl=m+15;
	}
	else if(R3==0)
	{
	 speedr=n-30;
	 speedl=m+30;
	}
	else if(R4==0)
	{
	 speedr=n-50;
	 speedl=n+50;
	}
////////////////////////normal//////////
	else 
	{
	 speedr=n;
	 speedl=m;			    
	} 
  Main_switch();
  if(JUMP){JUMP=0;break;}
 }
}
}


void GM_forward(int n,int JC)                     
{
  //uint u=0;
  t=0;
	FORWARD; //前进
	JUMPCHOOSE=JC;
 m=n;
 speedr=n; 
 speedl=m;
if(n<=200)
  {  
	while(1)
	 {  
///////////////////////////right/////////
  //////////////////////////////////////////////////
		   if((L1==1)&&(L2==0))	//右偏微调	
				{
				  speedr=n-10;
			      speedl=m+10;
				  }
			else if((L2==1)&&(L3==0))//右偏粗调
				{
				speedr=n-20;
			    speedl=m+20;
				}
			else if(L3==1)
				{
				speedr=n-40;
			    speedl=m+40;
			    }
			else if((R4==1)&&(R3==0))//左偏微调		
				{
				  speedr=n+10;
			      speedl=m-10;
				  }
			else if((R3==1)&&(R2==0))
				{
				speedr=n+20;
			    speedl=m-20;
				}
			else if(R2==1)
				{
				speedr=n+40;
			    speedl=m-40;
			    }
			else 
				{
			    speedr=n;
			    speedl=m;			    
	            } 
				//////////////////////////////////////////////
	t=t+1;
  Main_switch();

if(JUMP){JUMP=0;break;}
}
}
else
  {
	while(1)
	    {
             //////////////////////////////////////////////////
		   if((L1==1)&&(L2==0))	//右偏微调	
				{
				  speedr=n-10;
			      speedl=m+10;
				  }
			else if((L2==1)&&(L3==0))//右偏粗调
				{
				speedr=n-20;
			    speedl=m+20;
				}
			else if(L3==1)
				{
				speedr=n-40;
			    speedl=m+40;
			    }
			else if((R4==1)&&(R3==0))//左偏微调		
				{
				  speedr=n+10;
			      speedl=m-10;
				  }
			else if((R3==1)&&(R2==0))
				{
				speedr=n+20;
			    speedl=m-20;
				}
			else if(R2==1)
				{
				speedr=n+40;
			    speedl=m-40;
			    }
			else 
				{
			    speedr=n;
			    speedl=m;			    
	            } 
				//////////////////////////////////////////////
				t=t+1;
   Main_switch();
   

		if(JUMP){JUMP=0;break;}
		}
	  }
}


void GM_backward(int n,int JC)                      //后巡线，节点跳出，慢速
{
 //uint u;
 t=0;
BACKWARD; 
delay(3);
JUMPCHOOSE=JC;
 speedr=n;
  m=n+10;
  speedl=m;

if(n>=50)
   {
    while(1)
       { 
///////////////////////////right/////////
     if((L1==1)&&(L2==0))	
	{
	 speedr=n-10;
	 speedl=m+10;
	}
	else if((L2==1)&&(L3==0))
	{
	 speedr=n-20;
	 speedl=m+20;
	}
	else if(L3==1)
	{
	 speedr=n-30;
	 speedl=m+30;
	}
	else if((R1==1)&&(R2==0))	
	{
	 speedr=n+10;
	 speedl=m-10;
	}
	else if((R2==1)&&(R3==0))
	{
	 speedr=n+20;
	 speedl=m-20;
	}
	else if(R3==1)
	{
	 speedr=n+30;
	 speedl=m-30;
	}
	else 
	{
	 speedr=n;
	 speedl=m;			    
	} 
	t=t+1;
  Main_switch();
  if(JUMP){JUMP=0;break;}	
  }
}
else
  {
   while(1)
        {
            if((L1==1)&&(L2==0))	//右偏微调	
				{
				  speedr=n;
			      speedl=m+8;
				  }
			else if((L2==1)&&(L3==0))//右偏粗调
				{
				speedr=n;
			    speedl=m+16;
				}
			else if(L3==1)
				{
				speedr=n;
			    speedl=m+25;
			    }
		    else if((L4==1)&&(JUMPCHOOSE>2))
				{
				speedr=n;
			    speedl=m+30;
			    }

			else if((R1==1)&&(R2==0))//左偏微调		
				{
				  speedr=n+8;
			      speedl=m;
				  }
			else if((R2==1)&&(R3==0))
				{
				speedr=n+16;
			    speedl=m;
				}
			else if(R3==1)
				{
				speedr=n+25;
			    speedl=m;
			    }
			else if((R4==1)&&(JUMPCHOOSE>2))
				{
				speedr=n+30;
			    speedl=m;
			    }
			else 
				{
			    speedr=n;
			    speedl=m;
			    }
				t=t+1;
   Main_switch();
   
	if(JUMP){JUMP=0;break;}
	}
  }
}

void GM_forward_3D(int n,int JC)                       //******************************************三灯前巡线
{
FORWARD; //前进
JUMPCHOOSE=JC;
speedr=n;
speedl=n;
t=0;
	while(1)
	 {  //////////////////////////////////////////////////
		   if((L1==1)&&(L2==0))	//右偏微调	
				{
				  speedr=n-10;
			      speedl=n+10;
				  }
			else if((L2==1)&&(L3==0))//右偏粗调
				{
				speedr=n-20;
			    speedl=n+20;
				}
			else if(L3==1)
				{
				speedr=n-40;
			    speedl=n+40;
			    }
			else if((R4==1)&&(R3==0))//左偏微调		
				{
				  speedr=n+10;
			      speedl=n-10;
				  }
			else if((R3==1)&&(R2==0))
				{
				speedr=n+20;
			    speedl=n-20;
				}
			else if(R2==1)
				{
				speedr=n+40;
			    speedl=n-40;
			    }
			else 
				{
			    speedr=n;
			    speedl=n;			    
	            } 
				//////////////////////////////////////////////
				t++;
			Main_switch(); 
			if(JUMP){JUMP=0;break;}
		}

}



void GM_backward_3D(int n,int JC)                       //******************************************三灯后巡线
{
t=0;
BACKWARD; 
JUMPCHOOSE=JC;
speedr=n;
speedl=n;



    while(1)
       { 
            if((L1==1)&&(L2==0))	//右偏微调	
				{
				  speedr=n+8;
			      speedl=n-8;
				  }
			else if((L2==1)&&(L3==0))//右偏粗调
				{
				speedr=n+23;
			    speedl=n-23;
				}
			else if(L3==1)
				{
				speedr=n+43;
			    speedl=n-43;
			    }
			else if((R4==1)&&(R3==0))//左偏微调		
				{
				  speedr=n-13;
			      speedl=n+13;
				  }
			else if((R3==1)&&(R2==0))
				{
				speedr=n-27;
			    speedl=n+27;
				}
			else if(R2==1)
				{
				speedr=n-43;
			    speedl=n+43;
			    }
			else 
				{
			    speedr=n;
			    speedl=n;
			    }
				
			Main_switch(); 
			if(JUMP){JUMP=0;break;}	
			t=t+1;
		}
		
}




void Main_switch(void)     //x为最后调出方式的配置控制位 
{
  switch(JUMPCHOOSE)
  {
    case 0:
	if(L1==1)
	{
	  delay(5);
	  if(L1==1)
	    JUMP=1;
	}
	break;
	case 1:
	if(L2==1)
	{
	  delay(5);
	  if(L2==1)
	    JUMP=1;
	}
	break;
	case 2:
	if(L3==1)
	{
	  delay(5);
	  if(L3==1)
	    JUMP=1;
	}
	break;
	case 3:
	if(L4==1)
	{
	  delay(5);
	  if(L4==1)
	    JUMP=1;
	}
	break;
	case 4:
	if(R1==1)
	{
	  delay(5);
	  if(R1==1)
	    JUMP=1;
	}
	break;
	case 5:
	if(R2==1)
	{
	  delay(5);
	  if(R2==1)
	    JUMP=1;
	}
	break;
	case 6:
	if(R3==1)
	{
	  delay(5);
	  if(R3==1)
	    JUMP=1;
	}
	break;
	case 7:
	if(R4==1)
	{
	  delay(5);
	  if(R4==1)
	    JUMP=1;
	}
	break;
	case 8:
    if(JJ1==0)
	{
	  delay(5);
	  if(JJ1==0)
	    JUMP=1;
	}  
	break;
	case 9:
	if(JJ2==0)
	{
	  delay(5);
	  if(JJ2==0)
	    JUMP=1;
	}
	break;
	case 10:
	if(JJ3==0)
	{
	  delay(5);
	  if(JJ3==0)
	    JUMP=1;
	}
	break;
	case 11:
	if(JJ4==0)
	{
	  delay(5);
	  if(JJ4==0)
	    JUMP=1;
	}
	break;
	case 12:
	if(LL==0)
	{
	  delay(5);
	  if(LL==0)
	    JUMP=1;
	}
	break;
	case 13:
	if(RR==0)
	{
	  delay(5);
	  if(RR==0)
	    JUMP=1;
	}
	break;
	case 14:
	if(L1==0)
	{
	  delay(5);
	  if(L1==0)
	    JUMP=1;
	}
	break;
	case 15:
	if(L2==0)
	{
	  delay(5);
	  if(L2==0)
	    JUMP=1;
	}
	break;
	case 16:
	if(L3==0)
	{
	  delay(5);
	  if(L3==0)
	    JUMP=1;
	}
	break;
	case 17:
	if(L4==0)
	{
	  delay(5);
	  if(L4==0)
	    JUMP=1;
	}
	break;
	case 18:
	if(R1==0)
	{
	  delay(5);
	  if(R1==0)
	    JUMP=1;
	}
	break;
	case 19:
	if(R2==0)
	{
	  delay(5);
	  if(R2==0)
	    JUMP=1;
	}
	break;
	case 20:
	if(R3==0)
	{
	  delay(5);
	  if(R3==0)
	    JUMP=1;
	}
	break;
	case 21:
	if(R4==0)
	{
	  delay(5);
	  if(R4==0)
	    JUMP=1;
	}
	break;
	case 22:
    if(JJ1==1)
	{
	  delay(5);
	  if(JJ1==1)
	    JUMP=1;
	}  
	break;
	case 23:
	if(JJ2==1)
	{
	  delay(5);
	  if(JJ2==1)
	    JUMP=1;
	}
	break;
	case 24:
	if(JJ3==1)
	{
	  delay(5);
	  if(JJ3==1)
	    JUMP=1;
	}
	break;
	case 25:
	if(JJ4==1)
	{
	  delay(5);
	  if(JJ4==1)
	    JUMP=1;
	}
	break;
	case 26:
	if(LL==1)
	{
	  delay(5);
	  if(LL==1)
	    JUMP=1;
	}
	break;
	case 27:
	if(RR==1)
	{
	  delay(5);
	  if(RR==1)
	    JUMP=1;
	}
	break;
	case 28:
	if(abs(speedr-speedl)<=2)
	  JUMP=1;
    break;
	case 29:
	if(JJ5==0)
	{
	  delay(5);
	  if(JJ5==0)
	    JUMP=1;
	}
	break;
	case 30:
	if(JJ5==1)
	{
	  delay(5);
	  if(JJ5==1)
	    JUMP=1;
	}
	break;
	case 31:
	if(t>35)
	{
	  JUMP=1;
	}
	break;
	case 32:
	if(t>180)
	{
	  JUMP=1;
	}
	break;
	case 33:
	if((L4==1)&&(L3==1)&&(L2==1))
	{
	  delay(3);
	  if((L4==1)&&(L3==1)&&(L2==1))
	  {
	    JUMP=1;
	  }
	}
	break;
	case 34:
	if((R4==1)&&(R2==1))
	{
	  delay(3);
	  if((R4==1)&&(R3==1)&&(R2==1))
	  {
	    JUMP=1;
	  }
	}
	break;
	case 35:
	if(t>110)
	{
	  JUMP=1;
	}
	break;
    case 36:
    if(t>50000)
	{
	  JUMP=1;
	}
	break;
	case 37:
	if((JJ2==0)&&(JJ4==0))
	{
	  delay(5);
	  if((JJ2==0)&&(JJ4==0))
	  {
	    JUMP=1;
	  }
	}
	break;
	case 38:
	if((JJ2==1)&&(JJ4==1))
	{
	  delay(5);
	  if((JJ2==1)&&(JJ4==1))
	  {
	    JUMP=1;
	  }
	}
	break;
	case 39:
	if((LL==0)&&(RR==0))
	{
	  delay(5);
	  if((LL==0)&&(RR==0))
	  {
	    JUMP=1;
	  }
	}
	break;
	case 40:
	if((LL==1)&&(RR==1))
	{
	  delay(5);
	  if((LL==1)&&(RR==1))
	  {
	    JUMP=1;
	  }
	}
	break;
	case 41:
	if(LLL>=15)
	{
	  JUMP=1;
	}
	break;
    case 42:
	if(abs(k-61)<=5)
	{
	  JUMP=1;
	}
	break;
	case 43:
	if(t>=10000)
	{
	  JUMP=1;
	}
	break;
	case 44:
if(t>=16)
	{
	  JUMP=1;
	}
	break;
	
	default:break; 
  }

}