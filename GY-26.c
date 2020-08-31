// GY-26 IIC���Գ���
// ʹ�õ�Ƭ��STC89C51 
// ����11.0592M
// ��ʾ��LCD1602
// ���뻷�� Keil uVision2
// �����а�ģ�鵱24c04����ͨ��
#include  <C8051F340.H>	
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>
#define   uchar unsigned char
#define   uint unsigned int	
#define   DataPort P0	//LCD1602���ݶ˿�

#define	WriteDeviceAddress   0xE0	  //����������IIC�����еĵ�ַ
#define	ReadDviceAddress     0xE1     //������IIC�����е�ַ+1

typedef unsigned char BYTE;
typedef unsigned short WORD;

BYTE BUF[8];                         //���ݻ�����
BYTE code res[6] _at_ 0x23;

sbit	SCL=P0^6;      //iicʱ�����Ŷ���
sbit	SDA=P0^7;      //iic�������Ŷ���
sbit    LCM_RS=P2^0;   //LCD1602����˿�		
sbit    LCM_RW=P2^1;   //LCD1602����˿�		
sbit    LCM_EN=P2^2;   //LCD1602����˿�          
sbit    KEY_1 =P2^6;   //����1
sbit    KEY_2 =P2^5;   //����2
sbit    KEY_3 =P2^4;   //����3
sbit    KEY_4 =P2^3;   //����4		

uchar templ,temph,cnt;
uchar ge,shi,bai,qian;
uint  dis_data,dis_data1;
#define SYSCLK      12000000           // SYSCLK frequency in Hz
#define BAUDRATE        9600           // Baud rate of UART in bps


//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void SYSCLK_Init (void);
void UART0_Init (void);
void PORT_Init (void);
void Timer2_Init (int);
void delay(unsigned int);

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

//*********************************************************
void main()
{ 
   unsigned int i;
   delay(500);			
   //InitLcd();
   //EA=0;
   cnt=0;
   PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer
                                       // enable)
   PORT_Init();                        // Initialize Port I/O
   SYSCLK_Init ();                     // Initialize Oscillator
   UART0_Init();
   EA = 1;
   TX_Ready=0;
  while(1)            //ѭ��
  { 
    read_cmp();   //��������
//---------��ʾ�Ƕ�
    dis_data=0;
    dis_data=BUF[1];
    dis_data<<=8;
    dis_data|=BUF[2];

    conversion(dis_data);
	ge=HEX_TO_ASCII(ge);
	shi=HEX_TO_ASCII(shi);
	bai=HEX_TO_ASCII(bai);
	qian=HEX_TO_ASCII(qian);
	EA=0;
	SBUF0='';
	while(!TI0);
	TI0=0;
	EA=1;

    /*DisplayOneChar(0,0,qian); 
    DisplayOneChar(1,0,bai); 
    DisplayOneChar(2,0,shi); 
    DisplayOneChar(3,0,'.'); 
	DisplayOneChar(4,0,ge); 

//---------��ʾ�¶�
    dis_data=0;
    dis_data=BUF[5];
    dis_data<<=8;
    dis_data|=BUF[6];
    
	if(dis_data>4095){           //���bit-12Ϊ1��������λΪ��
	DisplayOneChar(0,1,'-');     //��ʾ����
	dis_data&=0xefff;            //�����λ
	}
    else DisplayOneChar(0,1,' ');//���bit-12Ϊ0,�ո�,���

    conversion(dis_data);
	ge=HEX_TO_ASCII(ge);
	shi=HEX_TO_ASCII(shi);
	bai=HEX_TO_ASCII(bai);
	qian=HEX_TO_ASCII(qian);

    DisplayOneChar(1,1,qian); 
    DisplayOneChar(2,1,bai); 
    DisplayOneChar(3,1,shi); 
    DisplayOneChar(4,1,'.'); 
	DisplayOneChar(5,1,ge); 
	DisplayOneChar(6,1,0XDF);    //�¶ȵ�λ
	DisplayOneChar(7,1,'C'); //�¶ȵ�λ

//-------��ʾ��ƫ��
	dis_data1=0;
    dis_data1=BUF[3];
    dis_data1<<=8;
    dis_data1|=BUF[4];

    conversion(dis_data1);
	ge=HEX_TO_ASCII(ge);
	shi=HEX_TO_ASCII(shi);
	bai=HEX_TO_ASCII(bai);
	qian=HEX_TO_ASCII(qian);

    DisplayOneChar(7,0,qian); 
    DisplayOneChar(8,0,bai); 
    DisplayOneChar(9,0,shi); 
    DisplayOneChar(10,0,'.'); 
	DisplayOneChar(11,0,ge); 

//-------��ʾУ׼�ȼ�
    conversion(BUF[7]);
	ge=HEX_TO_ASCII(ge);
	shi=HEX_TO_ASCII(shi);
	bai=HEX_TO_ASCII(bai);
	qian=HEX_TO_ASCII(qian);
    DisplayOneChar(10,1,bai); 
    DisplayOneChar(11,1,shi); 
	DisplayOneChar(12,1,ge); 
//----------�������

    if(KEY_1==0){
	    delay_10ms();
	    if(KEY_1==0){
 	    cal_on(); 
   	    while(KEY_1==0)delay_10ms();
	    }
    }	  
    if(KEY_2==0){
	  delay_10ms();
	  if(KEY_2==0){
	  cal_off();  
      while(KEY_2==0)delay_10ms();
	  }
	}
    if(KEY_3==0){
	  delay_10ms();
	  if(KEY_3==0){
	  recovery_factory();  
      while(KEY_3==0)delay_10ms();
	  }
	}
    if(KEY_4==0){
     delay_10ms();
 	 if(KEY_4==0){
	// CMP_OFFS();  
	 IIC_ADDR_Change();
     while(KEY_4==0)delay_10ms();
     }
    }*/

    for (i=0;i<4000;i++);               
  }
} 


