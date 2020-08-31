/**
  ******************************************************************************
  * @file    CCD_code.c
  * @author  MRT.LEE
  * @version V0.1
  * @date    2015-5-12
  * @brief   CCDѲ�ߺ�������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨��c8051f340-IDE
  *
  * �ص㣺������ʵ����
  *
  ******************************************************************************
*/

#include"All_Include.h"


bit CCDDIR;                             //CCD ���� 1Ϊǰ

bit SIFLAG;                           //�ǵ�һ�����ݱ�־
bit aftercj;                          //�ɼ����־
bit cjflag;                           //

unsigned char Threshold_value;          //��ֵ
unsigned char Integrationtime;       //����ʱ��,��λ����
xdata unsigned char Image_Data[129];    //ͼ�����飬���һ����������

unsigned char Data_average_value;       //����ƽ��ֵ
unsigned char light=30;                 //��������

unsigned int CLKFLAG;                 //���ؼ���

extern int m;
extern int k;
extern int i;
extern int j;
extern int r;
extern int l;
extern unsigned int t;
extern bit JUMP;                             //������־λ
extern int JUMPCHOOSE;                         //����ѡ�����


extern unsigned char BUF[8];
extern unsigned char cnt,countnumber;
extern unsigned int NNN,LLL;


void light_gain(void)           
{
int i,sum=0;
//AMX0P=0X01;                //�й�Ԫ��ģ��ͨ��P21
AD0BUSY=1;                 //����AD����ȡ��������
while(AD0INT==0);AD0INT=0;         //�ȴ�AD����
light=(ADC0H+light)/2;
Integrationtime=38-light/4;        //�ع�ʱ��
if(Integrationtime>15)Integrationtime=14;
if(Integrationtime<5)Integrationtime=3;
for(i=0;i<128;i++)
{sum=Image_Data[i]+sum;}
Data_average_value=sum/128;          //ƽ��ֵ
Threshold_value=2*Data_average_value; //��ֵ
if(Threshold_value>=230) Threshold_value=230;
if(Threshold_value<=30) Threshold_value=30;
//AMX0P=0X00;  //P20+
}
    
void CCD_forward(int n,int JC) 										///////////////////////   CCD   ������Ѳ��
{ 
 m=n;t=0;k=61;
 FORWARD;  delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=1;
 speedr=m;   //you
 speedl=m;
while(1)
{
 if(aftercj==1)
  { 
    for(i=0;i<128;i++)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i+2]>=Threshold_value))  
	     {
		 for(j=128;j>0;j--)
           {
				if((Image_Data[j]>Threshold_value)&&(Image_Data[j-2]>Threshold_value))  
			    {
				 k=(i+j)/2;
				 if(j-i >15)
				   k=61;
				 break;
				 }
		    }
			break;		 
	      }
	 }

	 
	if(m>127)
	{  
	  
	   if((m==199)||(m==174))//////////////////////////��ƫ
		{
		   	l=m+7*(k-55)/5;
			r=m-7*(k-55)/5; 
		}
		if(m>=200)
		{
			l=m+6*(k-61)/5;
			r=m-6*(k-61)/5;
		}
		else if(m==191)//////////////////////////��ƫ
		{
		   	l=m+7*(k-53)/5;
			r=m-7*(k-53)/5; 
		}
		else
		{
			l=m+6*(k-61)/4;
			r=m-6*(k-61)/4;
		}
		if(l>255)l=255;
		if(r>255)r=255;
		 speedl=r;   
		 speedr=l;  
		aftercj=0;
		TR2=1;
		ET2=1;
		t=t+1;
		
	}
	else
	{
		l=m+2*(k-20)/5;//72
		r=m-2*(k-20)/5;//72

		if(r<0)r=0;
		if(l<0)l=0;
		 speedl=l;   
		 speedr=r; 
		aftercj=0;
		TR2=1;
		ET2=1;
	}
   }
  Main_switch(); 
  if(JUMP){JUMP=0;break;}
 }
}                                       



