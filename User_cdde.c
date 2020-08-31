 /**
  ******************************************************************************
  * @file    User_code.c
  * @author  MRT.ZHONG
  * @version V1.0
  * @date    2015-5-12
  * @brief   整合程序-最终修改版
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



extern bit CCDDIR;                             //CCD 方向 1为前
extern bit SIFLAG;                           //非第一次数据标志
extern bit aftercj;                          //采集完标志
extern bit cjflag;                           //

extern unsigned char Integrationtime;       //积分时间,单位毫秒

extern unsigned int CLKFLAG;                 //像素记数
extern xdata unsigned char Image_Data[129];    //图像数组，最后一个数据舍弃
extern unsigned char flag2;

unsigned char flag11,flag22,flag33;

unsigned char BUF[8];
unsigned char cnt;
unsigned int Average1,Average2,NNN,LLL;
unsigned char flag_sp=0;/////////珠峰
unsigned char fast_slow=0;
unsigned char sec_chance=1;
unsigned char isr_choose=0;




////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////************  测试程序
///////////////////////////////////////////////////////////////

void test1()////////////////////////////调整平台
{
  	NNN=0;
	
	do
   {
		cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	  
	//}
	 
	//delay(10);
	 if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	 { 
	NNN=(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
	}

	if(abs(NNN-Average1)<360-abs(NNN-Average1))
	{ 
	   if(Average1<NNN)
	   {
	   speedr=127-40;
       speedl=127+40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
        }
		else
		{
		  speedr=127+40;
       speedl=127-40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
		}
	  
	
	}
	else
	{

	
	   
	   if(Average1<NNN)
	   {
	   speedr=127+40;
       speedl=127-40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
        }
		else
		{
		  speedr=127-40;
       speedl=127+40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
		}
	  }
	}
	while(abs(abs(Average1-NNN)-180)>=5); 
}


void test2()///////////////2pintai
{
  CCD_forward(191,11);
	
	 speedr=187;
	speedl=190;
	while(1)
	{
	  if(JJ2==0)
	  {
	    delay(5);
	    if(JJ2==0)
		{
		   break;
		}
	  }
	}
    speedr=187;
	speedl=190;
	while(1)
	{
	  if(JJ2==1)
	  {
	    delay(5);
		if(JJ2==1)
		{
		  break;
		}
	  }
	}
	speedr=187;
	speedl=190;
	while(1)
	{
	  if(JJ2==0)
	  {
	    delay(5);
		if(JJ2==0)
		{
		  break;
		}
	  }
	}
	speedr=187;
	speedl=190;
	while(1)
    {
	  if(JJ2==1)
	  {
	    delay(5);
		if(JJ2==1)
		{
		  break;
		}
	  }
	}
	speedr=185;
	speedl=185;
	while(1)
	{
	  if(JJ5==0)
	  {
	    delay(5);
		if(JJ5==0)
		{
		  break;
		}
	  }
	}
	DENG1=1;
    speedr=127;
	speedl=127;
	delay(200);
    
	 
	 speedr=127;
	 speedl=127;
	 delay(200);
	if(sec_chance==1)
	{
	flag11=numberAB();
	}
else
{
  speedr=127;
  speedl=127;
  delay(1000);
}
  /* D2=220;
   delay(300);
   D2=100;
   delay(300);
   D2=220;
   delay(300);
   D2=100;
   delay(300);
   D1=221;
   delay(300);
   speedr=170;
   speedl=180; 
   delay(260);
   speedr=127;
   speedl=127;
   delay(200);
   speedr=80;
   speedl=80;
   delay(210);
   D1=210;*/
   
    
  speedr=127-127;
speedl=127+100;
delay(440);///////////////////////////////580
speedr=127-110;
speedl=127+110;
delay(0);
speedr=127-80;
speedl=127+100;
delay(100);////////////////////////////50

speedr=127;
speedl=127;
delay(300);

//test1();
//Average1=0;Average2=0;NNN=0;LLL=0;

}

void test3()/////////////3pintai
{
    CCD_forward(191,11);
	DENG0=0;
	F_up_stage();
	if((sec_chance==1)&&(flag11=='A'))
	{
	flag22=numberCD();
	}
	else
	{
	speedr=127;
	speedl=127;
	delay(1000);
	}

	F_cycle(310,130,80);
	speedl=127;
	speedr=127;
	delay(300);
	//test1();
    //Average1=0;Average2=0;NNN=0;LLL=0;

}

void test4()/////////////////////4pintai
{
    CCD_forward(191,11);
	DENG0=0;
	F_up_stage();
	if((sec_chance==1)&&(flag11=='B'))
	{
	flag22=numberCD();
	}
	else
	{
	speedr=127;
	speedl=127;
	delay(1000);
	}
	/////////////////////////////////////////////////F_cycle(460,0,0);
     speedr=127+120;
	speedl=127-100;
	delay(460);
	speedr=127+60;
	speedl=127-110;
	delay(75);
DENG1=1;
	speedr=127;
	speedl=127;
	delay(300);
//	DENG1=1;
	//test1();
    //Average1=0;Average2=0;NNN=0;LLL=0;
}

void test5()///////////////////5pintai
{
  CCD_forward(191,11);
  
 F_up_stage();
    
 DENG0=0;
 if((sec_chance==1)&&(flag22=='C'))
 {
  flag33=numberEF();
  }
  else
	{
	speedr=127;
	speedl=127;
	delay(1000);
	}
speedr=127+127;
	speedl=127-95;
	delay(435);
	speedr=127+60;
	speedl=127-110;
	delay(80);

	speedr=127;
	speedl=127;
	delay(100);

   speedr=127;
   speedl=127;
   delay(300);
   DENG1=1;
   //test1();
   //Average1=0;Average2=0;NNN=0;LLL=0;
}

void test6()//////////////////////6pintai
{
  CCD_forward(191,11);
DENG0=0;
DENG1=1;
  speedr=185;
	speedl=190;
	while(1)
	{
	  if(JJ2==0)
	  {
	    delay(5);
	    if(JJ2==0)
		{
		   break;
		}
	  }
	}
    speedr=185;
	speedl=190;
	while(1)
	{
	  if(JJ2==1)
	  {
	    delay(5);
		if(JJ2==1)
		{
		  break;
		}
	  }
	}
	speedr=185;
	speedl=190;
	while(1)
	{
	  if(JJ2==0)
	  {
	    delay(5);
		if(JJ2==0)
		{
		  break;
		}
	  }
	}
	speedr=185;
	speedl=190;
	while(1)
    {
	  if(JJ2==1)
	  {
	    delay(5);
		if(JJ2==1)
		{
		  break;
		}
	  }
	}
	speedr=185;
	speedl=185;
	while(1)
	{
	  if(JJ5==0)
	  {
	    delay(5);
		if(JJ5==0)
		{
		  break;
		}
	  }
	}
	DENG1=1;
    speedr=127;
	speedl=127;
	delay(200);
   if((sec_chance==1)&&(flag22=='D'))
   {
   flag33=numberEF();
   }
   else
	{
	speedr=127;
	speedl=127;
	delay(1000);
	}
  
    speedr=127+127;
	speedl=127-95;
	delay(490);
	speedr=127+60;
	speedl=127-110;
	delay(80);

	
  speedr=127;
  speedl=127;
  delay(300);
//test1();
//Average1=0;Average2=0;NNN=0;LLL=0;
 

}


