#include <C8051F340.h>         
#include <stdio.h>             // Standard I/O definition file
#include <math.h>              // Math library file

#define SYSCLK            24000000
//#define Integrationtime   20                           //����ʱ��,��λ����
#define DOTCLK            (129000/(Integrationtime))   //����Ƶ��
#define Threshold_value   90                          //��ֵ
#define  UartBaudRate     115200
#define uint unsigned int
unsigned int i,j,k;
unsigned int CLKFLAG=0;
bit SIFLAG=0;
bit aftercj=0;
unsigned char light=25;                         //��������
unsigned char Integrationtime;               //����ʱ��,��λ����

xdata unsigned char Image_Data[129];    //ͼ�����飬���һ����������
xdata unsigned char Binary_Data[128];    //��ֵ����ͼ������
sfr16 TMR2R=0XCA;                               //T2����ֵ�Ĵ���

sbit SINPUT=P2^4;
sbit CLK=P2^7;
bit CCDDIR=1;                             //CCD ���� 1Ϊǰ

void sysclk(void)
{
int i = 0;
    FLSCL     = 0x90;
    CLKMUL    = 0x00;
    CLKMUL    = 0x80;
    for (i = 0; i < 20; i++);    // Wait 5us for initialization
    CLKMUL    |= 0xC0;
    while ((CLKMUL & 0x20) == 0);
    CLKSEL    = 0x02;           //4/2��
    OSCICN    = 0x83;           //����Ƶ
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

XBR0=0X01;      //TX0��P04��RX0��P05 /SYSCLK
XBR1=0X42;      //

}

void timer1(void)  //����������
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
CKCON|=0X30;               //T2 ʹ��ϵͳʱ��
TMR2CN=0X04;               //16λ���� TR2=1
TMR2R=-(SYSCLK/DOTCLK);    //��ʱ�жϲ���CCD��ʱ���ź�CLK����������SI
}

void AD(void)
{
AMX0P=0X00;  //P20+
AMX0N=0X1F;  //GND-
REF0CN=0X08; //VREF\VDD
ADC0CF=0X1C; //3M SAR �����
ADC0CN=0X80; //ADʹ��
}

void INTT(void)
{
EA=1;ET2=1;
}

void light_gain(void)
{
//AMX0P=0X04;                //�й�Ԫ��ģ��ͨ��P21
AD0BUSY=1;                 //����AD����ȡ��������
while(AD0INT==0);AD0INT=0;          //�ȴ�AD����
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

void TIMER2INT(void) interrupt 5  //T2�жϲ���CLK��SI,���������ݸ�PC��λ��
{
TF2H=0;   //���ж�
CLK=1;
delay_us(2);
SINPUT=0;
delay_us(2);
if(SIFLAG)       //��һ�ε�������Ч
{
AD0BUSY=1;                 //����AD
while(AD0INT==0);AD0INT=0;          //�ȴ�AD����
Image_Data[CLKFLAG]=ADC0H;    //ͼ������
if(Image_Data[CLKFLAG]==0xFF) Image_Data[CLKFLAG]=0xFE;       //����ͼ��ͷ���Լ�1
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
TMR2R=-(SYSCLK/DOTCLK);    //��ʱ�жϲ���CCD��ʱ���ź�CLK����������SI
CLKFLAG=0;
SINPUT=1;
SIFLAG=1;
SBUF0=0XFF;
while (!(TI0));TI0=0; 
}
}
 