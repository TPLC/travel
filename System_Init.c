/**
  ******************************************************************************
 
   系统初始化函数
 
  ******************************************************************************
*/

#include"All_Include.h"
int i,j,k=64;
int l,r,m,c,b;
extern bit flag;

unsigned int t=0;



bit JUMP=0;                             //跳出标志位
int JUMPCHOOSE;                         //跳出选择变量

extern unsigned char Integrationtime;       //积分时间,单位毫秒

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

void pio(void)
{
P0MDIN=0XFF;		//1101 1111
P0MDOUT=0X5F;       //0101 1111  P04;1 P05;0 P06;1P07;0 
P0SKIP=0X80;        //P04\P05  \\PWM P00\P01   \\P07 - T0  0100 1100

P1MDIN=0XFF;        
P1MDOUT=0XFF; //////////////////////////////////////////////////////////////////  
P1SKIP=0XFF;

P2MDIN=0XD4;       //  10110010
P2MDOUT=0XB4;      //  1011 0100
P2SKIP=0XBB;     //P22 P26 

P3MDIN=0XFF;
P3MDOUT=0X00;   
P3SKIP=0XFF;

P4MDIN=0XFF;
P4MDOUT=0X81;   //1000 0101


XBR0=0X01;      ////TX0：P04、RX0：P05		
XBR1=0XC5;      //CEX0\CEX1      T0-P07
XBR2=0X01;

}


void AD(void)
{
//AMX0P=0X00;  //P20+
AMX0N=0X1F;  //GND-
REF0CN=0X08; //VREF\VDD
ADC0CF=0X1C; //3M SAR 左对齐
ADC0CN=0X80; //AD使能
}


void PCA0(void)
{
PCA0MD&=~0X40;
PCA0CN=0X40;
PCA0MD=0X02;      // SYSCLK/4

PCA0CPM0=0X42;    ///PWM0;
PCA0CPL0=127;
PCA0CPH0=127;

PCA0CPM1=0X42;    ///PWM1;
PCA0CPL1=127;
PCA0CPH1=127;

PCA0CPM2=0xC2;    ///PWM2; //0X02为 8 位PWM输出
PCA0CPL2=245;     //0XC2为 16 位PWM输出
PCA0CPH2=211;

PCA0CPM3=0XC2;   ///PWM3;
PCA0CPL3=245;
PCA0CPH3=190;

PCA0CPM4=0XC2;   ///PWM4;
PCA0CPL4=245; 
PCA0CPH4=200;
}


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
}

void UART0(void)
{
SCON0|=0X10;
}



void timer2(void)
{
CKCON|=0X30;               //T2 使用系统时钟
TMR2CN=0X04;               //16位重载 TR2=1
TMR2R=-(SYSCLK/DOTCLK);    //定时中断产生CCD的时钟信号CLK及串行输入SI
}

void timer0(void)  //防止抛锚定时器
{
TMOD|=0x01;               
TH0=(65536-60000)/256;
TL0=(65536-60000)%256;	 
//TR0=1;
  //ET0=1;        
}
void INTT()
{
EA=1;ET2=1;ET0=1;//PT0=1;
}

	void UART1 (void)
{
   SMOD1 = 0x0C;                       // set to disable parity, 8-data bit,
                                       // disable extra bit, 
                                       // stop bit 1 bit wide

   SCON1 = 0x10;                       // SCON1: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits

   if (SYSCLK/BAUDRATE1/2/0xFFFF < 1) {
      SBRL1 = -(SYSCLK/BAUDRATE1/2);
      SBCON1 |= 0x03;                  // set prescaler to 1
   } else if (SYSCLK/BAUDRATE1/2/0xFFFF < 4) {
      SBRL1 = -(SYSCLK/BAUDRATE1/2/4);
      SBCON1 &= ~0x03;
      SBCON1 |= 0x01;                  // set prescaler to 4

   } else if (SYSCLK/BAUDRATE1/2/0xFFFF < 12) {
      SBRL1 = -(SYSCLK/BAUDRATE1/2/12);
      SBCON1 &= ~0x03;                 // set prescaler to 12
   } else {
      SBRL1 = -(SYSCLK/BAUDRATE1/2/48);
      SBCON1 &= ~0x03;
      SBCON1 |= 0x02;                  // set prescaler to 4
   }

   SCON1 |= 0x02;                      // indicate ready for TX
   SBCON1 |= 0x40;                     // enable baud rate generator
   
   //EIE2=0X02;////////////开启串口1中断后会很卡
}

void  Send_byte(uchar send_data)
{
    SBUF1=send_data;  
 while (!(SCON1 & 0x02));      // wait until UART1 is ready to transmit
         SCON1 &= ~0x02;    
}