void test10()
{
  CCD_forward(170,29);
	CCD_forward_SP(170,41);
	Average1=NNN/LLL;
	speedr=127;
	speedl=127;
	while(JJ5==1);
    

	//LLL=0;
	NNN=0;
	
	while(1)
   {
     speedr=160;
	 speedl=160;

	   cnt=0;                                                    
	   //SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	  
	//}
	 
	//delay(10);
	 if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	 { 
	NNN=(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
	}
	if(abs(NNN-Average1)>180)
	{
	
	  if(NNN>Average1)
	  {
	   speedr=127-20;
    speedl=127+20;
	delay(50);
	

	  }
	  else
	  {
	   speedr=127+20;
    speedl=127-20;
	delay(50);

	  }
	
	}
	else
	{

	  if(NNN>Average1)///////youpian
	  {
	   
	speedr=127+20;
    speedl=127-20;
	delay(50);
	
	
	  }
	  else//////////zuopian
	  {
	  speedr=127-20;
    speedl=127+20;
	delay(50);	   
	  }
	}
	}
}

void test11()/////////////////////////////////////////////////中平台转正
{
  CCD_forward(170,29);
	CCD_forward_SP(170,41);
	Average1=NNN/LLL;
	speedr=127;
	speedl=127;
	while(JJ5==1);
     CCD_forward(195,11);
  BELLON;

  GM_forward_3D(205,25);
  GM_forward_3D(205,39);

  GM_forward_3D(205,9);
  GM_forward_3D(205,23);
  GM_forward_3D(205,38);
  GM_forward_3D(210,9);
  GM_forward_3D(205,23);
  BELLOFF;
  F_cycle_sp(420,100,50);
	//LLL=0;
	NNN=0;
	
	do
   {
		cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	  
	//}
	 
	//delay(10);
	 if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	 { 
	NNN=(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
	}
	if(abs(NNN-Average1)>180)
	{
	
	  if(NNN>Average1)
	  {
	   speedr=127-40;
    speedl=127+40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);

	  }
	  else
	  {
	   speedr=127+40;
    speedl=127-40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	  }
	
	}
	else
	{

	  if(NNN>Average1)///////youpian
	  {
	   
	speedr=127+40;
    speedl=127-40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	
	  }
	  else//////////zuopian
	  {
	  speedr=127-40;
    speedl=127+40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	   
	  }
	}
	}
	while(abs(Average1-NNN)>=5);
}

void test12()/////////////////////////////测试中平台是否转歪
{
  CCD_forward(170,29);
	CCD_forward_SP(170,41);
	Average1=NNN/LLL;
	speedr=127;
	speedl=127;
	while(JJ5==1);
CCD_forward(195,11);
BELLON;
  GM_forward_3D(210,25);
  GM_forward_3D(210,9);
  GM_forward_3D(210,23);
  GM_forward_3D(210,9);
  GM_forward_3D(205,23);
  BELLOFF;
  F_cycle_sp(335,100,70);

	LLL=0;
	NNN=0;
	while(1)
	{

		cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	  
	//}
	 
	//delay(10);
	 if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	 { 
	NNN=NNN+(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
	LLL++;
	}
	if(LLL>=40)
	{
	  break;
	}
	}
	Average2=NNN/40;
	


	 if(Average2>Average1)//////////////////////////////////////转太少   右卡
	   {
	     BELLON;
		 delay(200);
		 BELLOFF;
		 delay(200);
		 BELLON;
		 delay(200);
		 BELLOFF;
		 /*if(Average2-Average1<=10)
		 {
		   speedl=127;
		   speedr=127;
		   delay(200);
		 }
		 else if(Average2-Average1<=20)
		 {
          speedr=127+60;
		 speedl=127-60;
		 delay(150);
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
		 else
		 {
		 speedr=127+60;
		 speedl=127-60;
		 delay(350);
		 speedr=127;
		 speedl=127;
		 delay(100);

		 }*/

	   }
	   else///////////////////////转过头  左卡
	   {
	     BELLON;
		 delay(200);
		 BELLOFF;
		 /*if(Average1-Average2<=10)
		 {
		   speedr=127;
           speedl=127;
		   delay(200);
		 }
		 if(Average1-Average2<=20)
		 {
		   speedr=127-60;
		 speedl=127+60;
		 delay(150);
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
		 else
		 {
		 speedr=127-60;
		 speedl=127+60;
		 delay(350); 
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }*/
	   }
}

void test13()///////////////////////////////////珠峰
{
    F_bridge();
speedr=127;
speedl=127;
delay(200);
	CCD_forward(190,11);
	GM_forward_3D(205,25);
	GM_forward_3D(205,31);
	
    GM_forward_3D(205,10);
	GM_forward_3D(205,11);
	GM_forward_3D(205,25);
	
    GM_forward(205,43);
	GM_forward_3D(205,11);
	GM_forward_3D(205,25);
	GM_forward_3D(205,31);
	GM_forward_3D(205,10);
	GM_forward(205,43);

	GM_forward_3D(205,11);
	speedr=200;
	speedl=200;
	while(1)
	{
	  if(JJ2==0)
	  {
	    delay(5);
	    if(JJ2==0)
		  break;
	  }
	}
	speedr=200;
	speedl=200;
	while(1)
	{
	  if(JJ2==1)
	  {
	    delay(5);
	    if(JJ2==1)
		  break;
	  }
	}
	
  speedr=127;
  speedl=127;
  delay(1000);
  

speedr=127-110;
speedl=127+70;
delay(530);///////////////////////////////580
speedr=127-110;
speedl=127+110;
delay(0);
speedr=127-80;
speedl=127+100;
delay(100);////////////////////////////50

speedr=127;
speedl=127;
delay(300);
	
 if(flag33=='F')
  {
  	D1=232;
	delay(300);
	D1=210;
	D3=225;
	delay(300);
	D3=200;
	delay(300);
}
   /////////////////////////////////////////


/////////////////////////////////////////////////////////////
   	/////////////////////////////////////////
	/*NNN=0;
	
	do
   {
		cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	  
	//}
	 
	//delay(10);
	 if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	 { 
	NNN=(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
	}
	if(abs(NNN-Average1)>180)
	{
	
	  if(NNN>Average1)
	  {
	   speedr=127-40;
    speedl=127+40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);

	  }
	  else
	  {
	   speedr=127+40;
    speedl=127-40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	  }
	
	}
	else
	{

	  if(NNN>Average1)///////youpian
	  {
	   
	speedr=127+40;
    speedl=127-40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	
	  }
	  else//////////zuopian
	  {
	  speedr=127-40;
    speedl=127+40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	   
	  }
	}
	}
	while(abs(Average1-NNN)>=5);*/
	 
////////////////////////////////////////////////////////////


	NNN=0;LLL=0;Average1=0;Average2=0;
	//isr_choose=3;
    //TR0=1;
	//CCD_forward_ss();
    CCD_forward(150,11);
	GM_forward_3D(150,25);
    GM_forward_3D(150,9);
    GM_forward_3D(150,23);
	GM_forward(150,43);
    GM_forward(150,43);
	GM_forward(150,43);
    GM_forward(150,43);
	flag_sp=1;
	CCD_forward(150,11);
	GM_forward_3D(150,25);
	GM_forward_3D(150,9);
	GM_forward_3D(150,23);
	
    GM_forward(150,43);
    GM_forward(150,43);
	GM_forward(150,43);
    GM_forward(150,43);
	GM_forward_3D(155,11);
	GM_forward_3D(155,25);
	GM_forward_3D(155,40);
	GM_forward_3D(155,9);	
	GM_forward_3D(190,23);
	
	flag_sp=2;
}



void test16()/////////////////////////////////////出门
{
  F_down();
  DENG1=1;
   
	CCD_forward(220,4);
	CCD_forward(220,18);

    CCD_forward(180,11);
	CCD_forward(180,25);
    speedr=180;
	speedl=180;
	while(1)
	{
	  if(JJ2==0)
	  {
	    delay(10);
		if(JJ2==0)
		{
		  break;
		}
	  }
	}
	speedr=180;
	speedl=180;
	while(1)
	{
	  if(JJ2==1)
	  {
	    delay(10);
		if(JJ2==1)
		{
		  break;
		}
	  }
	}
    changqiao(180,0);
	
	changqiao(180,1);
		changqiao_sp(180,0);
	changqiao_sp(180,1);
	changqiao(180,0);
	BELLON;
    
	
	
   CCD_forward(145,25);
	 CCD_forward(150,11);
	 CCD_forward(150,25);
	 
	 CCD_forward(150,9);
	 CCD_forward(150,23);
	 CCD_forward(150,38);
	 BELLOFF;
	 
	 test2();/////////////////pintai
  
	 F_down();
	 speedr=127;
	 speedl=127;
	 delay(100);
	  CCD_forward(185,11);
	  
	CCD_forward(185,25);
	BELLON;
	speedr=185;
	speedl=185;
	while(1)
	{
	  if(JJ2==0)
	  {
	    delay(12);
		if(JJ2==0)
		{
		  break;
		}
	  }
	}
	speedr=185;
	speedl=185;
	while(1)
	{
	  if(JJ2==1)
	  {
	    delay(12);
		if(JJ2==1)
		{
		  break;
		}
	  }
	}
	changqiao(185,0);
	changqiao(185,1);
	changqiao_sp(180,0);
	changqiao_sp(180,1);
  
	changqiao(180,0);
	BELLOFF;
	DENG1=1;
	
     CCD_forward(145,25);
	 CCD_forward(150,11);
	 CCD_forward(150,25);
	 CCD_forward(150,9);
	 CCD_forward(150,23);
	 if(fast_slow==1)
	 {
	 CCD_forward(195,3);
	 DENG1=0;
/////////////////////////////////////////////////F_turn_B_R();SPECIAL
	 BACKWARD;
    delay(5);
  speedl=127-60;
  speedr=127+70;////43
  while(R1==0);
  speedl=127-90;
  speedr=127+85;////100
  while(L4==0);
  speedl=127-30;
  speedl=127+40;
  while(L1==0);
  speedr=127;
  speedl=127;
  delay(100);
   }
  else
   {
  	 CCD_forward(195,3);
	 F_turn_B_R_SLOW();
}
 
}

void test17()//////////////////////////////////////3平台
{
DENG0=1;
CCD_backward(65,31);
if(fast_slow==1)
{
  CCD_backward(55,4);
	//////////////////////////////////////////////B_turn_F_R();有钉子
	  FORWARD;
  delay(5);
  speedr=127+128;
  speedl=127-25;
  while(L4==0);
  speedr=127+128;
  speedl=127-95;
  while(R1==0);//前巡线板右边的灯也反了
  speedr=127+40;
  speedl=127-10;
  while(R4==0);
  speedl=127;
  speedr=127;
  delay(80); 
}
else
{
  CCD_backward(65,4);
 B_turn_F_R_SLOW();
}
	DENG0=0;
	DENG1=1;
	CCD_forward(205,31);
   CCD_forward(210,4);
	CCD_forward(210,3);
	CCD_forward(210,17);
	
	test3();/////////////////////////pintai
		  if(flag11=='A')
  {
   	D1=232;
	delay(300);
	D1=210;
	D3=225;
	delay(300);
	D3=200;
	delay(300);
 }
	DENG1=1;
	F_down();
	CCD_forward_R(220,4);
	if(fast_slow==1)
	{
	CCD_forward(205,3);
	DENG1=0;
	F_turn_B_R();
	}
	else
	{  
	  CCD_forward(195,3);
	DENG1=0;
	F_turn_B_R_SLOW();
	}
   speedr=127;
	speedl=127;
	delay(100);
   DENG0=1;
	CCD_backward(65,3);
	CCD_backward(75,9);
    CCD_backward(75,23);
	CCD_backward(85,12);
	CCD_backward(85,13);
	CCD_backward(85,27);
	CCD_backward(85,40);
	CCD_backward(75,23);

	
	CCD_backward(65,3);
	///////////////////////////////////////////////B_turn_F_L();SPECIAL
    FORWARD;
  delay(5);
  speedr=127-80;//20
  speedl=127+40;
  while(R1==0);
  speedr=127-100;//90
  speedl=127+70;//128
  while(L4==0);
  speedr=127-40;//10
  speedl=127+30;//25
  while(L1==0);
  speedr=127;
  speedl=127;
  delay(100);
}

void test18()/////////////////////////////////////4平台
{
    DENG0=1;
	CCD_backward(55,31);
	if(fast_slow==1)
	{
	CCD_backward(55,3);
	////////////////////////////////////////////////////B_turn_F_L();有钉子
	FORWARD;
  delay(5);
  speedr=127-35;//20
  speedl=127+100;
  while(R1==0);
  speedr=127-80;//90
  speedl=127+100;//128
  while(L4==0);
  speedr=127-20;//10
  speedl=127+40;//25
  while(L1==0);
	DENG0=0;
	speedr=127;
	speedl=127;
	delay(100);
   }
   else
   {
     CCD_backward(65,3);
     B_turn_F_L_SLOW();
   }
	DENG1=1;
	CCD_forward(200,31);
	CCD_forward(210,3);
	CCD_forward(210,17);
	CCD_forward(200,31);
 test4();/////////////////////pintai
		  if(flag11=='B')
  {
  	D1=232;
	delay(300);
	D1=210;
	D3=225;
	delay(300);
	D3=200;
	delay(300);
}
	DENG1=1;
	F_down();
	
	CCD_forward(205,31);
	  CCD_forward(195,4);
	  F_turn_B_L_SLOW();

	
	DENG0=1;
	CCD_backward_L(60,9);

    CCD_backward(75,23);
	CCD_backward(85,12);
	CCD_backward(85,13);
	CCD_backward(85,27);
	CCD_backward(85,40);
	CCD_backward(75,23);

if(fast_slow==1)
	{
	CCD_backward(60,3);
	DENG0=0;
	
	/////////////////////////////////////////////////B_turn_F_L();SPECIAL
	FORWARD;
  delay(5);
  speedr=127-50;//20
  speedl=127+90;
  while(R1==0);
  speedr=127-80;//90
  speedl=127+90;//128
  while(L4==0);
  speedr=127-20;//10
  speedl=127+30;//25
  while(L1==0);
	speedr=127;
	speedl=127;
	delay(100);
	}
	else
	{
	 CCD_backward(62,3);
	  B_turn_F_L_SLOW();
	}
}

void test19()/////////////////////////////////3 to 5
{
  CCD_forward(205,31);
  CCD_forward(205,3);
  CCD_forward(220,17);
  CCD_forward(220,3);
  CCD_forward(220,17);
  CCD_forward(220,3);
  CCD_forward(205,17);
}



void test20()///////////////////////////////////5平台
{
  test5();//////////////////pintai
  if(flag22=='C')
  {
  	D1=232;
	delay(300);
	D1=210;
	D3=225;
	delay(300);
	D3=200;
	delay(300);
  }
  ///////////////////
  ///////////////////////F_cycle(0,0,0);//400 30 65
  F_down();
}

void test21()/////////////////////////////////4 to 6
{
    DENG0=1;
    CCD_backward(65,31);
	CCD_backward(50,13);
	CCD_backward(50,27);
	CCD_backward(50,13);
	CCD_backward(50,27);

	CCD_backward(50,13);
	CCD_backward(50,27);
	DENG0=0;
}

void test22()//////////////////////////////////6平台
{  DENG0=1;
   CCD_backward(60,4);
	CCD_backward_R(65,9);
	CCD_backward(75,35);
	CCD_backward(75,40);
	if(fast_slow==1)
	{
	CCD_backward(65,4);
	////////////////////////////////////////////////B_turn_F_R();SPECIAL
	DENG0=0;
	FORWARD;
  delay(10);
  speedr=127+110;
  speedl=127-45;
  while(L4==0);
  speedr=127+110;
  speedl=127-90;
  while(R1==0);//前巡线板右边的灯也反了
 speedr=127;
  speedl=127;
  delay(80);
  }
  else
  {  
    CCD_backward(65,4);
    B_turn_F_R_SLOW();
    
  }
speedr=127;
speedl=127;
delay(250);
test6();
   DENG1=1;
   	  if(flag22=='D')
  {
  	D1=232;
	delay(300);
	D1=210;
	D3=225;
	delay(300);
	D3=200;
	delay(300);
}
  F_down();
  GM_forward_3D(190,3);
  //////////////////////////////////曲线有可能看不到，转弯要偏向曲线一点
  ////////////////////////////////////////F_turn_B_L();SPECIAL
  BACKWARD;
  delay(5);
  speedl=127+50;//60
  speedr=127-90;//127
  while(L4==0);
  speedl=127+70;//95
  speedr=127-80;//127
  while(R1==0);
  speedl=127+30;
  speedr=127-40;
  while(R4==0);
 
  speedr=127;
  speedl=127;
  delay(100);
isr_choose=1;
  flag_sp=0;
  DENG0=1;
  CCD_backward_L(70,9);
  CCD_backward(80,35);
  CCD_backward(80,40);
  CCD_backward_L(75,4);
  BELLON;
  
  CCD_backward_L(75,18);
  CCD_backward_R(75,12);
  CCD_backward_F(75,4);
  CCD_backward_R(75,3);
  BELLOFF;
  flag_sp=1;

  DENG1=0;
}

void test23()//////////////////////////5 to 7
{
  CCD_forward(205,4); 
	F_turn_B_L();
	speedr=127;
	speedl=127;
	delay(100);
}

void test24()//////////////////////////////6 to 7
{
  DENG0=1;
  CCD_backward(65,31);
  CCD_backward_R(55,13);
  CCD_backward(50,27);
  CCD_backward(50,13);
  CCD_backward(50,27);
  CCD_backward(50,13);
  CCD_backward(50,27);
  if(fast_slow==1)
  {
  GM_backward_3D(55,3);

  DENG0=0;
  //////////////////////////////////////////B_turn_F_L();SPECIAL
  FORWARD;
  delay(5);
  
  speedr=127-80;//90
  speedl=127+100;//128
  while(L4==0);
  speedr=127-20;//10
  speedl=127+40;//25
  while(L1==0);
  speedr=127;
  speedl=127;
  delay(100);
  }
  else
  {
    GM_backward_3D(65,3);
    B_turn_F_L_SLOW();
  }
  CCD_backward_F(50,3);
  
}

void test25()////////////////////////////7平台
{
 DENG0=1;
  CCD_backward_L(35,4);
  CCD_backward_L(35,18);
  if(fast_slow==1)
  {
  CCD_backward(60,4);
  B_turn_F_R();
  speedl=127;
  speedr=127;
  delay(100);
  }
  else
  {
    CCD_backward(65,4);
  B_turn_F_R_SLOW();
  }
  DENG0=0;
  DENG1=1;
  CCD_forward_B(170,3);
  
 CCD_forward(190,11);
 CCD_forward(190,12);
 CCD_forward(190,13);
 CCD_forward(190,31);
 CCD_forward(190,27);
 CCD_forward(190,40);
 
 CCD_forward(190,11);
 CCD_forward(190,31);
 BELLON;
 CCD_forward(185,13);
 CCD_forward(185,12);
 CCD_forward(185,26);
 BELLOFF;
 CCD_forward(185,40);
 CCD_forward(185,9);
 CCD_forward(190,23);
 CCD_forward(195,38);

 BELLON;
 if(fast_slow==1)
 {
 GM_forward_3D(195,4);
 BELLOFF;
 ///////////////////////////////////F_turn_B_L();SPECIAL
 BACKWARD;
  delay(5);
  speedl=127+35;//60
  speedr=127-105;//127
  while(L4==0);
  speedl=127+67;//95
  speedr=127-107;//127
  while(R1==0);
  speedl=127+30;
  speedr=127-40;
  while(R4==0);
  speedr=127;
  speedl=127;
  delay(100);
  }
  else
  {
    GM_forward_3D(195,4);
	F_turn_B_L_SLOW();
  }
  CCD_backward_F(60,3);
  if(fast_slow==1)
  {
  GM_backward_3D(60,3);
  ///////////////////////////////////////////B_turn_F_L(); SPECIAL
  FORWARD;
  delay(5);
  speedr=127-45;//20
  speedl=127+100;
  while(R1==0);
  speedr=127-90;//90
  speedl=127+100;//128
  while(L4==0);
  speedr=127-30;//90
  speedl=127+40;//128
  while(L1==0);
  speedr=127;
  speedl=127;
  delay(120);
  }
  else
  {
    GM_backward_3D(65,3);
    B_turn_F_L_SLOW();
  }
  DENG1=1;
  CCD_forward(190,11);
  ///////////////////////////////////////////////////
  GM_forward(190,43);
  GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);

GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
  speedr=127;
  speedl=127;
  delay(700);
  GM_forward_3D(165,11);
  GM_forward_3D(170,25);
  CCD_forward(175,9);
  CCD_forward(180,23);
  CCD_forward(180,38);
  CCD_forward(195,31);
 
  
  CCD_forward(195,11);
  BELLON;

  GM_forward_3D(205,25);
  GM_forward_3D(205,39);

  GM_forward_3D(205,9);
  GM_forward_3D(205,23);
  GM_forward_3D(205,38);
  GM_forward_3D(210,11);
  GM_forward_3D(210,9);
  GM_forward_3D(205,23);
  BELLOFF;
  
  F_cycle_sp(430,100,50);/////////////////335,100,70
  if(flag33=='E')
  {
  	D1=232;
	delay(300);
	D1=210;
	D3=225;
	delay(300);
	D3=200;
	delay(300);
}



/////////////////////////////////////////
/*	NNN=0;
	
	do
   {
		cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	  
	//}
	 
	//delay(10);
	 if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	 { 
	NNN=(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
	}
	if(abs(NNN-Average1)>180)
	{
	
	  if(NNN>Average1)
	  {
	   speedr=127-40;
    speedl=127+40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);

	  }
	  else
	  {
	   speedr=127+40;
    speedl=127-40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	  }
	
	}
	else
	{

	  if(NNN>Average1)///////youpian
	  {
	   
	speedr=127+40;
    speedl=127-40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	
	  }
	  else//////////zuopian
	  {
	  speedr=127-40;
    speedl=127+40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	   
	  }
	}
	}
	while(abs(Average1-NNN)>=5);
	NNN=0;LLL=0;Average1=0;Average2=0;*/
	///////////////////////////////////////////
  CCD_forward_ss();
  CCD_forward(155,11);
  GM_forward_3D(155,9);
  GM_forward_3D(155,23);
  GM_forward_3D(155,12);
  GM_forward_3D(155,26);
  CCD_forward(175,9);
  CCD_forward(175,23);
  CCD_forward(190,11);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);

  speedr=127;
  speedl=127;
  delay(600);
  GM_forward_3D(170,11);
  GM_forward_3D(175,25);
  speedr=127;
  speedl=127;
  delay(100);
  if(fast_slow==1)
  {
  GM_forward_3D(205,3);
  /////////////////////////////////F_turn_B_R();SPECIAL
  BACKWARD;
  delay(5);
  speedl=127-90;
  speedr=127+40;////43
  while(R1==0);
  speedl=127-90;
  speedr=127+80;////100
  while(L4==0);
  
  speedr=127;
  speedl=127;
  delay(130);
  }
  else
  {
    GM_forward_3D(192,3);
    F_turn_B_R_SLOW();
  }
  CCD_backward(65,4);
  if(fast_slow==1)
  {
  GM_backward_3D(65,4);
  ////////////////////////////////B_turn_F_R();SPECIAL
  FORWARD;
  delay(5);
  speedr=127+110;
  speedl=127-50;
  while(L4==0);
  speedr=127+110;
  speedl=127-95;
  while(R1==0);//前巡线板右边的灯也反了
  
  speedl=127;
  speedr=127;
  delay(100);
  }
  else
  {
    GM_backward_3D(65,4);
	 B_turn_F_R_SLOW();
  }
   CCD_forward(190,11);
   CCD_forward(190,25);
  CCD_forward(190,12);
  CCD_forward(190,13);
  CCD_forward(190,27);
  CCD_forward(190,11);
  CCD_forward(190,13);
  CCD_forward(190,12);

  CCD_forward(190,26);
  CCD_forward(190,40);
  if(fast_slow==1)
  {
  CCD_forward(200,4);
  ////////////////////////////////////F_turn_B_L();SPECIAL
  BACKWARD;
  delay(5);
  speedl=127+43;//60
  speedr=127-127;//127
  while(L4==0);
  speedl=127+90;//95
  speedr=127-110;//127
  while(R1==0);
  speedr=127;
  speedl=127;
  delay(100);
  }
else
{  
  CCD_forward(195,4);
  F_turn_B_L_SLOW();
}

  DENG1=0;
  DENG0=1;
  CCD_backward_F(70,3);
  CCD_backward_R(55,3);
  CCD_backward_R(55,17);
  CCD_backward(75,3);
  
}

