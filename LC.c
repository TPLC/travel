#include<c8051f340.h>
#include<stdio.h>

void sysclk(void)
{
  int i = 0;
    FLSCL     = 0x90;
    CLKMUL    = 0x00;
    CLKMUL    = 0x80;
    for (i = 0; i < 20; i++);    // Wait 5us for initialization
    CLKMUL    |= 0xC0;
    while ((CLKMUL & 0x20) == 0);
    CLKSEL    = 0x02;           //4/2±¶
    OSCICN    = 0x83;           //²»·ÖÆµ
}

void pio(void)
{
P0MDIN=0XFF;		//0111 1111
P0MDOUT=0XFF;       //1011 1111
P0SKIP=0X00;        //P04\P05  \\PWM P00\P01   \\P07 - T0  0100 1100

P1MDIN=0XFF;        
P1MDOUT=0XFF; //////////////////////////////////////////////////////////////////  
P1SKIP=0XFF;

P2MDIN=0XD4;       //  10110010
P2MDOUT=0XF4;      //  1011 0010
P2SKIP=0XFF;

P3MDIN=0XFF;
P3MDOUT=0X00;   
P3SKIP=0XFF;

P4MDIN=0XFF;
P4MDOUT=0XF1;   //1000 0101


XBR0=0X01;      ////TX0£ºP04¡¢RX0£ºP05		
XBR1=0XD5;      //CEX0\CEX1      T0-P07

}

void main()
{
  
}