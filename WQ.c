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

#define	WriteDeviceAddress   0xE0	  //定义器件在IIC总线中的地址
#define	ReadDviceAddress     0xE1     //器件在IIC总线中地址+1

typedef unsigned char BYTE;
typedef unsigned short WORD;

BYTE BUF[8];                         //数据缓存区
BYTE code res[6] _at_ 0x23;

sbit	SCL=P1^0;      //iic时钟引脚定义
sbit	SDA=P1^1;      //iic数据引脚定义
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

	 
                                                 //接收数据的累计值
   
	while(1)
	{
//	cnt=0;  
	/*SeriPushSend(0X31);                                       //发送1帧读取命令。
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
  /*  delay(100);                                    //传送数据延时 
	  if(BUF[0]==0X0D&&BUF[1]==0X0A){                         //帧头判断
        SUM=BUF[6]+BUF[5]+BUF[4]+BUF[3]+BUF[2]+BUF[1]+BUF[0]; //校验和
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
    temp_data=temp_data%1000;   //取余运算
    bai_data=temp_data/100 ;
    temp_data=temp_data%100;   //取余运算
    shi_data=temp_data/10 ;
    temp_data=temp_data%10;   //取余运算
    ge_data=temp_data;
    qian= qian_data;
    bai = bai_data;
    shi = shi_data;
    ge  = ge_data ; 	
}

void read_cmp(void)
{   uchar i;

    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0x31);                   //发送一次测量角度
    AT24C04_Stop();                           //停止信号

	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();                               //延时，实际应用中可以执行其他程序
	Delay5ms();
	Delay5ms();
	Delay5ms();


    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0x35);                   //发送一次测量温度
    AT24C04_Stop();                           //停止信号

    Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();
	Delay5ms();                               //延时，实际应用中可以执行其他程序

    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //发送存储单元地址，从0开始	
    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress+1);   //发送设备地址+读信号
	 for (i=0; i<8; i++)
    {
        BUF[i] = AT24C04_RecvByte();
        if (i == 7)
        {
           AT24C04_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          AT24C04_SendACK(0);                //回应ACK
       }
   }
    AT24C04_Stop();                          //停止信号

}

//--------------------------------------------------

/**************************************
延时5微秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
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
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5ms()
{
    WORD n = 560;

    while (n--);
}

/**************************************
起始信号
**************************************/
void AT24C04_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void AT24C04_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void AT24C04_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
bit AT24C04_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void AT24C04_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    AT24C04_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE AT24C04_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }

    return dat;
}

//*********************************************************
void cal_on(void)
{                                             //校准
    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xC0);                   //发送校准命令
    AT24C04_Stop();                           //发送停止信号
}
//*********************************************************
void cal_off(void)                            //关闭校准
{
    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xC1);                   //发送停止校准命令
    AT24C04_Stop();                           //发送停止信号
}
//*********************************************************
void recovery_factory(void)                   //恢复出厂设置
{
    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xA0);                   //发送数据0xA0
    AT24C04_Stop();                           //发送停止信号

    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xAA);                   //发送数据0xAA
    AT24C04_Stop();                           //发送停止信号

    AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xA5);                   //发送数据0xA5
    AT24C04_Stop();                           //发送停止信号

	AT24C04_Start();                          //起始信号
    AT24C04_SendByte(WriteDeviceAddress);     //发送设备地址+写信号
    AT24C04_SendByte(0x00);                   //0表示命令 
    AT24C04_SendByte(0xC5);                   //发送0xC5,恢复出厂命令
    AT24C04_Stop();                           //发送停止信号

}
//*********************************************************
void IIC_ADDR_Change(void)                   //iic地址更改
{
    AT24C04_Start();                         //起始信号
    AT24C04_SendByte(WriteDeviceAddress);    //发送设备地址+写信号
    AT24C04_SendByte(0x00);                  //0表示命令 
    AT24C04_SendByte(0xA0);                  //发送数据0xA0
    AT24C04_Stop();                          //发送停止信号

    AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x00);                 //0表示命令 
    AT24C04_SendByte(0xAA);                 //发送数据0xAA
    AT24C04_Stop();                         //发送停止信号

    AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x00);                 //0表示命令 
    AT24C04_SendByte(0xA5);                 //发送数据0xA5
    AT24C04_Stop();                         //发送停止信号

	AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x00);                 //0表示命令 
    AT24C04_SendByte(0xE8);                 //新的IIC地址E0-FE中偶数(参考PDF文档)
    AT24C04_Stop();                         //发送停止信号

}
//*********************************************************
void CMP_OFFS(void)                         //磁偏角
{
    AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x03);                 //0表示命令 
    AT24C04_SendByte(0x00);                 //磁偏角高8位，写入0
    AT24C04_Stop();                         //发送停止信号

    AT24C04_Start();                        //起始信号
    AT24C04_SendByte(WriteDeviceAddress);   //发送设备地址+写信号
    AT24C04_SendByte(0x04);                 //0表示命令 
    AT24C04_SendByte(0x64);                 //磁偏角低8位，写入100（实际是10.0度）
    AT24C04_Stop();                         //发送停止信号
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
//串口中断
void serial_serve(void) interrupt 4	
{
  if(RI0==1){
    RI0=0;
    BUF[cnt]=SBUF0;
	cnt++;
	if(cnt==7)cnt=0;
  }
}

//参考宏晶网站24c04通信程序

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------