void test26()//////////////////////////////5 to 8
{
DENG1=1;
    CCD_forward(200,13);
  CCD_forward(205,27);
  CCD_forward(225,13);
  CCD_forward(225,27);
  CCD_forward(225,13);
  CCD_forward(225,27);
  CCD_forward(225,13);
  CCD_forward(225,27);
  CCD_forward_L(225,13);
  CCD_forward_L(225,27);
  CCD_forward_L(210,13);
  CCD_forward_L(205,27);
  DENG1=0;
}

void test27()///////////////////////////////8平台
{
if(fast_slow==1)
{
  GM_forward_3D(200,4);
  F_turn_B_L();
  }
  else
  {  
  GM_forward_3D(195,4);
  F_turn_B_L_SLOW();
  }
  DENG0=1;
  //CCD_backward_F(65,3);
  //CCD_backward_F(65,17);
  CCD_backward(55,31);
  CCD_backward(55,3);
  CCD_backward(55,17);
  DENG0=0;
  if(fast_slow==1)
  {
  GM_backward_3D(60,3);
	B_turn_F_L();
  speedr=127;
  speedl=127;
  delay(100);
  }
  else
  {
    GM_backward_3D(65,3);
	B_turn_F_L_SLOW();
  }
  DENG1=1;
  CCD_forward(170,44);
 
  
  DENG1=0;
  if(fast_slow==1)
  {
  GM_forward_3D(205,4);
  F_turn_B_L();
  }
  else
  {
    GM_forward_3D(195,4);
  F_turn_B_L_SLOW();
  }
  CCD_backward(60,31);
  if(fast_slow==1)
  {
  GM_backward_3D(60,3);
  B_turn_F_L();
  speedl=127;
  speedr=127;
  delay(110);
  }
  else
  
  {
    GM_backward_3D(65,3);
  B_turn_F_L_SLOW();
  }
  test13();///珠峰
   CCD_forward(190,11);
  GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
  speedr=127;
  speedl=127;
  delay(720);
  GM_forward_3D(170,11);
  CCD_forward(170,25);
  CCD_forward(170,40);

  /*GM_forward_3D(170,13);
  speedr=127;
  speedl=127;
  delay(400);
  speedr=100;
  speedl=100;
  while(1)
  {
    if(RR==0)
	{
	  delay(5);
	  if(RR==0)
	  {
	    break;
	  }
	}
  }
  speedr=127;
  speedl=127;
  delay(200);
  BACKWARD;
  delay(5);
  speedr=127+80;
  speedl=127-80;
  while(R1==0);
  speedr=127+60;
  speedl=127-60;
  while(L3==0);
  speedr=127+30;
  speedl=127-30;*/
  GM_forward_3D(195,3);
  F_turn_B_R_SLOW();
  speedr=127;
  speedl=127;
  delay(200);
  DENG0=1;
  CCD_backward_F(65,4);
  CCD_backward_F(65,18);

  
  if(fast_slow==1)
  {
  GM_backward_3D(65,4);
  //////////////////////////////////B_turn_F_R();SPECIAL
	FORWARD;
  delay(5);
  speedr=127+110;
  speedl=127-40;
  while(L4==0);
  speedr=127+110;
  speedl=127-90;
  while(R1==0);//前巡线板右边的灯也反了
 
speedr=127;
speedl=127;
delay(100);
}
else
{
  GM_backward_3D(60,4);
  B_turn_F_R_SLOW();
}
CCD_forward(200,31);
  if(fast_slow==1)
  {
  GM_forward_3D(205,3);
  F_turn_B_R();

  speedr=127;
  speedl=127;
  delay(100);
  }
else
{  
  GM_forward_3D(195,3);
  F_turn_B_R_SLOW();
}
  DENG0=1;
  CCD_backward(55,31);
  GM_backward_3D(55,4);
  CCD_backward(55,18);
  if(fast_slow==1)
  {
  GM_backward_3D(65,4);
  DENG0=0;
  B_turn_F_R();
  speedl=127;
  speedr=127;
  delay(80);
  }
  else
  {
    GM_backward_3D(65,4);
    B_turn_F_R_SLOW();
  }
  DENG1=1;
  CCD_forward(190,31);/////////////////////加段延时，场地原因
  CCD_forward_R(205,4);
  CCD_forward_R(205,18);
  CCD_forward_R(205,4);
  CCD_forward_R(205,18);
}