/*******************************/
void delay(unsigned int k)	
{						
unsigned int i,j;				
for(i=0;i<k;i++)
{			
for(j=0;j<121;j++)			
{;}}						
}
/*******************************/
void WaitForEnable(void)	
{					
DataPort=0xff;		
LCM_RS=0;LCM_RW=1;_nop_();
LCM_EN=1;_nop_();_nop_();
while(DataPort&0x80);	
LCM_EN=0;				
}					
/*******************************/
void WriteCommandLCM(uchar CMD,uchar Attribc)
{					
if(Attribc)WaitForEnable();	
LCM_RS=0;LCM_RW=0;_nop_();
DataPort=CMD;_nop_();	
LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}					
/*******************************/
void WriteDataLCM(uchar dataW)
{					
WaitForEnable();		
LCM_RS=1;LCM_RW=0;_nop_();
DataPort=dataW;_nop_();	
LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}		
/***********************************/
void InitLcd()				
{			
WriteCommandLCM(0x38,1);	
WriteCommandLCM(0x08,1);	
WriteCommandLCM(0x01,1);	
WriteCommandLCM(0x06,1);	
WriteCommandLCM(0x0c,1);
}			
/***********************************/
void DisplayOneChar(uchar X,uchar Y,uchar DData)
{						
Y&=1;						
X&=15;						
if(Y)X|=0x40;					
X|=0x80;			
WriteCommandLCM(X,0);		
WriteDataLCM(DData);		
}						
/***********************************/
/*
void DisplayListChar(uchar X,uchar Y,uchar code *DData)
{
uchar ListLength=0; 
Y&=0x1;                
X&=0xF;                
while(X<=15)             
{                       
DisplayOneChar(X,Y,DData[ListLength]);
ListLength++;           
X++;                 
}                     
}    
*/                 
/***********************************/
//*********************************************************
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

void PORT_Init (void)
{
   P0MDOUT |= 0x10;                    // Enable UTX as push-pull output
   XBR0     = 0x01;                    // Enable UART on P0.4(TX) and P0.5(RX)
   XBR1     = 0x40;                    // Enable crossbar and weak pull-ups
}

//-----------------------------------------------------------------------------
// SYSCLK_Init
//-----------------------------------------------------------------------------
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

void UART0_Interrupt (void) interrupt 4
{
   if (RI0 == 1)
   {
     

      RI0 = 0;                           // Clear interrupt flag

      Byte = SBUF0;                      // Read a character from UART

	  TX_Ready = 1; 

     
   }
   
}


//�ο��꾧��վ24c04ͨ�ų���