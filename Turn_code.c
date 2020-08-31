#include"All_Include.h"


void F_turn_L()
{
  //CCD_forward(205,4);
  CCD_forward(180,14);
  speedl=127-100;
  speedr=127+80;
  while(R4==0);
}

void B_turn_L() 
{
  CCD_backward(55,3);
  CCD_backward(75,17);
  speedr=127;
  speedl=127;
  delay(10);
  speedr=127+120;
  speedl=127-70;
  while(L4==0);
  speedr=127+50;
  speedl=127-40;
  while(L1==0);
  speedr=127;
  speedl=127;
  while(1);
}


void B_turn_F_L()//OK  三教改
{
  //CCD_backward(55,3);
  //speedr=127;
 //speedl=127;
  //delay(150);
  FORWARD;
  delay(5);
  speedr=127-35;//20
  speedl=127+100;
  while(R1==0);
  speedr=127-85;//90
  speedl=127+110;//128
  while(L4==0);
  speedr=127-20;//10
  speedl=127+50;//25
  while(L1==0);
}

void B_turn_F_R()//OK
{
  //CCD_backward(55,4);//当检测到R1亮时，后巡线板右边的灯反了。。。
  FORWARD;
  delay(5);
  speedr=127+128;
  speedl=127-60;
  while(L4==0);
  speedr=127+128;
  speedl=127-90;
  while(R1==0);//前巡线板右边的灯也反了
  speedr=127+40;
  speedl=127-10;
  while(R4==0);
}

void F_turn_B_R()//OK  shun
{
  //CCD_forward(205,3);
  
  BACKWARD;
  delay(5);
  speedl=127-80;////80
  speedr=127+50;////50
  while(R1==0);
  speedl=127-80;/////80
  speedr=127+75;////75
  while(L4==0);
  speedl=127-30;////30
  speedl=127+30;////30
  while(L1==0);
  speedr=127;
  speedl=127;
  delay(80);
 
}

void F_turn_B_L()//
{
  //CCD_forward(204,4);
  //speedr=127;
  //speedl=127;
  //delay(100);
  BACKWARD;
  delay(5);
  speedl=127+30;//60
  speedr=127-127;//127
  while(L4==0);
  speedl=127+80;//95
  speedr=127-127;//127
  while(R1==0);
  speedl=127+30;

  speedr=127-40;
  while(R4==0);
  
  speedr=127;
  speedl=127;
  delay(100);
}

void B_up_stage(int s,int t,int c)
{
  //CCD_backward(55,9);
	speedr=55;
	speedl=55;
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
    speedr=55;
	speedl=55;
	while(1)
	{
	  if(JJ4==1)
	  {
	    delay(5);
		if(JJ4==1)
		{
		  break;
		}
	  }
	}
	speedr=60;
	speedl=60;
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
	speedr=65;
	speedl=65;
	while(1)
    {
	  if(JJ4==1)
	  {
	    delay(5);
		if(JJ4==1)
		{
		  break;
		}
	  }
	}
    speedr=127;
	speedl=127;
	delay(1500);
    speedr=127-123;
	speedl=127+90;
	delay(s);//500
	speedr=127-120;
	speedl=127+70;
	delay(t);//150
    speedr=127-120;
    speedl=127+40;
	delay(c);//20
	speedr=127;
	speedl=127;
	delay(100);
}

void F_up_stage(void)
{
  //CCD_forward(190,11);
    speedr=190;
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
    speedr=190;
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
	speedr=190;
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
	speedr=190;
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
    
}

void F_down()
{
  CCD_forward(165,11);
  CCD_forward(155,25);
  CCD_forward(155,9);
  CCD_forward(155,23);
  CCD_forward(155,9);
  CCD_forward(160,23);
  CCD_forward(160,38);
}

void B_down()
{
  CCD_backward(80,9);
  CCD_backward(85,23);
  CCD_backward(85,11);
  CCD_backward(85,25);
  CCD_backward(85,11);
  CCD_backward(85,25);
  CCD_backward(85,38);
}

void F_bridge()
{
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
  speedr=127;
  speedl=127;
  delay(700);
  GM_forward_3D(165,11);
  CCD_forward(170,25);
}