void test28()////////////////////////6to8
{
  speedr=127;
  speedl=127;
  delay(200);
  CCD_forward_L(180,3);
  CCD_forward_L(180,17);
  CCD_forward_L(200,13);
  CCD_forward_L(200,27);
}


void test31()////////////////////////////////////////7tohome
{
 DENG0=1;
  CCD_backward(65,9);
  CCD_backward(75,23);
	CCD_backward(85,12);
	CCD_backward(85,13);
	CCD_backward(85,27);
	CCD_backward(85,40);
	CCD_backward(75,23);
  GM_backward_3D(55,3);
  speedr=55;
  speedl=55;
  while(1)
  {
    if(R1==1)
	{
	  delay(5);
	  if(R1==1)
	    break;
	}
  }
  ////////////////////////B_turn_F_R();SPECIAL
  FORWARD;
  delay(5);
  speedr=127+128;
  speedl=127-30;
  while(L4==0);
  speedr=127+128;
  speedl=127-70;
  while(R1==0);//前巡线板右边的灯也反
  speedr=127;
  speedl=127;
  delay(50);
  CCD_backward(55,31);
  if(fast_slow==1)
  {
  CCD_backward(55,4);
  //////////////////////////////////////////////////////B_turn_F_R();有钉子

  FORWARD;
  delay(5);
  speedr=127+128;
  speedl=127-20;
  while(L4==0);
  speedr=127+128;
  speedl=127-80;
  while(R1==0);//前巡线板右边的灯也反了
  speedr=127+40;
  speedl=127-10;
  while(R4==0);
speedl=127;
speedr=127;
delay(80); 
}
else
{
  CCD_backward(65,4);
  B_turn_F_R_SLOW();
}
  
  DENG0=0;
  	CCD_forward(205,31);
	if(fast_slow==1)
	{
	GM_forward_3D(205,3);
	F_turn_B_R();
}
else
{ 
  GM_forward_3D(195,3);
  F_turn_B_R_SLOW();
}
	DENG0=1;
	CCD_backward(65,9);

	speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==0)
	  {
	    delay(10);
	    if(JJ4==0)
		{
		   break;
		}
	  }
	}
    speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==1)
	  {
	    delay(10);
		if(JJ4==1)
		{
		  break;
		}
	  }
	}
	speedr=75;
	speedl=75;
	while(1)
	{
	  if(JJ4==0)
	  {
	    delay(10);
		if(JJ4==0)
		{
		  break;
		}
	  }
	}
	speedr=75;
	speedl=75;
	while(1)
    {
	  if(JJ4==1)
	  {
	    delay(10);
		if(JJ4==1)
		{
		  break;
		}
	  }
	}
	DENG0=0;
}

