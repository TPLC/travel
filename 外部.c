#include<C8051F340.h>

sbit led1 = P2^2;
sbit led2 = P2^3;
sbit test_pin = P0^0;

void Osc_Init()
{
  OSCICN    = 0x83;
}

void Port_Init()
{
  P0MDOUT = 0X00;
  P2MDOUT = 0X0C;
  XBR1    = 0X40;
}

void Timer0_Init()
{ 
  TL0  = 0X38;
  TH0  = 0X38;
  TMOD = 0X02;
  TR0  = 1;
} 

void Ext_Isr_Init()
{

  TCON |= 0x05; 
  IT01CF = 0X10;
}

void Init_Device()
{
  Osc_Init();
  Port_Init();
  Timer0_Init();
  Ext_Isr_Init();
}

void INTT()
{
  ET0 = 1;
  EX0 = 1;
  
  EA  = 1;
}

void delay(unsigned int x)
{
unsigned int ii,jj;

for(ii=0;ii<1000;ii++)
   for(jj=0;jj<x;jj++)
{;;}
}

void main()
{
  PCA0MD &= ~0x40;
  Init_Device();
  INTT();
  while(1)
  { 
    if(test_pin==0)
	{
	  delay(3);
	  if(test_pin==0)
	  {
	    led1 = ~led1; 
	  }
	}
  
  }
}

void Ext_ISR() interrupt 0
{
  led2 = ~led2;
}

void Timer0_ISR() interrupt 1
{
  static unsigned int counter = 0;
  if(counter++ == 5000)////10000 2s
  {
    led1 = ~led1;
	counter = 0;
  }
}



