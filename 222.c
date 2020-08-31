#include<C8051F340.h>
#include <stdio.h>

#define SYSCLK            24000000
#define  UartBaudRate     115200		//设置波特率


void delay(unsigned int);
void timer1(void);
void UART0(void);
void sysclk(void);

void delay(unsigned int x)
{
unsigned int ii,jj;

for(ii=0;ii<1000;ii++)
   for(jj=0;jj<x;jj++)
{;;}
}


void timer1(void)  //发生波特率
{
    if (SYSCLK/UartBaudRate/2/256 < 1) {
      TH1 = -(SYSCLK/UartBaudRate/2);
      CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
      CKCON |=  0x08;
   } else if (SYSCLK/UartBaudRate/2/256 < 4) {
      TH1 = -(SYSCLK/UartBaudRate/2/4);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01                 
      CKCON |=  0x09;
   } else if (SYSCLK/UartBaudRate/2/256 < 12) {
      TH1 = -(SYSCLK/UartBaudRate/2/12);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 00
   } else {
      TH1 = -(SYSCLK/UartBaudRate/2/48);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
      CKCON |=  0x02;
   }

   TL1 = TH1;                          // init Timer1
   TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;                       
   TR1 = 1;                            // START Timer1
   IP |= 0x10;                         // Make UART high priority
          
                            
}

void UART0(void)
{
SCON0=0X10;
}  

void pio(void)
{
P0MDOUT=0X1F;       //1011 1111

XBR0=0X01;      ////TX0：P04、RX0：P05		
XBR1=0XD5;      //CEX0\CEX1      T0-P07
}


void sysclk(void)
{
  int i = 0;
    FLSCL     = 0x90;
    CLKMUL    = 0x00;
    CLKMUL    = 0x80;
    for (i = 0; i < 20; i++);    // Wait 5us for initialization
    CLKMUL    |= 0xC0;
    while ((CLKMUL & 0x20) == 0);
    CLKSEL    = 0x02;           //4/2倍
    OSCICN    = 0x83;           //不分频
}

void main()
{
  PCA0MD &= ~0x40;
  sysclk();
  pio();
  	UART0();
	timer1();
	while(1)
   {
      // If the complete word has been entered via the terminal followed by
      // carriage return
      //if(TX_Ready == 1)
     // {
         //TX_Ready = 0;                 // Set the flag to zero
         //TI0 = 1;
		//  EA=0;
		                       // Set transmit flag to 1
		 SBUF0='1';
		 while(!TI0);
		 TI0=0;
		 delay(1000);
		// EA=1;
		 //delay(100);
     // }
  }
}