void test32()///////////////////////////////////////8tohome
{

	 CCD_forward(195,3);
  //F_turn_B_R_SLOW();
  BACKWARD;
  delay(5);
  speedl=127-85;////110
  speedr=127+60;
  while(R1==0);
  speedl=127-90;/////110
  speedr=127+90;
  while(L4==0);
  speedl=127-60;
  speedl=127+70;
  while(L1==0);
  speedr=127;
  speedl=127;
  delay(250);
    CCD_forward(170,11);
	CCD_forward(170,25);
    speedr=170;
	speedl=170;
	delay(250);
	CCD_forward(170,12);
	CCD_forward(170,13);
	CCD_forward(170,27);
	CCD_forward(170,40);
	CCD_forward(170,9);
	CCD_forward(170,23);
		CCD_forward(170,13);
	CCD_forward(170,27);


	  GM_forward_3D(195,4);
	F_turn_B_L_SLOW();
	
	CCD_forward_B(195,3);
	CCD_forward_B(195,17);
	
	
     CCD_forward(195,4);
      F_turn_B_R_SLOW();
   
	DENG1=1;
	CCD_forward_B(200,3);
	CCD_forward_B(200,17);

    GM_forward_3D(195,3);
   F_turn_B_R_SLOW();
  
	DENG0=1;
	CCD_backward(55,9);

	speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==0)
	  {
	    delay(10);
	    if(JJ4==0)
		{
		   break;
		}
	  }
	}
    speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==1)
	  {
	    delay(10);
		if(JJ4==1)
		{
		  break;
		}
	  }
	}
	speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==0)
	  {
	    delay(15);
		if(JJ4==0)
		{
		  break;
		}
	  }
	}
	speedr=65;
	speedl=65;
	while(1)
    {
	  if(JJ4==1)
	  {
	    delay(15);
		if(JJ4==1)
		{
		  break;
		}
	  }
	}
	
	DENG0=0; 
}

void test33()////////////////////////7to8
{
 B_turn_F_L();
  speedr=127;
  speedl=127;
  delay(100);
  CCD_forward(200,31);
  CCD_forward(205,13);
  CCD_forward(205,27);
  CCD_forward(215,13);
  CCD_forward(215,27);
  CCD_forward(215,13);
  CCD_forward(215,27);
  CCD_forward_L(215,13);
  CCD_forward_L(215,27);
  CCD_forward_L(205,13);
  CCD_forward_L(205,27); 
}

void test34()////////////////////////8to7
{
  CCD_forward(225,12);
  CCD_forward(225,26);
  CCD_forward(230,12);
  CCD_forward(230,26);
  CCD_forward(225,12);
  CCD_forward(225,26);
if(fast_slow==1)
{
  CCD_forward(205,3);
F_turn_B_R();
}
else
{
 CCD_forward(195,3);
F_turn_B_R_SLOW(); 
}

 
  CCD_backward(60,31);
}

void test35()///////////////////////////////8to5
{
 CCD_forward(200,13);
  CCD_forward(225,27);
  CCD_forward(225,13);
  CCD_forward(225,27);
  CCD_forward(225,13);
  CCD_forward(225,27);
  CCD_forward(210,13);
  CCD_forward(210,27);
}

void test36()//////////////////////////5to节点
{
   CCD_forward(200,13);
  CCD_forward(225,27);
  CCD_forward(225,13);
  CCD_forward(225,27);
  CCD_forward(225,13);
  CCD_forward(225,27);
  if(fast_slow==1)
  {
  CCD_forward(205,4);
  F_turn_B_L();
}
else
{
  CCD_forward(195,4);
  F_turn_B_L_SLOW();
}
	 CCD_forward(170,11);
	CCD_forward(170,25);
    speedr=170;
	speedl=170;
	delay(250);
	CCD_forward(170,12);
	CCD_forward(170,13);
	CCD_forward(170,27);
	CCD_forward(170,40);
	CCD_forward(170,9);
	CCD_forward(170,23);
	CCD_forward(170,13);
	CCD_forward(170,27);



}

void test37()///////4&4tohome
{ if(fast_slow==1)
{
  GM_forward_3D(205,4);
  F_turn_B_L();
  }
  else
  {
    GM_forward_3D(195,4);
  F_turn_B_L_SLOW();
  }
  CCD_forward(200,31);
  CCD_forward(210,4);
  CCD_forward(210,18);
  CCD_forward(210,4);
  CCD_forward(210,18);
  test4();
  F_down();
  DENG1=1;
  CCD_forward(200,31);
  CCD_forward(210,3);
  CCD_forward(210,17);
  if(fast_slow==1)
  {
  CCD_forward(205,3);
  F_turn_B_L();
  }
  else
  {
    CCD_forward(195,3);
  F_turn_B_L_SLOW();
  }
  CCD_forward(195,31);
  if(fast_slow==1)
  {
  GM_forward_3D(205,3);
  F_turn_B_R();
  }
else 
{
  GM_forward_3D(195,3);
  F_turn_B_R_SLOW();
}
  DENG0=1;
  CCD_backward(65,31);
  
	CCD_backward(65,9);
	
	speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==0)
	  {
	    delay(10);
	    if(JJ4==0)
		{
		   break;
		}
	  }
	}
    speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==1)
	  {
	    delay(10);
		if(JJ4==1)
		{
		  break;
		}
	  }
	}
	speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==0)
	  {
	    delay(15);
		if(JJ4==0)
		{
		  break;
		}
	  }
	}
	speedr=65;
	speedl=65;
	while(1)
    {
	  if(JJ4==1)
	  {
	    delay(15);
		if(JJ4==1)
		{
		  break;
		}
	  }
	}
	
	DENG0=0; 
}

void test38()///////3&3tohome
{
 if(fast_slow==1)
 {
  GM_forward_3D(205,3);
  F_turn_B_R();
  }
  else
  {
    GM_forward_3D(195,3);
  F_turn_B_R_SLOW();
  }
  CCD_forward(205,31);
  CCD_forward(210,3);
  CCD_forward(210,17);
  test3();
  F_down();
  DENG1=1;
  CCD_forward(200,31);
  CCD_forward_R(210,4);
  CCD_forward_R(210,18);
  CCD_forward_L(205,3);
  CCD_forward_L(205,17);
  if(fast_slow==1)
  {
  CCD_forward(205,3);
  F_turn_B_R();
  }
  else
  {
    CCD_forward(195,3);
  F_turn_B_R_SLOW();
  }
  CCD_forward(200,31);
  if(fast_slow==1)
  {
  CCD_forward(205,3);
  F_turn_B_R();
  }
  else
  {
    CCD_forward(195,3);
  F_turn_B_R_SLOW(); 
  }
  DENG0=1;
    CCD_backward(60,31);
	CCD_backward(55,9);

	speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==0)
	  {
	    delay(10);
	    if(JJ4==0)
		{
		   break;
		}
	  }
	}
    speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==1)
	  {
	    delay(10);
		if(JJ4==1)
		{
		  break;
		}
	  }
	}
	speedr=65;
	speedl=65;
	while(1)
	{
	  if(JJ4==0)
	  {
	    delay(15);
		if(JJ4==0)
		{
		  break;
		}
	  }
	}
	speedr=65;
	speedl=65;
	while(1)
    {
	  if(JJ4==1)
	  {
	    delay(15);
		if(JJ4==1)
		{
		  break;
		}
	  }
	}
	
	DENG0=0; 


}

void test39()////////////7to5
{
  
  FORWARD;
  delay(5);
  speedr=127+70;
  speedl=127-55;
  while(L4==0);
  speedr=127+85;
  speedl=127-85;
  while(R1==0);//前巡线板右边的灯也反了
  speedr=127+50;
  speedl=127-60;
  while(R4==0);
  speedr=127;
  speedl=127;
  delay(100);
  
}

void test40()////////////8to节点
{
  if(fast_slow==1)
 {
  CCD_forward(205,3);
  F_turn_B_R();
  speedr=127;
  speedl=127;
  delay(100);
  }
  else
  {
     CCD_forward(195,3);
  F_turn_B_R_SLOW();
  }
 

	 CCD_forward(170,11);
	CCD_forward(170,25);
    speedr=170;
	speedl=170;
	delay(250);
	CCD_forward(170,12);
	CCD_forward(170,13);
	CCD_forward(170,27);
	CCD_forward(170,40);
	CCD_forward(170,9);
	CCD_forward(170,23);
		CCD_forward(170,13);
	CCD_forward(170,27);
}

void test41()////////////////////////7to节点
{
   B_turn_F_L();
  speedr=127;
  speedl=127;
  delay(100);
  CCD_forward(200,31);
  CCD_forward(205,13);
  CCD_forward(205,27);
  CCD_forward(210,13);
  CCD_forward(210,27);
  if(fast_slow==1)
  {
  CCD_forward(205,4);
  F_turn_B_L();
   }
   else
   {
     CCD_forward(195,4);
  F_turn_B_L_SLOW();
   }
 


	CCD_forward(170,11);
	CCD_forward(170,25);
    speedr=170;
	speedl=170;
	delay(250);
	CCD_forward(170,12);
	CCD_forward(170,13);
	CCD_forward(170,27);
	CCD_forward(170,40);
	CCD_forward(170,9);
	CCD_forward(170,23);


}

void test42()
{
  CCD_forward(170,29);
	CCD_forward_SP(170,41);
	Average1=NNN/LLL;
	speedr=127;
	speedl=127;
	while(JJ5==1);

		NNN=0;
	
	do
   {
		cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	  
	//}
	 
	//delay(10);
	 if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	 { 
	NNN=(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
	}

	   speedr=127-40;
    speedl=127+40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200); 
	}
	while(abs(abs(Average1-NNN)-180)>=5);

}

