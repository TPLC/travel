//-----------------------------------------------------------------------------
// F34x_UART0_Interrupt.c
//-----------------------------------------------------------------------------
// Copyright 2006 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program demonstrates how to configure the C8051F340 to write to and read
// from the UART interface. The program reads a word using the UART interrupts
// and outputs that word to the screen, with all characters in uppercase
//
// How To Test:
//
// 1) Ensure that jumpers are placed on J12 of the C8051F340 target board
//    that connect the P0.4 pin to the TX signal, and P0.5 to the RX signal.
// 2) Ensure that the serial cable is connected to the RS232 connector
//    on the target board.
// 3) Specify the target baudrate in the constant <BAUDRATE>.
// 4) Open Hyperterminal, or a similar program, and connect to the target
//    board's serial port.
// 5) Download and execute code on an 'F34x target board.
// 6) Type up to 64 characters into the Terminal and press Enter.  The MCU 
//    will then print back the characters that were typed
//
// Target:         C8051F34x
// Tool chain:     Keil C51 7.50 / Keil EVAL C51
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (SM)
//    -5 JUN 2007
//


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <c8051f340.h>                 // SFR declarations
#include <stdio.h>
#include  <math.h>    //Keil library  
	
#include  <INTRINS.H>
//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define SYSCLK      12000000           // SYSCLK frequency in Hz
#define BAUDRATE        9600           // Baud rate of UART in bps
#define   uchar unsigned char
#define   uint unsigned int	

#define BAUDRATE1     9600           // Baud rate of UART1 in bps

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void SYSCLK_Init (void);
void UART0_Init (void);
void PORT_Init (void);
void Timer2_Init (int);
void delay(unsigned int);
void UART1_Init (void);

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

#define UART_BUFFERSIZE 64
unsigned char UART_Buffer[UART_BUFFERSIZE];
unsigned char UART_Buffer_Size = 0;
unsigned char UART_Input_First = 0;
unsigned char UART_Output_First = 0;
unsigned char TX_Ready =1;
static char Byte;

#define	WriteDeviceAddress   0xE0	  //����������IIC�����еĵ�ַ
#define	ReadDviceAddress     0xE1     //������IIC�����е�ַ+1

typedef unsigned char BYTE;
typedef unsigned short WORD;

BYTE BUF[8];                         //���ݻ�����
BYTE code res[6] _at_ 0x23;

sbit	SCL=P1^0;      //iicʱ�����Ŷ���
sbit	SDA=P1^1;      //iic�������Ŷ���
sfr16 SBRL1 = 0xB4;

uchar templ,temph,cnt;
uchar ge,shi,bai,qian;
uint  dis_data,dis_data1;
   	unsigned char SUM; 

void delay(unsigned int k);
void InitLcd();
void WriteDataLCM(uchar dataW);
void WriteCommandLCM(uchar CMD,uchar Attribc);
void DisplayOneChar(uchar X,uchar Y,uchar DData);
uchar HEX_TO_ASCII(uchar HEX_data);
void conversion(uint temp_data);

//------------------------------------

