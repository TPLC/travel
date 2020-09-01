/**
  ******************************************************************************
  * @file    xunbao.c
  * @author  MRT.ZHONG
  * @version V1.1				//Add the light functions by yukino
  * @date    2015-5-13
  * @brief   Ѱ������λ�ý��պ�������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨��c8051f340-IDE
  *
  * �ص㣺������ʵ����
  *
  ******************************************************************************
*/



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////*************   ����ʶ��ص�
//////////////////////////////////////////////////////////////////////////////////

#include"All_Include.h"

unsigned char m1,n2,p,byte,count1,count2,flag1,flag2;		//���ձ������ݱ�־λ
unsigned char treasure1,treasure2,treasure3,nontreasure;				//�����ŵص�
//unsigned char flag11,flag22,flag33;							//��ʶ�����־
										//�����
//uchar program=0x00;
extern unsigned char BUF[8];
extern unsigned char cnt;
extern unsigned int Average1,Average2,NNN,LLL;



unsigned char numberAB()								//ʶ��3,4
{
	DENG1=1;										//����ƿ���
	m1=0;
	n2=0;
	p=0;
	count1=0;
	count2=0;
	flag1=0;
	nontreasure=0;	
      while(1)
    { 
           
				while(1)
			{     
			
				SBUF0=49;   //ʶ�� 48='0' 49='1,A'  50='2,B'  51='3,C' 52='4,D' 53='5,E' 54='6,F' 55 56 57='9'
				delay(20);	     
	        	while(!TI0);//���ͱ�־λ
	            TI0=0;	
				  delay(40);  
				  byte=SBUF0;
		// while(!RI0);
				  RI0=0;

				if(byte==49)
				m1++;
				else if(byte==50)
				n2++;
				else
				p++;
				if(m1>=20||n2>=20||p>=40) break;
				     			                   
			}		
		if(m1>=20)
			{
			BELLON;
			delay(200);
			BELLOFF;
			delay(300);
          
			flag1=1;
			count1=1;//3��ƽ̨
			m1=0;
			break;
			}
		if(n2>=20){
			BELLON;

			delay(200);
			BELLOFF;

		    delay(200);
			BELLON;

			delay(200);
			BELLOFF;

			flag1=1;
			count2=1;//4��ƽ̨
			n2=0;
			break;	
			}
		if(p>=40)    //δʶ��
			{
			BELLON;
			delay(100);
			BELLOFF;
		    delay(100);
			BELLON;
			delay(100);
			BELLOFF;
			delay(100);
			BELLON;
			delay(100);
			BELLOFF;
		    	if(nontreasure<2)
			{
			
			
			speedl=90;
			speedr=90;
			delay(100);
			
			speedl=127;
		    	speedr=127;
				delay(200);
				
				}
             else if(nontreasure<4)
			 {
			   
			speedl=180;
			speedr=180;
			delay(100);
			speedl=127;
			speedr=127;
			delay(200);
			 }
			 	else if(nontreasure<6)
			 {
			  
			
			speedl=127+40;
			speedr=127-40;
			delay(70);
	        speedr=127;
			speedl=127;
			delay(200);
			 }
			 	else if(nontreasure<8)
			 {
			  
			
			speedl=127-40;
			speedr=127+40;
			delay(70);
			speedr=127;
			speedl=127;
			delay(200);

			 }
			p=0;
			nontreasure++;
		   }		

	    if(flag1==1) break; 
	    	/////////////////////////////////////////////////
	     
	}

	LLL=0;
	NNN=0;
	Average1=0;
	Average2=0;
	
    /////////////////////////////////////////////////////////////	
	
	if(count1==1)
		flag2='A';//
	else if(count2==1)
		flag2='B';//
	else
		flag2=0xff;
		DENG1=0;									//����ƹر�
	return flag2;

}