void CCD_backward(int n,int JC)  //////////////////////////////////////////////////
{  
 m=n;t=0;  
 BACKWARD; delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=0;
 speedr=m;   //you
 speedl=m;
 while(1)
 {
 if(aftercj==1)
  {
    for(i=128;i>0;i--)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i-2]>=Threshold_value))  
	     {
		 for(j=0;j<128;j++)
           {
			if((Image_Data[j]>=Threshold_value)&&(Image_Data[j+2]>=Threshold_value))  
		    {k=(i+j)/2;
			 if(i-j>15)
			   k=63;
			 break;}
		    }
			break;		 
	      }
	 }
	if(m<=50)
	{
		l=m+5*(k-63)/4;
		r=m-5*(k-63)/4;
    }
	else if(m<=10)
	{
	    l=m+5*(k-63)/5;
		r=m-5*(k-63)/5;
	}
	else
	{
		l=m+7*(k-63)/4;
		r=m-7*(k-63)/4;
	}
	if(r<0)r=0;
	if(l<0)l=0;
	 speedl=r;   
	 speedr=l; 
	aftercj=0;
	TR2=1;
	ET2=1;
	
	 
	t=t+1;
	
  }

  Main_switch(); 
  if(JUMP){JUMP=0;break;}
 }
}
/*********** CCDƯ�����*******************/
void CCD_forward_Left(int n,int JC) 					/////////////////////// 
{
m=n;t=0;
 FORWARD;  delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=1;
 speedr=m;   //you
 speedl=m;
while(1)
{
 if(aftercj==1)
  { 
    for(i=127;i>=0;i--)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i-2]>=Threshold_value))  
	     {
		    k=(i+55)/2;
			break;
		    /*for(j=i;j>=0;j--)
	           {
				if((Image_Data[j]<Threshold_value)&&(Image_Data[j-2]<Threshold_value))  
			    {k=(i+j)/2;break;}
			    }
				break;	
			*/	 
	      }
	 }
	if(m>=200)
	{
		l=m+(k-92);//58
		r=m-(k-92);
	}
	else
	{
		l=m+5*(k-58)/4;
		r=m-5*(k-58)/4;
	}
	if(l>255)l=255;
	if(r>255)r=255;
	 speedl=r;   
	 speedr=l;   
	aftercj=0;
	TR2=1;
	ET2=1;
	 t=t+Integrationtime;
   } 
   Main_switch(); 
   if(JUMP){JUMP=0;break;}
  }
}

void CCD_forward_L(int n,int JC) 					///////////////////////   CCD 	������Ѳ��
{
m=n;t=0;
 FORWARD;  delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=1;
 speedr=m;   //you
 speedl=m;
while(1)
{
 if(aftercj==1)
  { 
    for(i=127;i>=0;i--)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i-2]>=Threshold_value))  
	     {
		 for(j=i;j>=0;j--)
           {
			if((Image_Data[j]<Threshold_value)&&(Image_Data[j-2]<Threshold_value))  
		    {k=(i+j)/2;break;}
		    }
			break;		 
	      }
	 }
	if(m>=200)
	{
		l=m+6*(k-61)/5;
		r=m-6*(k-61)/5;
	}
	else
	{
		l=m+5*(k-61)/4;
		r=m-5*(k-61)/4;
	}
	if(l>255)l=255;
	if(r>255)r=255;
	 speedl=r;   
	 speedr=l;   
	aftercj=0;
	TR2=1;
	ET2=1;
	 t=t+1;
   } 
   Main_switch(); 
   if(JUMP){JUMP=0;break;}
   }
}
  