void Delay5us();
void Delay5ms();
void AT24C04_Start();
void AT24C04_Stop();
void AT24C04_SendACK(bit ack);
bit  AT24C04_RecvACK();
void AT24C04_SendByte(BYTE dat);
BYTE AT24C04_RecvByte();
void AT24C04_ReadPage();
void AT24C04_WritePage();
void read_cmp(void);
//-----------------------------------
void cal_on();
void cal_off();
void recovery_factory();
void CMP_OFFS();
void IIC_ADDR_Change();
void delay_10ms();
void  SeriPushSend(uchar);

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void)
{

   //cnt=0;


   PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer
                                       // enable)
   PORT_Init();                        // Initialize Port I/O
   SYSCLK_Init ();                     // Initialize Oscillator
   UART0_Init();
UART1_Init();
  EA=1;
  

   //while(1)
   //{
      // If the complete word has been entered via the terminal followed by
      // carriage return
      
    //cnt=0;  

	 
                                                 //�������ݵ��ۼ�ֵ
   
	while(1)
	{
//	cnt=0;  
	/*SeriPushSend(0X31);                                       //����1֡��ȡ���
	delay(300);

	
    
	SBUF1 =BUF[1];   
		 while (!(SCON1 & 0x02));      // wait until UART1 is ready to transmit
         SCON1 &= ~0x02;               // clear TI1 interrupt flag
delay(100);
		 SBUF1 =BUF[2];   
		 while (!(SCON1 & 0x02));      // wait until UART1 is ready to transmit
         SCON1 &= ~0x02;               // clear TI1 interrupt flag
delay(100);
		 SBUF1 =BUF[3];   
		 while (!(SCON1 & 0x02));      // wait until UART1 is ready to transmit
         SCON1 &= ~0x02;               // clear TI1 interrupt flag
delay(100);
		 SBUF1 =BUF[4];   
		 while (!(SCON1 & 0x02));      // wait until UART1 is ready to transmit
         SCON1 &= ~0x02;               // clear TI1 interrupt flag
delay(100);
		 SBUF1 =BUF[5];   
		 while (!(SCON1 & 0x02));      // wait until UART1 is ready to transmit
         SCON1 &= ~0x02;               // clear TI1 interrupt flag
delay(100);
		 SBUF1 =BUF[6];   
		 while (!(SCON1 & 0x02));      // wait until UART1 is ready to transmit
         SCON1 &= ~0x02;               // clear TI1 interrupt flag
             // clear TI1 interrupt flag
		}
  /*  delay(100);                                    //����������ʱ 
	  if(BUF[0]==0X0D&&BUF[1]==0X0A){                         //֡ͷ�ж�
        SUM=BUF[6]+BUF[5]+BUF[4]+BUF[3]+BUF[2]+BUF[1]+BUF[0]; //У���
   	    if (BUF[7]==SUM){ 
		
		      SBUF1 =BUF[4];   
		 while (!(SCON1 & 0x02));      // wait until UART1 is ready to transmit
         SCON1 &= ~0x02;               // clear TI1 interrupt flag
		   
         }
	}*/
 
  }

  
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the Crossbar and GPIO ports.
//
// P0.4   digital   push-pull    UART TX
// P0.5   digital   open-drain   UART RX
//
//-----------------------------------------------------------------------------

void PORT_Init (void)
{
   P0MDOUT |= 0x11;                    // Enable UTX as push-pull output
   XBR0     = 0x01;                    // Enable UART on P0.4(TX) and P0.5(RX)
   XBR1     = 0x40;                    // Enable crossbar and weak pull-ups
      XBR2 = 0x01;                        // route UART 1 to crossbar
}

//-----------------------------------------------------------------------------
// SYSCLK_Init
//-------::----------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This routine initializes the system clock to use the internal oscillator
// at its maximum frequency.
// Also enables the Missing Clock Detector.
//-----------------------------------------------------------------------------

void SYSCLK_Init (void)
{
   OSCICN |= 0x03;                     // Configure internal oscillator for
                                       // its maximum frequency
   RSTSRC  = 0x04;                     // Enable missing clock detector
}

//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the UART0 using Timer1, for <BAUDRATE> and 8-N-1.
//-----------------------------------------------------------------------------

void UART0_Init (void)
{
   SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits
   if (SYSCLK/BAUDRATE/2/256 < 1) {
      TH1 = -(SYSCLK/BAUDRATE/2);
      CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
      CKCON |=  0x08;
   } else if (SYSCLK/BAUDRATE/2/256 < 4) {
      TH1 = -(SYSCLK/BAUDRATE/2/4);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01
      CKCON |=  0x01;
   } else if (SYSCLK/BAUDRATE/2/256 < 12) {
      TH1 = -(SYSCLK/BAUDRATE/2/12);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 00
   } else {
      TH1 = -(SYSCLK/BAUDRATE/2/48);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
      CKCON |=  0x02;
   }

   TL1 = TH1;                          // init Timer1
   TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;
   TR1 = 1;                            // START Timer1
   TX_Ready = 1;                       // Flag showing that UART can transmit
   IP |= 0x10;                         // Make UART high priority
   ES0 = 1;                            // Enable UART0 interrupts

}

//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// UART0_Interrupt
//-----------------------------------------------------------------------------
//
// This routine is invoked whenever a character is entered or displayed on the
// Hyperterminal.
//
//-----------------------------------------------------------------------------

/*void UART0_Interrupt (void) interrupt 4
{
   if (RI0 == 1)
   {
     

      RI0 = 0;                           // Clear interrupt flag

      Byte = SBUF0;                      // Read a character from UART

	  TX_Ready = 1; 

     
   }
   
}*/

void delay(unsigned int x)
{
unsigned int ii,jj;

for(ii=0;ii<1000;ii++)
   for(jj=0;jj<x;jj++)
{;;}
}

//*********************************************************
uchar HEX_TO_ASCII(uchar HEX_data)
{uchar ASCII_data;
	switch(HEX_data){       
	   case 0x00:ASCII_data=0x30;break;
	   case 0x01:ASCII_data=0x31;break;
       case 0x02:ASCII_data=0x32;break;
       case 0x03:ASCII_data=0x33;break;
	   case 0x04:ASCII_data=0x34;break;
	   case 0x05:ASCII_data=0x35;break;
       case 0x06:ASCII_data=0x36;break;
	   case 0x07:ASCII_data=0x37;break;
	   case 0x08:ASCII_data=0x38;break;
	   case 0x09:ASCII_data=0x39;break;
	   case 0x0a:ASCII_data=0x41;break;
	   case 0x0b:ASCII_data=0x42;break;
	   case 0x0c:ASCII_data=0x43;break;
       case 0x0d:ASCII_data=0x44;break;
	   case 0x0e:ASCII_data=0x45;break;
	   case 0x0f:ASCII_data=0x46;break;
    } 
    return(ASCII_data);  
}
//*********************************************************
void conversion(uint temp_data)  
{  
    uchar ge_data,shi_data,bai_data ,qian_data;
	qian_data=temp_data/1000 ;
    temp_data=temp_data%1000;   //ȡ������
    bai_data=temp_data/100 ;
    temp_data=temp_data%100;   //ȡ������
    shi_data=temp_data/10 ;
    temp_data=temp_data%10;   //ȡ������
    ge_data=temp_data;
    qian= qian_data;
    bai = bai_data;
    shi = shi_data;
    ge  = ge_data ; 	
}

void read_cmp(void)
{   uchar i;

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0x31);                   //����һ�β����Ƕ�
    AT24C04_Stop();                           //ֹͣ�ź�

	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();                               //��ʱ��ʵ��Ӧ���п���ִ����������
	Delay5ms();
	Delay5ms();
	Delay5ms();


    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0x35);                   //����һ�β����¶�
    AT24C04_Stop();                           //ֹͣ�ź�

    Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();                               //��ʱ��ʵ��Ӧ���п���ִ����������

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //���ʹ洢��Ԫ��ַ����0��ʼ	
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress+1);   //�����豸��ַ+���ź�
	 for (i=0; i<8; i++)
    {
        BUF[i] = AT24C04_RecvByte();
        if (i == 7)
        {
           AT24C04_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          AT24C04_SendACK(0);                //��ӦACK
       }
   }
    AT24C04_Stop();                          //ֹͣ�ź�

}