unsigned char numberCD()								//ʶ��5,6
{
	DENG1=1;										//����ƿ���
	m1=0;
	n2=0;
	p=0;
	count1=0;
	count2=0;
	flag1=0;
	nontreasure=0;	
      while(1)
    { 
           
				while(1)
			{     
			
				SBUF0=50;   //ʶ�� 48='0' 49='1,A'  50='2,B'  51='3,C' 52='4,D' 53='5,E' 54='6,F' 55 56 57='9'	     
	        	while(!TI0);//���ͱ�־λ
	            TI0=0;	 
				  delay(30);  
				  byte=SBUF0;
		// while(!RI0);
				  RI0=0;

				if(byte==51)
				m1++;
				else if(byte==52)
				n2++;
				else
				p++;
				if(m1>=20||n2>=20||p>=40) break;
				     			                   
			}		
		if(m1>=20)
			{
			
			BELLON;
         
			delay(200);
			BELLOFF;
		
			delay(300);
			
			flag1=1;
			count1=1;//5��ƽ̨
			m1=0;
			break;
			}
		if(n2>=20){
			BELLON;
			
			delay(200);
			BELLOFF;
			
		    delay(200);
			BELLON;

			delay(200);

			BELLOFF;
			flag1=1;
			count2=1;//6��ƽ̨
			n2=0;
			break;	
			}
		if(p>=40)    //δʶ��
			{
			BELLON;
			delay(100);
			BELLOFF;
		    delay(100);
			BELLON;
			delay(100);
			BELLOFF;
			delay(100);
			BELLON;
			delay(100);
			BELLOFF;
				if(nontreasure<2)
			{
			
				
			
			speedl=90;
			speedr=90;
			delay(100);
			
				speedl=127;
		    	speedr=127;
				delay(100);
				}
				else if(nontreasure<4)
			 {
		
			speedl=180;
			speedr=180;
			delay(100);
			speedl=127;
			speedr=127;
			delay(200);
			 }
			p=0;
			nontreasure++;
		   }		
	    if(flag1==1) break; 
	    
	}
	
	
	
    /////////////////////////////////////////////////////////////	
	
	if(count1==1)
		flag2='C';//
	else if(count2==1)
		flag2='D';//
	else
		flag2=0xff;
		DENG1=0;									//����ƹر�
	return flag2;

}
unsigned char numberEF()								//ʶ��7,8
{
	DENG1=1;										//����ƿ���
	m1=0;
	n2=0;
	p=0;
	count1=0;
	count2=0;
	flag1=0;
	nontreasure=0;	
	LLL=0;
	NNN=0;
	Average1=0;
      while(1)
    { 
           
				while(1)
			{     
			
				SBUF0=51;   //ʶ�� 48='0' 49='1,A'  50='2,B'  51='3,C' 52='4,D' 53='5,E' 54='6,F' 55 56 57='9'	     
	        	while(!TI0);//���ͱ�־λ
	            TI0=0;	 
				  delay(30);  
				  byte=SBUF0;
		 //while(!RI0);
				  RI0=0;

				if(byte==53)
				m1++;
				else if(byte==54)
				n2++;
				else
				p++;
				if(m1>=20||n2>=20||p>=40) break;
				     			                   
			}		
		if(m1>=20)
			{
			BELLON;
			delay(200);
			BELLOFF;
			delay(300);
			flag1=1;
			count1=1;//7��ƽ̨
			m1=0;
			break;
			}
		if(n2>=20){
			BELLON;
			delay(200);
			BELLOFF;
		    delay(200);
			BELLON;
			delay(200);
			BELLOFF;
			
			flag1=1;
			count2=1;//8��ƽ̨
			n2=0;
			break;	
			}
		if(p>=40)    //δʶ��
			{
			BELLON;
			delay(100);
			BELLOFF;
		    delay(100);
			BELLON;
			delay(100);
			BELLOFF;
			delay(100);
			BELLON;
			delay(100);
			BELLOFF;
         
			if(nontreasure==6)
			{
			  speedl=127-40;
			speedr=127+40;
			delay(70);
			speedr=127;
			speedl=127;
			delay(200);
			speedl=127-40;
			speedr=127+40;
			delay(70);
			speedr=127;
			speedl=127;
			delay(200);
			}
			if(nontreasure<2)
			 {
			 
			speedl=90;
			speedr=90;
			delay(100);
			
			speedl=127;
			speedr=127;
			delay(200);
				}
			else if(nontreasure<4)
			 {
			  
			
			speedl=180;
			speedr=180;
			delay(100);
			speedl=127;
			speedr=127;
			delay(200);
			 }

            	else if(nontreasure<6)
			 {
			  
			
			speedl=127+40;
			speedr=127-40;
			delay(70);
	        speedr=127;
			speedl=127;
			delay(200);
			 }
			 	else if(nontreasure<8)
			 {
			  
			
			speedl=127-40;
			speedr=127+40;
			delay(70);
			speedr=127;
			speedl=127;
			delay(200);

			 }
			 else
			 {
			}
			p=0;
			nontreasure++;
		   }		
	if(flag1==1) break; 
	}
		
    /////////////////////////////////////////////////////////////	
	if(count1==1)
		flag2='E';//
	else if(count2==1)
		flag2='F';//
	else
		flag2=0xff;
		DENG1=0;									//����ƹر�
	return flag2;

}
