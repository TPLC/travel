#include<c8051f310.h>
#include<stdio.h>
sbit LED1=P0^0;
int a=0;
void clock(void)
{
  OSCICL=0X2D;
  OSCICN=0XC2;
  CLKSEL=0X00;
}

void pio(void)
{
 XBR0=0X00;
 XBR1=0X00;
 P0MDIN=0XFF;
 P0MDOUT=0X00;
 P0SKIP=0X00;
}

void intt(void)
{
  IE|=0X81;
  INT01CF=0X04;
  IP=0X01;
}

void delay(unsigned int m )
{
  unsigned int i,j;
  for(i=0;i<255;i++)
  for(j=0;j<m;j++)
  {; ;}
}
main()
{
  PCA0MD &=~0X40;
  clock();
  pio();
  intt();
  while(1)
  {
   a=0;
   LED1=1;
   if(a==1)
   {
   LED1=0;
   delay(500);
   }
    }
}

void hhhh(void) interrrupt 0
{

 a=1;
}#include<stdio.h>sbit LED1=P0^0;int a=0;void clock(void){  OSCICL=0X2D;  OSCICN=0XC2;  CLKSEL=0X00;}void pio(void){ XBR0=0X00; XBR1=0X00; P0MDIN=0XFF; P0MDOUT=0X00; P0SKIP=0X00;}void intt(void){  IE|=0X81;  INT01CF=0X04;  IP=0X01;}void delay(unsigned int m ){  unsigned int i,j;  for(i=0;i<255;i++)  for(j=0;j<m;j++)  {; ;}}main(){  PCA0MD &=~0X40;  clock();  pio();  intt();  while(1)  {   a=0;   LED1=1;   if(a==1)   {   LED1=0;   delay(500);   }    }}void hhhh(void) interrrupt 0{ a=1;}#include<stdio.h>sbit LED1=P0^0;int a=0;void clock(void){  OSCICL=0X2D;  OSCICN=0XC2;  CLKSEL=0X00;}void pio(void){ XBR0=0X00; XBR1=0X00; P0MDIN=0XFF; P0MDOUT=0X00; P0SKIP=0X00;}void intt(void){  IE|=0X81;  INT01CF=0X04;  IP=0X01;}void delay(unsigned int m ){  unsigned int i,j;  for(i=0;i<255;i++)  for(j=0;j<m;j++)  {; ;}}main(){  PCA0MD &=~0X40;  clock();  pio();  intt();  while(1)  {   a=0;   LED1=1;   if(a==1)   {   LED1=0;   delay(500);   }    }}void hhhh(void) interrrupt 0{ a=1;}#include<stdio.h>sbit LED1=P0^0;int a=0;void clock(void){  OSCICL=0X2D;  OSCICN=0XC2;  CLKSEL=0X00;}void pio(void){ XBR0=0X00; XBR1=0X00; P0MDIN=0XFF; P0MDOUT=0X00; P0SKIP=0X00;}void intt(void){  IE|=0X81;  INT01CF=0X04;  IP=0X01;}void delay(unsigned int m ){  unsigned int i,j;  for(i=0;i<255;i++)  for(j=0;j<m;j++)  {; ;}}main(){  PCA0MD &=~0X40;  clock();  pio();  intt();  while(1)  {   a=0;   LED1=1;   if(a==1)   {   LED1=0;   delay(500);   }    }}void hhhh(void) interrrupt 0{ a=1;}