//--------------------------------------------------

/**************************************
��ʱ5΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5us()
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();  
}

/**************************************
��ʱ5����(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5ms()
{
    WORD n = 560;

    while (n--);
}

/**************************************
��ʼ�ź�
**************************************/
void AT24C04_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void AT24C04_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void AT24C04_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
bit AT24C04_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ

    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void AT24C04_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    AT24C04_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE AT24C04_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }

    return dat;
}

//*********************************************************
void cal_on(void)
{                                             //У׼
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xC0);                   //����У׼����
    AT24C04_Stop();                           //����ֹͣ�ź�
}
//*********************************************************
void cal_off(void)                            //�ر�У׼
{
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xC1);                   //����ֹͣУ׼����
    AT24C04_Stop();                           //����ֹͣ�ź�
}
//*********************************************************
void recovery_factory(void)                   //�ָ���������
{
    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xA0);                   //��������0xA0
    AT24C04_Stop();                           //����ֹͣ�ź�

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xAA);                   //��������0xAA
    AT24C04_Stop();                           //����ֹͣ�ź�

    AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xA5);                   //��������0xA5
    AT24C04_Stop();                           //����ֹͣ�ź�

	AT24C04_Start();                          //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);     //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                   //0��ʾ���� 
    AT24C04_SendByte(0xC5);                   //����0xC5,�ָ���������
    AT24C04_Stop();                           //����ֹͣ�ź�

}
//*********************************************************
void IIC_ADDR_Change(void)                   //iic��ַ����
{
    AT24C04_Start();                         //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);    //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                  //0��ʾ���� 
    AT24C04_SendByte(0xA0);                  //��������0xA0
    AT24C04_Stop();                          //����ֹͣ�ź�

    AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                 //0��ʾ���� 
    AT24C04_SendByte(0xAA);                 //��������0xAA
    AT24C04_Stop();                         //����ֹͣ�ź�

    AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                 //0��ʾ���� 
    AT24C04_SendByte(0xA5);                 //��������0xA5
    AT24C04_Stop();                         //����ֹͣ�ź�

	AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x00);                 //0��ʾ���� 
    AT24C04_SendByte(0xE8);                 //�µ�IIC��ַE0-FE��ż��(�ο�PDF�ĵ�)
    AT24C04_Stop();                         //����ֹͣ�ź�

}
//*********************************************************
void CMP_OFFS(void)                         //��ƫ��
{
    AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x03);                 //0��ʾ���� 
    AT24C04_SendByte(0x00);                 //��ƫ�Ǹ�8λ��д��0
    AT24C04_Stop();                         //����ֹͣ�ź�

    AT24C04_Start();                        //��ʼ�ź�
    AT24C04_SendByte(WriteDeviceAddress);   //�����豸��ַ+д�ź�
    AT24C04_SendByte(0x04);                 //0��ʾ���� 
    AT24C04_SendByte(0x64);                 //��ƫ�ǵ�8λ��д��100��ʵ����10.0�ȣ�
    AT24C04_Stop();                         //����ֹͣ�ź�
}
//*********************************************************
void Delay_10ms(void)
{
    int n=560;
    while (n--);
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
}

void  SeriPushSend(uchar send_data)
{
    SBUF0=send_data;  
	while(!TI0);TI0=0;	  
}
//�����ж�
void serial_serve(void) interrupt 4	
{
  if(RI0==1){
    RI0=0;
    BUF[cnt]=SBUF0;
	cnt++;
	if(cnt==7)cnt=0;
  }
}

//�ο��꾧��վ24c04ͨ�ų���

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------