void CCD_backward_L(int n,int JC)  //////////////////////////////////////////////////
{
 m=n;t=0; 
 BACKWARD; delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=0;
 speedr=m;   //you
 speedl=m;
 while(1)
 {
 if(aftercj==1)
  {
    for(i=127;i>=0;i--)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i-2]>=Threshold_value))  
	     {
		 for(j=i;j>=0;j--)
           {
			if((Image_Data[j]<Threshold_value)&&(Image_Data[j-2]<Threshold_value))  
		    {k=(i+j)/2;break;}
		    }
			break;		 
	      }
	 }
	
	 if(m<=50)
	{
		l=m+(k-63);//64
		r=m-(k-63);//
	}
	else
	{
		l=m+5*(k-63)/4;//
		r=m-5*(k-63)/4;//
	}
	if(r<0)r=0;
	if(l<0)l=0;
	 speedl=r;   
	 speedr=l;  
	aftercj=0;
	TR2=1;
	ET2=1;
	t=t+Integrationtime;
   }
   Main_switch(); 
   if(JUMP){JUMP=0;break;}
  }
}





void CCD_forward_R(int n,int JC)  								///////////////////////   CCD   ������Ѳ��
{
 m=n;t=0;k=70;
 FORWARD; delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=1;
 speedr=m;   //you
 speedl=m;
while(1)
{
 if(aftercj==1)
  { 
    for(i=0;i<128;i++)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i+2]>=Threshold_value))  
	     {
		 for(j=i;j<128;j++)
           {
			if((Image_Data[j]<Threshold_value)&&(Image_Data[j+2]<Threshold_value))  
		    {k=(i+j)/2;break;}
		    }
			break;		 
	      }
	 }

	l=m+7*(k-61)/4;//70
	r=m-7*(k-61)/4;//

	if(l>255)l=255;
	if(r>255)r=255;
	 speedl=r;   
	 speedr=l;   
	aftercj=0;
	TR2=1;
	ET2=1;
	 t=t+Integrationtime;
   } 
   Main_switch(); 
   if(JUMP){JUMP=0;break;}
  }
}



void CCD_backward_R(int n,int JC)  //////////////////////////////////////////////////
{ 
  m=n;t=0; 
 BACKWARD;  delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=0;
 speedr=m;   //you
 speedl=m;
 while(1)
 {
 if(aftercj==1)
  {
    for(i=0;i<128;i++)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i+2]>=Threshold_value))  
	     {
		 for(j=i;j<128;j++)
           {
			if((Image_Data[j]<Threshold_value)&&(Image_Data[j+2]<Threshold_value))  
		    {k=(i+j)/2;break;}
		    }
			break;		 
	      }
	 }
    if(m<=50)
	 {
	  	l=m+5*(k-63)/4;//
	    r=m-5*(k-63)/4;//64
	 }
	else
	{
	l=m+7*(k-63)/5;//
	r=m-7*(k-63)/5;//64
    }
	if(r<0)r=0;
	if(l<0)l=0;
	 speedl=r;   
	 speedr=l; 
	aftercj=0;
	TR2=1;
	ET2=1;
	 t=t+1;
   }
   Main_switch(); 
   if(JUMP){JUMP=0;break;}
  }
}






void CCD_FOR_BOLANG(int n)  									///////////////////////   CCD   ���˰�Ѳ��
{
 m=n; t=0;
FORWARD;  delay(10);
 CCDDIR=1;
 speedr=m;   //you
 speedl=m;
while(1)
{
 if(aftercj==1)
  {
    for(i=0;i<128;i++)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i+2]>=Threshold_value))  
	     {
		 for(j=i;j<128;j++)
           {
			if((Image_Data[j]<Threshold_value)&&(Image_Data[j+2]<Threshold_value))  
		    {k=(i+j)/2;break;}
		    }
			break;		 
	      }
	  }
if(m>=200)
{
l=m+((k-66)/2);
r=m-((k-66)/2);
}
else if(m==176)///BO LANG
{
l=m+(5*(k-66)/3);
r=m-(5*(k-66)/3);
}
else
{
l=m+(k-66);
r=m-(k-66);
}
if(r>=255) r=255;
if(l>=255) l=255;
 speedl=r;   
 speedr=l;
aftercj=0;
TR2=1;
ET2=1;
t+=Integrationtime;

}
if(LL==0||RR==0)
  {t=0;}

if(t>300)
    {break;}

}
}

