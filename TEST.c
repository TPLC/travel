#include<c8051f340.h>
#include <stdio.h> 
#include <math.h>
#include<stdlib.h>

sbit led=P2^3;
unsigned int a=0;

void SYSCLK_Init (void)
{
   OSCICN |= 0x03;                     // Configure internal oscillator for
                                       // its maximum frequency
   RSTSRC  = 0x04;                     // Enable missing clock detector
}

void PORT_Init (void)
{
   P0MDOUT |= 0x10;                    // Enable UTX as push-pull output
   XBR0     = 0x01;                                       
   XBR1     = 0x40;                    // Enable crossbar and weak pull-ups
   P2MDIN=0XFF;
   P2MDOUT=0XFF;
}

void main()
{
  char date[20];
  PCA0MD &= ~0x40;
  SYSCLK_Init();
  PORT_Init();
  led=0;
  free(date);
  while(1)
  {
    led=1;
  }
    
}
