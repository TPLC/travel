/*****************************/
/****************************/

#ifndef _System_Init_h_
#define _System_Init_h_

#include <c8051f340.h>

#define uint unsigned int
#define uchar unsigned char


#define SYSCLK            24000000
#define  UartBaudRate     115200		//设置波特率
#define DOTCLK     (129000/(Integrationtime))   //像素频率

#define BAUDRATE1     9600   

#define speedl PCA0CPH0
#define speedr PCA0CPH1 
//P4
#define BELLON     P4&=0X7F  
#define BELLOFF    P4|=0X80  
#define FORWARD    P4&=0XFE
#define BACKWARD   P4|=0X01
#define DENG0ON     P4|=0X40
#define DENG0OFF    P4&=0XBF  
#define DENG1ON     P4|=0X20
#define DENG1OFF    P4&=0XDF 
#define HW1   (!(!(P4&0x08)))
#define HW2   (!(!(P4&0x10)))
#define HW3   (!(!(P4&0x20)))
#define HW4   (!(!(P4&0x40)))
#define D1 PCA0CPH2
#define D2 PCA0CPH3
#define D3 PCA0CPH4

sfr16 TMR2R=0XCA;                       //T2重载值寄存器TH2
sfr16 SBRL1 = 0xB4;

//P1 
sbit LL=P1^5;
sbit RR=P1^1;

sbit JJ1=P2^4;
sbit JJ2=P1^4;//后
sbit JJ3=P1^0;//右斜
sbit JJ4=P1^2;//前
sbit JJ5=P1^7;//左斜
//sbit JG1=P0^6
sbit JG2=P1^6;
sbit SINPUT=P2^4;                       //SI
sbit CLK=P2^7;                          //CLK

sbit DENG0=P1^3;//后
sbit DENG1=P1^6;//前
/*sbit HW1=P2^6;
sbit HW2=P2^2;
sbit HW3=P0^7;
sbit HW4=P0^6;*/


void sysclk(void);
void pio(void);
void timer2(void);
void AD(void);
void INTT(void);
void PCA0(void);
void timer1(void);  //发生波特率
void UART0(void);
void delay(uint x);
void Sent_byte(uchar);
void Timer0_Init(void);
void UART1(void);
void  Send_byte(uchar);
void timer0(void);

#endif