void CCD_BACK_BOLANG(int n)  //////////////////////////////////////////////////
{  m=n; t=0;
 BACKWARD;  delay(10);
 CCDDIR=0;
 speedr=m;   //you
 speedl=m;
 while(1)
 {
 if(aftercj==1)
  {
    for(i=0;i<128;i++)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i+2]>=Threshold_value))  
	     {
		 for(j=i;j<128;j++)
           {
			if((Image_Data[j]<Threshold_value)&&(Image_Data[j+2]<Threshold_value))  
		    {k=(i+j)/2;break;}
		    }
			break;		 
	      }
	  }

	  if(m<=40)
{
l=m+((k-60)/2);
r=m-((k-60)/2);
}
else if(m==81)///BO LANG
{
l=m+5*(k-64)/3;
r=m-5*(k-64)/3;
}
else
{
l=m+(k-64);
r=m-(k-64);
}
if(l<=0)l=0;
if(r<=0)r=0;
 speedl=r;   
 speedr=l;


aftercj=0;
TR2=1;
ET2=1;
t+=20;
 }
if(LL==0||RR==0)
  {t=0;}

if(t>300)
    {break;}

}
}

void CCD_forward_B(int n,int JC)
{
 m=n;t=0;k=70;
 BACKWARD;  delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=1;
 speedr=m;   //you
 speedl=m;
while(1)
{
 if(aftercj==1)
  { 
    for(i=0;i<128;i++)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i+2]>=Threshold_value))  
	     {
		 for(j=128;j>0;j--)
           {
				if((Image_Data[j]>Threshold_value)&&(Image_Data[j-2]>Threshold_value))  
			    {
				 k=(i+j)/2;
				 if(j-i >15)
				   k=65;
				 break;
				 }
		    }
			break;		 
	      }
	 }
	 
	if(m>127)
	{
	   
		 if(m>=200)
		{
			l=m+6*(k-61)/5;
			r=m-6*(k-61)/5;
		}
		else
		{
			l=m+6*(k-61)/4;
			r=m-6*(k-61)/4;
		}
		if(l>255)l=255;
		if(r>255)r=255;
		 speedl=r;   
		 speedr=l;  
		aftercj=0;
		TR2=1;
		ET2=1;
		
		 t=t+1;
	}
	else
	{
		l=m+2*(k-52)/5;//72
		r=m-2*(k-52)/5;//72

		if(r<0)r=0;
		if(l<0)l=0;
		 speedl=l;   
		 speedr=r; 
		aftercj=0;
		TR2=1;
		ET2=1;

		 t=t+1;
	}
  } 
  Main_switch(); 
  if(JUMP){JUMP=0;break;}
 }
}

void CCD_backward_F(int n,int JC)
{
  m=n;t=0; 
 FORWARD; delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=0;
 speedr=m;   //you
 speedl=m;
 while(1)
 {
 if(aftercj==1)
  {
    for(i=128;i>0;i--)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i-2]>=Threshold_value))  
	     {
		 for(j=0;j<128;j++)
           {
			if((Image_Data[j]>=Threshold_value)&&(Image_Data[j+2]>=Threshold_value))  
		    {k=(i+j)/2;
			 if(i-j>15)
			   k=63;
			 break;}
		    }
			break;		 
	      }
	 }
	if(m<=50)
	{
		l=m+4*(k-63)/5;
		r=m-4*(k-63)/5;
    }
	else
	{
		l=m+6*(k-63)/4;
		r=m-6*(k-63)/4;
	}
	if(r<0)r=0;
	if(l<0)l=0;
	 speedl=r;   
	 speedr=l; 
	aftercj=0;
	TR2=1;
	ET2=1;
	 
	t=t+1;
	
  }

  Main_switch(); 
  if(JUMP){JUMP=0;break;}
 }
}