void test43()/////////////////////////OK
{
    CCD_forward(170,29);
	CCD_forward_SP(170,41);
	Average1=NNN/LLL;
	speedr=127;
	speedl=127;
	while(JJ5==1);

		NNN=0;
	
	do
   {
		cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	  
	//}
	 
	//delay(10);
	 if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	 { 
	NNN=(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
	}

	if(abs(NNN-Average1)<360-abs(NNN-Average1))
	{ 
	   if(Average1<NNN)
	   {
	   speedr=127-40;
       speedl=127+40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
        }
		else
		{
		  speedr=127+40;
       speedl=127-40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
		}
	  
	
	}
	else
	{

	
	   
	   if(Average1<NNN)
	   {
	   speedr=127+40;
       speedl=127-40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
        }
		else
		{
		  speedr=127-40;
       speedl=127+40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
		}
	
	 
	}
	}
	while(abs(abs(Average1-NNN)-180)>=5); 
}


void test44()////////////////////////////调整平台
{
  	NNN=0;
	
	do
   {
		cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	  
	//}
	 
	//delay(10);
	 if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	 { 
	NNN=(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
	}

	if(abs(NNN-Average1)<360-abs(NNN-Average1))
	{ 
	   if(Average1<NNN)
	   {
	   speedr=127-40;
       speedl=127+40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
        }
		else
		{
		  speedr=127+40;
       speedl=127-40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
		}
	  
	
	}
	else
	{

	
	   
	   if(Average1<NNN)
	   {
	   speedr=127+40;
       speedl=127-40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
        }
		else
		{
		  speedr=127-40;
       speedl=127+40;
	   delay(70);
	   speedl=127;
	   speedr=127;
	   delay(200);
		}
	
	 
	}
	}
	while(abs(abs(Average1-NNN)-180)>=5); 
}

void test45()
{
 while(1)
  {
      if(JJ5==0)
	  {
	  Send_byte(0XC0);
       }
	   break;
   }
   delay(2000);
   while(1)
   {
     if(JJ5==0)
	 {
	   Send_byte(0XC0);
	 }
	 break;
   }
}

void test46()//////7to6
{
  	DENG1=1;
   test39();
   CCD_backward(65,31);
   CCD_backward(45,13);
   CCD_backward(45,17);
   CCD_backward(45,13);
   CCD_backward(45,17);
   CCD_backward(55,13);
   CCD_backward(65,17);
   
}

void test47()////////////6to节点
{
  CCD_backward_R(65,4);
  B_turn_F_L_SLOW();
  DENG1=1;
  CCD_forward(170,11);
	CCD_forward(170,25);
    speedr=170;
	speedl=170;
	delay(250);
	CCD_forward(170,12);
	CCD_forward(170,13);
	CCD_forward(170,27);
	CCD_forward(170,40);
	CCD_forward(170,9);
	CCD_forward(170,23);
		CCD_forward(170,13);
	CCD_forward(170,27);
}

void test48()///8to6
{ 
  
  CCD_forward_B(200,4);
  CCD_forward_B(200,18);
  speedr=180;
  speedl=180;
  delay(200);
  speedr=127;
  speedl=127;
  delay(600);
}


////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////************  主程序
///////////////////////////////////////////////////////////////

void main()
{
	PCA0MD &= ~0x40;

	sysclk();
	pio();
	PCA0();
	AD();


	AMX0P=0X01;
	light_gain();
	AMX0P=0X00;

	SINPUT=0;
	CLK=0;
	SINPUT=1;

	UART0();
	timer1();

	UART1();

	
	INTT();
	timer2();
	delay(10);

	timer0();
    
	  D1=225;
	  D2=225;
	 
	
  /*isr_choose=1;
  flag_sp=0;
  CCD_backward_L(70,9);
  TR0=1;
  CCD_backward(92,35);
  CCD_backward(90,40);
  CCD_backward_L(75,4);
  
  
  CCD_backward_L(75,18);
  CCD_backward_R(75,12);
  
  CCD_backward_F(75,4);
  CCD_backward_R(75,3);
  flag_sp=1;*/
  

/*CCD_forward(170,31);
  CCD_forward_SP(170,41);
Average1=NNN/LLL;
  DENG1=0;
  GM_forward_3D(200,4);
  F_turn_B_L();
  CCD_backward_F(60,3);
  GM_backward_3D(60,3);
  B_turn_F_L();
  speedl=127;
  speedr=127;
  delay(100);
  test13();///珠峰*/
  

/*CCD_forward(155,29);
CCD_forward_SP(170,41);
Average1=NNN/LLL;
GM_forward_3D(205,4);
  F_turn_B_L();
  GM_backward_3D(60,3);
  B_turn_F_L();
  speedl=127;
  speedr=127;
  delay(60);
  test13();///珠峰*/


    /*CCD_forward(180,4);
	 CCD_forward_SP(180,41);
	 Average1=NNN/40;
	 CCD_forward(180,3);
	 
	
	 
TR0=1;*/
 
	
   /*while(1)////////////////////////////////////////OLED的端口还未设置 
	{		
	cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	    
	delay(50);
	}*/
    
	
	
	

	
/********3 5 8*******75miao**/
	/*test16();/////chu
	test17();////3
	test19();////3to5
	test20();////5
	test26();///5to8
	test27();////8*/
/********3 5 7*******65miao**/
	/*test16();/////chu
    test17();////3
	test19();/////3to5
    test20();////5
	test23();////5to7
	test25();////7*/

/********3 6 7******75miao**/
	/*test16();//////chu
	test17();/////3
	test22();////6
	test24();////6to7
	test25();/////7*/

/********3 6 8******76miao**/
   /*test16();/////chu
	test17();/////3
    test22();/////6
	test28();////6to8
	test27();/////8*/

/********4 5 7******58miao**/
	/*test16();////chu
	test18();////4
	test20();////5
	test23();////5to7
	test25();////7*/

/********4 5 8******75miao**/
	/*test16();////chu
	test18();////4
	test20();////5
	test26();////5to8
	test27();////8*/

/********4 6 7******74miao**/
    /*test16();////chu
	test18();////4
	test21();////4to6
	test22();////6
	test24();////6to7
	test25();////7*/

/********4 6 8******77miao**/
    /*test16();////chu
	test18();////4
	test21();////4to6
	test22();////6
	test28();////6to8
	test27();////8*/
    
/********调试*********////////////////////////////////////////////////////////////////////
/*while(1)
{ 
   if(JJ2==0)
   {
    delay(1000);
    while(1)
   {
      
      if(JJ2==0)
     {
     delay(5);
     if(JJ2==0)
     {
      test2();
	break;
      }
	  
	}
	if(JJ3==0)
	{delay(5);
	if(JJ3==0)
	{
	 test3();
	break;
	}
	}
	if(RR==0)
	{delay(5);
	if(RR==0)
	{
	 test4();
	break;
	}
	}
	if(JJ5==0)
	{
    delay(5);
    if(JJ5==0)
    {
	test5();
	break;
	}
   }
   if(LL==0)
   {delay(5);
   if(LL==0)
   {
	test6();
	break;
    }
   }
  }
  }
}*/


   //test2();//////2pintai
   //test3();/////3pintai
   //test4();////4pintai
   //test5();//////5pintai
   //test6();/////6pintai
	//test13();///////珠峰
    //test16();////chu
	//test17();////3
	//test18();////4
	//test19();////3to5
    //test20();////5
	//test21();////4to6
    //test22();////6
	//test23();////5to7
	//test24();////6to7
	//test25();////7
	//test26();////5to8
	//test28();////6to8
    //test27();////8
	//test30();
	//test31();
	//test32();
	//test34(); 
    //test36();
    //test37();
    //test38();
   //test40();
    //test47();////6to节点
//test48();////8to节点
 /*if(fast_slow==1)
  {
  GM_backward_3D(65,4);
  DENG0=0;
  B_turn_F_R();
  speedl=127;
  speedr=127;
  delay(80);
  }
  else
  {
    GM_backward_3D(65,4);
    B_turn_F_R_SLOW();
  }
  DENG1=1;
  CCD_forward(190,31);/////////////////////加段延时，场地原因
  CCD_forward_R(205,4);
  CCD_forward_R(205,18);
  CCD_forward_R(205,4);
  CCD_forward_R(205,18);
 test48();//8to6
	   test22();////6
	   test47();//6to节点
	   test38();/////////3&3tohome*/

 


  
/*CCD_forward(170,29);
CCD_forward_SP(170,41);


Average1=NNN/15;
speedr=127;
speedl=127;
while(JJ5==1);


NNN=0;
	
	do
   {
		cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////除了8以外的数都不能输出正常值
      {
      break;
      }  
	}
	  
	//}
	 
	//delay(10);
	 if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	 { 
	NNN=(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
	}
	if(abs(NNN-Average1)>180)
	{
	
	  if((NNN)>Average1)
	  {
	   speedr=127-40;
    speedl=127+40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);

	  }
	  else
	  {
	   speedr=127+40;
    speedl=127-40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	  }
	
	}
	else
	{

	  if(NNN>Average1)///////youpian
	  {
	   
	speedr=127+40;
    speedl=127-40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	
	  }
	  else//////////zuopian
	  {
	  speedr=127-40;
    speedl=127+40;
	delay(70);
	speedl=127;
	speedr=127;
	delay(200);
	   
	  }
	}
	}
	while(abs(Average1-NNN)>=5);*/

/////////////////////////////////////////////////////////////////////////////////二型寻宝
   
 

  sec_chance=1;
  fast_slow=0;

  while(1)
  { 
    flag_sp=0;
    NNN=0;
	LLL=0;
	Average1=0;
	Average2=0;
    speedr=127;
	speedl=127;
	while(1)
	{
	  if(JJ5==0)
	  { 
	  delay(5);
        if(JJ5==0)
		{
		  break;
		}
	  }
	};
	speedr=127;
	speedl=127;
    while(JJ5==0);
   test16();/////////chu
	switch(flag11)
	{
	  case 'A':
	  test17();//////3
	  
	  
      break;
	  case 'B':
	  test18();//////4
	  
	  break;
	}
	switch(flag22)
	{
	  case 'C':
	  if(flag11=='A')
	  {
	    test19();////3to5
	  }
	  test20();/////5
	  
	  break;
	  case 'D':
	  if(flag11=='B')
	  {
	    test21();///4to6
	  }
	  test22();/////6

	  break;
	}
	switch(flag33)
	{
	  case 'E':
	  if(flag22=='C')
	  {
	    test23();/////5to7
	  }
	  if(flag22=='D')
	  {
	    test24();////6to7
	  }
	   test25();////7
	 /*if(flag22!='D')
	 {
	 test33();////7to8
	 test27();////8
	 test40();/////8to节点
	 if(flag11=='B')
		{
		  test38();/////////3&3tohome
        }
		if(flag11=='A')
		{
		  test37();////////4&4tohome
		}
	 }
	 else
	 {
	 if(fast_slow==0)
	 {
	 test31();//////7tohome
	 }
	 else
	 {
	   test39();////7to5
	   test20();/////5
	   test36();//////5to节点
        if(flag11=='B')
		{
		  test38();/////////3&3tohome
        }
		if(flag11=='A')
		{
		  test37();///////4&4tohome
		}
	 }
	 }*/
	 //test31();//////7tohome
      if(flag22=='C')
	  {
	    test46();////7to6
        test22();///6
        test47();//6to节点
		if(flag11=='B')
		{
		  test38();/////////3&3tohome

        }
		if(flag11=='A')
		{
		  test37();/////////4&4tohome
		}
	  }
      if(flag22=='D')
	  {
	    test39();//7to5
        test20();///5
        test36();//5to节点
		if(flag11=='B')
		{
		  test38();/////////3&3tohome

        }
		if(flag11=='A')
		{
		  test37();/////////4&4tohome
		}
	  }  
	  break;
	  case 'F':
	  if(flag22=='C')
	  {
         test26();////5to8
	  }
	  if(flag22=='D')
	  {
	     test28();////6to8
	  }
	  
	  test27();/////8
	  /*if(flag22!='D')
	  {
	  test34();/////8to7
	  test25();/////7
	  test41();/////7to节点
      if(flag11=='B')
		{
		  test38();/////////3&3tohome

        }
		if(flag11=='A')
		{
		  test37();/////////4&4tohome
		}
	  }
	  else
	  {
	    if(fast_slow==0)
		{
		  test32();//////8tohome
		  
		}
		else
		{
	    test35();//////////8to5
		test20();///////////5
		test36();/////////5to节点
		if(flag11=='B')
		{
		  test38();/////////3&3tohome

        }
		if(flag11=='A')
		{
		  test37();/////////4&4tohome
		}

		}
	  }*/
	  //test32();//////8tohome
     if(flag22=='C')
	 {
	     test48();//8to6
	   test22();////6
	   test47();//6to节点
	   if(flag11=='B')
		{
		  test38();/////////3&3tohome

        }
		if(flag11=='A')
		{
		  test37();/////////4&4tohome
		}
	 }
	 if(flag22=='D')
	 {
	  test35();// 8to5 
	  test20();///5
      test36();//5to节点
	  if(flag11=='B')
		{
		  test38();/////////3&3tohome

        }
		if(flag11=='A')
		{
		  test37();/////////4&4tohome
		}
	 }
	 if(flag11)
	  break;
	}
	sec_chance=2;
	}
  
		 
/********检测********/
  
////////////////////////////////////////////////////////////

/*****指南针检测*****/
    /*CCD_forward(180,4);
	CCD_forward_SP(180,41);
	Average1=NNN/LLL;
	speedr=127;
	speedl=127;
	while(1)
	{
	  if(JJ4==0)
	  {
	    delay(5);
		if(JJ4==0)
		{
		  break;
		}
	  }
	}
	CCD_forward(180,4);
	CCD_forward_SP(180,41);
	Average2=NNN/LLL;
	speedl=127;
	speedr=127;
	if(Average1<Average2)
	{
	  if(Average2-Average1<=10)
	  {
	    BELLON;
		delay(200);
		BELLOFF;
		delay(200);
		BELLON;
		delay(200);
		BELLOFF;

	  }
	}
	 if(Average1>=Average2)
	{
	  if(Average1-Average2<=10)
	  {
	    BELLON;
		delay(200);
		BELLOFF;
	  }
	}*/
	/*CCD_forward(180,4);

	CCD_forward_SP(180,41);*/
       
/******寻宝检测******/
    //CCD_forward(191,11);
	//CCD_forward(200,11);
    //F_up_stage();
	 /*speedr=185;
	speedl=190;
	while(1)
	{
	  if(JJ2==0)
	  {
	    delay(5);
	    if(JJ2==0)
		{
		   break;
		}
	  }
	}
    speedr=185;
	speedl=190;
	while(1)
	{
	  if(JJ2==1)
	  {
	    delay(5);
		if(JJ2==1)
		{
		  break;
		}
	  }
	}
	speedr=185;
	speedl=190;
	while(1)
	{
	  if(JJ2==0)
	  {
	    delay(5);
		if(JJ2==0)
		{
		  break;
		}
	  }
	}
	speedr=185;
	speedl=190;
	while(1)
    {
	  if(JJ2==1)
	  {
	    delay(5);
		if(JJ2==1)
		{
		  break;
		}
	  }
	}
	speedr=185;
	speedl=185;
	while(1)
	{
	  if(JJ5==0)
	  {
	    delay(5);
		if(JJ5==0)
		{
		  break;
		}
	  }
	}
	DENG1=1;
    speedr=127;
	speedl=127;
	delay(200);*/
    //numberAB();

   //numberCD();
    //numberEF();
	

/****CCD延时检测****/
    //CCD_forward(200,31);
	//CCD_forward(200,32);
	//CCD_forward(200,35);

    //CCD_backward(65,31);
	//CCD_backward(55,32);
	//CCD_backward(75,35);

/******转弯检测******/
     /*while(1)
	 {
	 if(JJ2==0)
	 {
	 delay(5);
	 if(JJ2==0)
	 {
       CCD_forward(205,3);
       F_turn_B_R();
        break;
	  }
	 }
	 while(1)
	 {
	 if(JJ3==0)
	 {
	 delay(5);
	 if(JJ3==0)
	 {
       CCD_forward(205,4);
       F_turn_B_L();
	   break;
	  }
	 }
	 while(1)
	 {
	 if(JJ4==0)
	 {
	 delay(5);
	 if(JJ4==0)
	 {
       CCD_backward(55,4);
       B_turn_F_R();
	   break;
	  }
	 }
	 while(1)
	 {
	 if(JJ5==0)
	 {
	 delay(5);
	 if(JJ5==0)
	 {
       CCD_forward(55,3);
       B_turn_F_L();
	   break;
	  }
	 }*/

//////////////////////////////////////////SLOW
	 /*while(1)
	 {
	 if(JJ2==0)
	 {
	 delay(5);
	 if(JJ2==0)
	 {
       CCD_forward(195,3);
       F_turn_B_R_SLOW();
	   break;
	  }
	 }
	 while(1)
	 {
	 if(JJ3==0)
	 {
	 delay(5);
	 if(JJ3==0)
	 {
       CCD_forward(195,4);
       F_turn_B_L_SLOW();
	   break;
	  }
	 }
	 while(1)
	 {
	 if(JJ4==0)
	 {
	 delay(5);
	 if(JJ4==0)
	 {
       CCD_backward(65,4);
       B_turn_F_R_SLOW();
	   break;
	  }
	 }
	 while(1)
	 {
	 if(JJ5==0)
	 {
	 delay(5);
	 if(JJ5==0)
	 {
       CCD_forward(65,3);
       B_turn_F_L_SLOW();
	   break;
	  }
	 }*/




/*****前光敏检测*****/
    /*while(1)
	{
	  FORWARD;
	  if(R1==1)
	  {
	    delay(5);
	    if(R1==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(R2==1)
	  {
	    delay(5);
	    if(R2==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(R3==1)
	  {
	    delay(5);
	    if(R3==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(R4==1)
	  {
	    delay(5);
	    if(R4==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(L1==1)
	  {
	    delay(5);
	    if(L1==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(L2==1)
	  {
	    delay(5);
	    if(L2==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(L3==1)
	  {
	    delay(5);
	    if(L3==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(L4==1)
	  {
	    delay(5);
	    if(L4==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	}*/


/*****后光敏检测*****/
    /*while(1)
	{
	  BACKWARD;
	  if(R1==1)
	  {
	    delay(5);
	    if(R1==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(R2==1)
	  {
	    delay(5);
	    if(R2==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(R3==1)
	  {
	    delay(5);
	    if(R3==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(R4==1)
	  {
	    delay(5);
	    if(R4==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(L1==1)
	  {
	    delay(5);
	    if(L1==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(L2==1)
	  {
	    delay(5);
	    if(L2==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(L3==1)
	  {
	    delay(5);
	    if(L3==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	  if(L4==1)
	  {
	    delay(5);
	    if(L4==1)
		{
		  BELLON;
		  delay(200);
		  BELLOFF;
		  delay(200);
		}
	  }
	}*/

/*****接近&色标*****/
     /*while(1)
	 {
	   if(JJ2==0)
	   {
	     delay(5);
		 if(JJ2==0)
		 {
		   BELLON;
		   delay(200);
		   BELLOFF;
		   delay(200);
		 }
	   }
	   if(JJ3==0)
	   {
	     delay(5);
		 if(JJ3==0)
		 {
		   BELLON;
		   delay(200);
		   BELLOFF;
		   delay(200);
		 }
	   }
	   if(JJ4==0)
	   {
	     delay(5);
		 if(JJ4==0)
		 {
		   BELLON;
		   delay(200);
		   BELLOFF;
		   delay(200);
		 }
	   }
	   if(JJ5==0)
	   {
	     delay(5);
		 if(JJ5==0)
		 {
		   BELLON;
		   delay(200);
		   BELLOFF;
		   delay(200);
		 }
	   }
	  if(LL==0)
	   {
	     delay(5);
		 if(LL==0)
		 {
		   BELLON;
		   delay(200);
		   BELLOFF;
		   delay(200);
		 }
	   }
	   if(RR==0)
	   {
	     delay(5);
		 if(RR==0)
		 {
		   BELLON;
		   delay(200);
		   BELLOFF;
		   delay(200);
		 }
	   }
	 }*/
/*****红外检测*****/
    /*while(1)
	 {
	   if(HW4==0)
	   {
	     delay(5);
		 if(HW4==0)
		 {
		   BELLON;
		   delay(200);
		   BELLOFF;
		 }
	   }
	 }*/
    
     	while(1)  
	{
	  speedr=127;
	  speedl=127;
	}
 
}

void Timer0_ISR (void) interrupt 1
{
   static int counter = 0;
   NNN=0;LLL=0;Average2=0;
   //TH0=(65536-60000)/256;
   //TL0=(65536-60000)%256;
   EA=0;/////////////////////////////////////////////
   if((counter++) == 160)
   {
      if(isr_choose==1)
	  {
	   if(flag_sp==0)
	   {
	   speedr=127;
	   speedl=127;
	   delay(200);
	   speedr=180;
	   speedl=180;
	   delay(200);
	   speedr=127;
	   speedl=127;
	   delay(200);
	   
	   }
	   else
	   {
	      flag_sp=0;isr_choose=0;
	      TR0=0;
	   }
       
	  }
	  if(isr_choose==2)
	  {
	    if(flag_sp==0)
		{
		  speedr=127;
		  speedl=127;
		  delay(200);
		  GM_backward_3D(100,9);
		  GM_backward_3D(100,23);
		  speedr=127;
		  speedl=127;
		  delay(200);
		  GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);

GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
GM_forward(190,43);
		  
		  speedr=127;
		  speedl=127;
		  delay(750);
		}
		else
		{
		  flag_sp=0;isr_choose=0;
		  TR0=0;
		}
	  }
      if(isr_choose==3)
	  {
     
     if(flag_sp==0)
	 {
	   speedr=127;
	   speedl=127;
	   delay(200);
	   speedr=70;
	   speedl=70;
	   delay(400);
       speedr=127;
	   speedl=127;
	   delay(100);
	   while(1)
	   {
	   cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	   //SBUF1=0X31;  
	   while(1)
	   {
	     if(SCON1&0X01)
         {
         SCON1&=~0X01;
         BUF[cnt]=SBUF1;
  	     cnt++;
         }
        if(cnt>=8)/////////////除了8以外的数都不能输出正常值
        {
        break;
        }  
	  }
	  
	
	 
	   delay(10);
	   if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	   { 
     	NNN=NNN+(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
     	LLL++;
     	}
		if(LLL>=15)
		{
		  break;
		}
	   }
	   Average2=NNN/LLL;

	   if(Average2>Average1)//////////////////////////////////////转太少   右卡
	   {
	     BELLON;
		 delay(200);
		 BELLOFF;
		 delay(200);
		 BELLON;
		 delay(200);
		 BELLOFF;
		 if(Average2-Average1<=10)
		 {
		   speedl=127;
		   speedr=127;
		   delay(200);
		 }
		 else if(Average2-Average1<=20)
		 {
          speedr=127+60;
		 speedl=127-60;
		 delay(150);
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
		 else
		 {
		 speedr=127+60;
		 speedl=127-60;
		 delay(300);
		 speedr=127;
		 speedl=127;
		 delay(100);

		 }

	   }
	   else///////////////////////转过头  左卡
	   {
	     BELLON;
		 delay(200);
		 BELLOFF;
		 if(Average1-Average2<=10)
		 {
		   speedr=127;
           speedl=127;
		   delay(200);
		 }
		 if(Average1-Average2<=20)
		 {
		   speedr=127-60;
		 speedl=127+60;
		 delay(150);
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
		 else
		 {
		 speedr=127-60;
		 speedl=127+60;
		 delay(300); 
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
	   }
	 }
	 if(flag_sp==1)
	 {
	   speedr=127;
	   speedl=127;
	   delay(200);
	   
	   while(1)
	   {
	   cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //发送1帧读取命令。
	   //SBUF1=0X31;  
	   while(1)
	   {
	     if(SCON1&0X01)
         {
         SCON1&=~0X01;
         BUF[cnt]=SBUF1;
  	     cnt++;
         }
        if(cnt>=8)/////////////除了8以外的数都不能输出正常值
        {
        break;
        }  
	  }
	  
	
	 
	   delay(10);
	   if((BUF[0]==0X0D)&&(BUF[1]==0X0A))
	   { 
     	NNN=NNN+(BUF[2]-0X30)*100+(BUF[3]-0X30)*10+(BUF[4]-0X30);
     	LLL++;
     	}
		if(LLL>=40)
		{
		  break;
		}
	   }
	   Average2=NNN/40;
	   if(abs(Average2-Average1)>180)
	   {
         if(Average2>Average1)//////////////////////////////////////转太duo   zuo卡
	   {
	     BELLON;
		 delay(200);
		 BELLOFF;
		
		 if((360-Average2)+Average1<=10)
		 {
		   speedl=127;
		   speedr=127;
		   delay(200);
		 }
		 else if((360-Average2)+Average1<=20)
		 {
		   speedr=70;
	   speedl=70;
	   delay(600);
       speedr=127;
	   speedl=127;
	   delay(100);
          speedr=127-60;
		 speedl=127+60;
		 delay(150);
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
		 else
		 {
		 speedr=70;
	   speedl=70;
	   delay(600);
       speedr=127;
	   speedl=127;
	   delay(100);
		 speedr=127-60;
		 speedl=127+60;
		 delay(300);
		 speedr=127;
		 speedl=127;
		 delay(100);

		 }

	   }
	   else///////////////////////转taishao  you卡
	   {
	     BELLON;
		 delay(200);
		 BELLOFF;
		 delay(200);
		 BELLON;
		 delay(200);
		 BELLOFF;
		 if((360-Average1)+Average2<=10)
		 {
		   speedr=127;
           speedl=127;
		   delay(200);
		 }
		 if((360-Average1)+Average2<=20)
		 {
		 speedr=70;
	   speedl=70;
	   delay(600);
       speedr=127;
	   speedl=127;
	   delay(100);
		   speedr=127+60;
		 speedl=127-60;
		 delay(150);
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
		 else
		 {
		 speedr=70;
	   speedl=70;
	   delay(600);
       speedr=127;
	   speedl=127;
	   delay(100);
		 speedr=127+60;
		 speedl=127-60;
		 delay(300); 
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
	   } 
	   }
       else
	   {
	   if(Average2>Average1)//////////////////////////////////////转太少   右卡
	   {
	     BELLON;
		 delay(200);
		 BELLOFF;
		 delay(200);
		 BELLON;
		 delay(200);
		 BELLOFF;
		 if(Average2-Average1<=10)
		 {
		   speedl=127;
		   speedr=127;
		   delay(200);
		 }
		 else if(Average2-Average1<=20)
		 {
		   speedr=70;
	   speedl=70;
	   delay(600);
       speedr=127;
	   speedl=127;
	   delay(100);
          speedr=127+60;
		 speedl=127-60;
		 delay(150);
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
		 else
		 {
		 speedr=70;
	   speedl=70;
	   delay(600);
       speedr=127;
	   speedl=127;
	   delay(100);
		 speedr=127+60;
		 speedl=127-60;
		 delay(300);
		 speedr=127;
		 speedl=127;
		 delay(100);

		 }

	   }
	   else///////////////////////转过头  左卡
	   {
	     BELLON;
		 delay(200);
		 BELLOFF;
		 if(Average1-Average2<=10)
		 {
		   speedr=127;
           speedl=127;
		   delay(200);
		 }
		 if(Average1-Average2<=20)
		 {
		 speedr=70;
	   speedl=70;
	   delay(600);
       speedr=127;
	   speedl=127;
	   delay(100);
		   speedr=127-60;
		 speedl=127+60;
		 delay(150);
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
		 else
		 {
		 speedr=70;
	   speedl=70;
	   delay(600);
       speedr=127;
	   speedl=127;
	   delay(100);
		 speedr=127-60;
		 speedl=127+60;
		 delay(300); 
		 speedr=127;
		 speedl=127;
		 delay(100);
		 }
	   }
	   }
	 }
     if(flag_sp==2)
	 {
	   NNN=0;LLL=0;Average1=0;Average2=0;flag_sp=0;isr_choose=0;
	   TR0=0;
	 }

	 }
	  counter=0;
   }
   EA=1;////////////////////////////////////
   TH0=(65536-60000)/256;
   TL0=(65536-60000)%256;
  
}




void TIMER2INT(void) interrupt 5  //T2中断产生CLK和SI,CCD采集数据
{
TF2H=0;   //清中断
CLK=1;
SINPUT=0;

if(SIFLAG)                        //第一次的数据无效
{
	cjflag=1;
	AD0BUSY=1;                         //启动AD
	while(AD0INT==0);AD0INT=0;         //等待AD结束
	Image_Data[CLKFLAG]=ADC0H;         //图像数组

}
CLKFLAG++;
CLK=0;

if(CLKFLAG==129)
 {
	if(CCDDIR)
	{
		AMX0P=0X01; 
		light_gain();
		AMX0P=0X00;
	}
	else
	{
		AMX0P=0X04; 
		light_gain();
		AMX0P=0X03;
	}

	TMR2R=-(SYSCLK/DOTCLK);    //定时中断产生CCD的时钟信号CLK及串行输入SI
	CLKFLAG=0;
	SINPUT=1;
	SIFLAG=1;

	if(cjflag)
	{
		aftercj=1;
		TR2=0;ET2=0;
	}
 }

}
