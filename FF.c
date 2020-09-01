
#include<c8051f310.h>
unsigned int i,j,m;
void sys(void)　//设置系统时钟
{
CLKSEL=0X00;
OSCICL=0X2D;
OSCICN=0XC2;
}

void pio(void)  //设置I/0端口
{
XBR0=0X00;XBR1=0X40;
P0MDIN=0XFF;P0MDOUT=0X00;P0SKIP=0XFF;
P1MDIN=0XFF;P1MDOUT=0X00;P1SKIP=0XFF;
}

void delay(m)  //延时程序
{
for(i=0;i<10;i++)
for(j=0;j<m;j++)
{;;}
}

main()
{
PCA0MD&=～0X4D;
sys();
pio();
while(1)
{
P0=0XC0;P1=0XFE;delay(100);//P0=1100 0000;P1=1111 1110
P0=0XF9;P1=0XFD;delay(100);//P0=1111 1001;P1=1111 1101
P0=0XA4;P1=0XFB;delay(100);//P0=1010 0100;P1=1111 1011
P0=0XB0;P1=0XF7;delay(100);//P0=1011 0000;P1=1111 0111
P0=0X99;P1=0XEF;delay(100);//P0=1001 1001;P1=1110 1111
P0=0X92;P1=0XDF;delay(100);//P0=1001 0010;P1=1101 1111
}//自左往右显示的数为543210
}