void B_bridge()
{
  //CCD_backward(70,9);
  GM_backward_3D(55,29);
  speedr=127;
  speedl=127;
  delay(600);
  CCD_backward(85,9);
  GM_backward(55,23);
}

void F_cycle_sp(int s,int t,int c)
{
  speedr=127;
  speedl=127;
  delay(1000);
  speedr=127+127;
	speedl=127-95;
	delay(s);
	speedr=127+115;
	speedl=127-100;
	delay(t);
	speedr=127+60;
	speedl=127-100;
	delay(c);
	speedr=127;
	speedl=127;
	delay(300);
}

void changqiao(int n,int m)
{
  while(1)
  {
  if((HW1==1)&&(HW4==0))
	{
	  speedr=n+13;
	  speedl=n-13;
	}
	/*else if(HW2==0)
	{
	  speedr=n-27;
	  speedl=n+27;
	}*/
	else if((HW4==1)&&(HW1==0))
	{
	  speedr=n-13;
	  speedl=n+13;
	}
	/*else if(HW3==0)
	{
	  speedr=n+27;
	  speedl=n-27;
	}*/
	else
	{
	  speedr=n;
	  speedl=n;
	}
	  if(JJ4==m)
	  {
	    delay(13);
		if(JJ4==m)
		  break;
	  }
	}
}

void changqiao_sp(int n,int m)
{
  while(1)
  {
  if((HW1==1)&&(HW4==0))
	{
	  speedr=n+13;
	  speedl=n-13;
	}
	/*else if(HW2==0)
	{
	  speedr=n-27;
	  speedl=n+27;
	}*/
	else if((HW4==1)&&(HW1==0))
	{
	  speedr=n-13;
	  speedl=n+13;
	}
	/*else if(HW3==0)
	{
	  speedr=n+27;
	  speedl=n-27;
	}*/
	else
	{
	  speedr=n;
	  speedl=n;
	}
	  if(JJ2==m)
	  {
	    delay(10);
		if(JJ2==m)
		  break;
	  }
	}
}

void F_cycle(int s,int t,int c)
{
    speedr=127+125;
	speedl=127-95;
	delay(s);      ///395
	speedr=127+115;
	speedl=127-100;
	delay(t);      ///95
	speedr=127+60;
	speedl=127-110;
	delay(c);      ///60
	speedr=127;
	speedl=127;
	delay(100);
}





/////////////////////////////////////////////////////////////////SLOW
void B_turn_F_L_SLOW()//OK  三教改
{
  //CCD_backward(65,3);
  FORWARD;
  delay(5);
  speedr=127-60;//20
  speedl=127+70;
  while(R1==0);
  speedr=127-85;//90
  speedl=127+100;//128
  while(L4==0);
  speedr=127-50;//10
  speedl=127+50;//25
  while(L1==0);
  speedr=127;
  speedl=127;
  delay(100);
}

void B_turn_F_R_SLOW()//OK
{
  //CCD_backward(65,4);
  FORWARD;
  delay(5);
  speedr=127+100;
  speedl=127-55;
  while(L4==0);
  speedr=127+105;
  speedl=127-85;
  while(R1==0);//前巡线板右边的灯也反了
  speedr=127+50;
  speedl=127-60;
  while(R4==0);
  speedr=127;
  speedl=127;
  delay(100);
}

void F_turn_B_R_SLOW()//OK  shun
{
 // CCD_forward(195,3);
  BACKWARD;
  delay(5);
  speedl=127-60;////110
  speedr=127+60;
  while(R1==0);
  speedl=127-80;/////110
  speedr=127+90;
  while(L4==0);
  speedl=127-40;
  speedl=127+60;
  while(L1==0);
  speedr=127;
  speedl=127;
  delay(100);
 
}

void F_turn_B_L_SLOW()//
{
  //CCD_forward(195,4);
  BACKWARD;
  delay(5);
  speedl=127+50;//60
  speedr=127-90;//127
  while(L4==0);
  speedl=127+75;//95
  speedr=127-105;//127
  while(R1==0);
  speedl=127+50;

  speedr=127-60;
  while(R4==0);
  
  speedr=127;
  speedl=127;
  delay(100);
}