void CCD_forward_B_R(int n,int JC)
{
  m=n;t=0;k=70;
 BACKWARD; delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=1;
 speedr=m;   //you
 speedl=m;
while(1)
{
 if(aftercj==1)
  { 
    for(i=0;i<128;i++)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i+2]>=Threshold_value))  
	     {
		 for(j=i;j<128;j++)
           {
			if((Image_Data[j]<Threshold_value)&&(Image_Data[j+2]<Threshold_value))  
		    {k=(i+j)/2;break;}
		    }
			break;		 
	      }
	 }

	l=m+5*(k-63)/4;//70
	r=m-5*(k-63)/4;//

	if(l>255)l=255;
	if(r>255)r=255;
	 speedl=r;   
	 speedr=l;   
	aftercj=0;
	TR2=1;
	ET2=1;
	 t=t+Integrationtime;
   } 
   Main_switch(); 
   if(JUMP){JUMP=0;break;}
  }
}

void CCD_forward_SP(int n,int JC) 										///////////////////////   CCD   ������Ѳ��
{ 
 m=n;t=0;k=55;LLL=0;NNN=0;
 FORWARD;  delay(10);
 JUMPCHOOSE=JC;
 CCDDIR=1;
 speedr=m;   //you
 speedl=m;
while(1)
{
 if(aftercj==1)
  { 
    for(i=0;i<128;i++)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i+2]>=Threshold_value))  
	     {
		 for(j=128;j>0;j--)
           {
				if((Image_Data[j]>Threshold_value)&&(Image_Data[j-2]>Threshold_value))  
			    {
				 k=(i+j)/2;
				 if(j-i >15)
				   k=55;
				 break;
				 }
		    }
			break;		 
	      }
	 }
	 
	if(m>127)
	{
	   
		if(m>=200)
		{
			l=m+6*(k-61)/5;
			r=m-6*(k-61)/5;
		}
		else
		{
			l=m+6*(k-61)/4;
			r=m-6*(k-61)/4;
		}
		if(l>255)l=255;
		if(r>255)r=255;
		 speedl=r;   
		 speedr=l;  
		aftercj=0;
		TR2=1;
		ET2=1;
		t=t+1;
		
	}
	else
	{
		l=m+2*(k-20)/5;//72
		r=m-2*(k-20)/5;//72

		if(r<0)r=0;
		if(l<0)l=0;
		 speedl=l;   
		 speedr=r; 
		aftercj=0;
		TR2=1;
		ET2=1;

	}
  } 
  	//while(1)////////////////////////////////////////OLED�Ķ˿ڻ�δ���� 
	//{		
	cnt=0;                                                    
	   	//SeriPushSend(0X31);
	   Send_byte(0X31);                                       //����1֡��ȡ���
	//SBUF1=0X31;  
	while(1)
	{
	  if(SCON1&0X01)
      {
      SCON1&=~0X01;
      BUF[cnt]=SBUF1;
  	  cnt++;
      }
      if(cnt>=8)/////////////����8��������������������ֵ
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
	//}
  Main_switch(); 
  if(JUMP){JUMP=0;break;}
 }
} 

void CCD_forward_ss() 										///////////////////////   CCD   ������Ѳ��
{ 
t=0;k=61;
 
 CCDDIR=1;
 
delay(50);
while(1)
{
 if(aftercj==1)
  { 
    for(i=0;i<128;i++)
    {  if((Image_Data[i]>=Threshold_value)&&(Image_Data[i+2]>=Threshold_value))  
	     {
		 for(j=128;j>0;j--)
           {
				if((Image_Data[j]>Threshold_value)&&(Image_Data[j-2]>Threshold_value))  
			    {
				 k=(i+j)/2;
				 break;
				 }
		    }
			break;		 
	      }
	 }
	 if(k>61)
	 {
       l=127+40;
	   r=127-40;
	   if(l>255)l=255;
		if(r>255)r=255;
		 speedl=r;   
		 speedr=l;  
		aftercj=0;
		TR2=1;
		ET2=1;
		t=t+1;
	 }
	 else
	 {
	   l=127-35;
	   r=127+55;
	   if(l>255)l=255;
		if(r>255)r=255;
		 speedl=r;   
		 speedr=l;  
		aftercj=0;
		TR2=1;
		ET2=1;
		t=t+1;
	 }
	
   }
  if(t>=3)  
  {
    if(k==61)
	{
	  break;
	}
  }

 }
}                                       



