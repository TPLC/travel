#include<c8051f340.h>

sbit led1 = P2^2; 
sbit DB1  = P0^1;
sbit DB2  = P0^2;
sbit D1   = P0^2;
sbit D2   = P0^3;
sbit D3   = P0^4;
sbit D4   = P0^5;

unsigned char flag = 0;
unsigned time_flag = 0;

void Osc_Init()
{
  OSCICN    = 0x83;
}

void Port_Init()
{
  P0MDOUT = 0X03;
  P2MDOUT = 0X0C;
  XBR1    = 0X42;
}

void Timer0_Init()
{ 
  TL0  = 0X38;
  TH0  = 0X38;
  TMOD = 0X02;
  TR0  = 1;
} 

void PCA0_Init()
{
  
}

void Init_Device()
{
  Osc_Init();
  Port_Init();
  Timer0_Init();
}

void delay(unsigned int x)
{
unsigned int ii,jj;

for(ii=0;ii<1000;ii++)
   for(jj=0;jj<x;jj++)
{;;}
}

void stop()
{
  ;////////////////////小车停止
}

void anchor()//////////小车抛锚对应事件
{
  ;////////////////////舵机控制将挡板打下
  stop();//////////////小车停止
}

void main()
{
  PCA0MD &= ~0x40;
  Init_Device();
  EA  = 1;
  ET0 = 1;
  led1=0;
  while(1)
  { 
    while(1)
	{
      if(D1 == 0)
	  {
	    delay(5);
	    if(D1 == 0)
	    {
	       flag = 1;   
	    }
      }
	  if(time_flag == 1)
	  {
	    time_flag = 0; 
	    flag = 0;
	    break;
	  }
    }
	
    while(D2);////////////检测是否过第一个门
    
	TR0 = 1;//////////////继续第二个抛锚检测
	while(1)
	{
      if(D3 == 0)
	  {
	    delay(5);
	    if(D3 == 0)
	    {
	       flag = 1;   
	    }
      }
	  if(time_flag == 1)
	  {
	    time_flag = 0;
	    flag = 0;
	    break;
	  }
    }
    
    while(D3);//////////检测是否过第二个门
    
    stop();/////////////通过所有门，一切正常，终点小车停止 
  }
}

void Timer0_ISR() interrupt 1
{
  static unsigned int counter = 0;
  if(counter++ == 10000)////10000 2s
  {
    time_flag = 1;//////////时间标志，说明过了2s
    if(flag == 1)///////////2s内通过
	{
	  anchor();/////////////说明抛锚，将挡板打下，小车停止
 	}
	counter = 0;
	TR0 = 0;
  }
}