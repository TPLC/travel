#include <C8051F340.h>         
#include <stdio.h>             // Standard I/O definition file
#include <math.h>              // Math library file

#define SYSCLK            24000000
//#define Integrationtime   20                           //积分时间,单位毫秒
#define DOTCLK            (129000/(Integrationtime))   //像素频率
#define Threshold_value   90                          //阀值
#define  UartBaudRate     115200
#define uint unsigned int
unsigned int i,j,k;
unsigned int CLKFLAG=0;
bit SIFLAG=0;
bit aftercj=0;
unsigned char light=25;                         //环境亮度
unsigned char Integrationtime;               //积分时间,单位毫秒

xdata unsigned char Image_Data[129];    //图像数组，最后一个数据舍弃
xdata unsigned char Binary_Data[128];    //二值化后图像数组
sfr16 TMR2R=0XCA;                               //T2重载值寄存器

sbit SINPUT=P2^4;
sbit CLK=P2^7;
bit CCDDIR=1;                             //CCD 方向 1为前

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
P0MDIN=0XFF;
P0MDOUT=0XFF;   
P0SKIP=0X00;        //P04\P05\P06

P1MDIN=0XFF;        
P1MDOUT=0X00;   
P1SKIP=0XFF;

P2MDIN=0X90;       
P2MDOUT=0X90;   
P2SKIP=0XFF;

P3MDIN=0XFF;
P3MDOUT=0X00;   
P3SKIP=0XFF;

XBR0=0X01;      //TX0：P04、RX0：P05 /SYSCLK
XBR1=0X42;      //

}

void timer1(void)  //发生波特率
{
#if ((SYSCLK/UartBaudRate/2) < 255)
   #define SCALE1 1
      CKCON |= 0x08;                 
#elif ((SYSCLK/UartBaudRate/4/2) < 255)
   #define SCALE1 4
      CKCON |= 0x01;
      CKCON &= ~0x0A;                
#endif
   TMOD |= 0x20;       
   TH1 = -(SYSCLK/UartBaudRate/SCALE1/2);
   TL1 = TH1;                        
   TR1 = 1;                          
}

void timer2(void)
{
CKCON|=0X30;               //T2 使用系统时钟
TMR2CN=0X04;               //16位重载 TR2=1
TMR2R=-(SYSCLK/DOTCLK);    //定时中断产生CCD的时钟信号CLK及串行输入SI
}

void AD(void)
{
AMX0P=0X00;  //P20+
AMX0N=0X1F;  //GND-
REF0CN=0X08; //VREF\VDD
ADC0CF=0X1C; //3M SAR 左对齐
ADC0CN=0X80; //AD使能
}

void INTT(void)
{
EA=1;ET2=1;
}

void light_gain(void)
{
//AMX0P=0X04;                //感光元件模拟通道P21
AD0BUSY=1;                 //启动AD，获取环境亮度
while(AD0INT==0);AD0INT=0;          //等待AD结束
light=(ADC0H+light)/2;
Integrationtime=30-light/2;
}
void UART0(void)
{
SCON0|=0X10;
}

void delay_us(unsigned int time)
 {     
   while (time--);
 }		  
void delay_ms(unsigned int time)
 {
   while(time--) delay_us(100);  		 
 }

void main(void)//////////////////////////////////////////////////////////////////////MAIN
{
PCA0MD &= ~0x40; 
sysclk();
pio();
AD();
light_gain();
AMX0P=0X00;  //P20+

timer1();
UART0();
SINPUT=0;
CLK=0;
SINPUT=1;
timer2();
INTT();
CCDDIR=0;
while(1);
}

void TIMER2INT(void) interrupt 5  //T2中断产生CLK和SI,并发送数据给PC上位机
{
TF2H=0;   //清中断
CLK=1;
delay_us(2);
SINPUT=0;
delay_us(2);
if(SIFLAG)       //第一次的数据无效
{
AD0BUSY=1;                 //启动AD
while(AD0INT==0);AD0INT=0;          //等待AD结束
Image_Data[CLKFLAG]=ADC0H;    //图像数组
if(Image_Data[CLKFLAG]==0xFF) Image_Data[CLKFLAG]=0xFE;       //遇到图像头，自减1
SBUF0=Image_Data[CLKFLAG];
while (!(TI0));TI0=0;
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
SBUF0=0XFF;
while (!(TI0));TI0=0; 
}
}
 