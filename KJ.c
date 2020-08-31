#include <C8051F340.h>                 // SFR declarations
#include <stdio.h>
#define SYSCLK       48000000          // SYSCLK frequency in Hz
#define BAUDRATE1     115200           // Baud rate of UART1 in bps
sfr16 SBRL1 = 0xB4;
sbit key1=P2^0;
sbit LED1=P2^2;

unsigned int Read_stm;

void SYSTEMCLOCK_Init();
void PORT_Init();                       // initialize crossbar and GPIO
void UART1_Init();  
void Delay();
void delay(unsigned int);

void main (void) {


   PCA0MD &= ~0x40;                    // Disable Watchdog timer

   SYSTEMCLOCK_Init();                // initialize oscillator
   PORT_Init();                       // initialize crossbar and GPIO
   UART1_Init();                      // initialize UART1
   key1=1;
   //EA=1;
   while(1)
   {
     //if(key1==0)
     //{
	  //EA=0;
      while (!(SCON1 & 0x02));         // wait until UART1 is ready to transmit
      SCON1 &= ~0x02;                  // clear TI1 interrupt flag
      SBUF1 = 0X00;              // output <c> using UART 1
      delay(50);
	  //EA=1;
	  //}
	  /*if(Read_stm==1)
	  {
	    while(1)
	    {
	      LED1=0;
	      delay(200);
	      LED1=1;
	    }
	  }*/
   }
}


void SYSTEMCLOCK_Init (void)
{
   OSCICN |= 0x03;                     // Configure internal oscillator for
                                       // its maximum frequency and enable
                                       // missing clock detector

   CLKMUL  = 0x00;                     // Select internal oscillator as
                                       // input to clock multiplier

   CLKMUL |= 0x80;                     // Enable clock multiplier
   Delay();                            // Delay for clock multiplier to begin
   CLKMUL |= 0xC0;                     // Initialize the clock multiplier
   Delay();                            // Delay for clock multiplier to begin

   while(!(CLKMUL & 0x20));            // Wait for multiplier to lock
   CLKSEL  = 0x03;                     // Select system clock
}


void PORT_Init (void)
{  

   XBR2 = 0x01;                        // route UART 1 to crossbar
   XBR1 = 0x40;                        // enable crossbar
   P0MDOUT |= 0x11;                    // set P0.4 to push-pull output
   P2MDOUT  =0X04;

}

void UART1_Init (void)
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
   EIE2=0X02;
}

void Delay(void)
{
   int x;
   for(x = 0;x < 500;x)
      x++;
}

void UART1_interrupt(void)interrupt 16
{
  if(SCON1&0x01)
  {
    SCON1 &= ~0x01;
    Read_stm=SBUF1;
  }
}
 
void delay(unsigned int x)
{
unsigned int ii,jj;

for(ii=0;ii<1000;ii++)
   for(jj=0;jj<x;jj++)
{;;}
}