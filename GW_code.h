/*****************************/
/****************************/

#ifndef _GW_code_h_
#define _GW_code_h_

#include <c8051f340.h>

//P3 ��������
sbit L4=P3^0;
sbit L3=P3^1;
sbit L2=P3^2;
sbit L1=P3^3;
sbit R4=P3^4;
sbit R3=P3^5;
sbit R2=P3^6;
sbit R1=P3^7;
//sbit DENG=P0^6;



void GM_forward_SE(int n,int JC);
void GM_forward(int n,int JC);
void GM_backward(int n,int JC);
void GM_forward_3D(int n,int JC);                       //******************************************����ǰѲ��
void GM_backward_3D(int n,int JC);                       //******************************************���ƺ�Ѳ��

void Main_switch(void);     //xΪ��������ʽ�����ÿ���λ 

#endif