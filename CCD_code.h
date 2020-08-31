/*****************************/
/****************************/

#ifndef _CCD_code_h_
#define _CCD_code_h_


#include <c8051f340.h>

//CCD//P2
#define DOTCLK     (129000/(Integrationtime))   //ÏñËØÆµÂÊ
#define QIANCCD1   AMX0P=0X00  //P20aaa
#define QIANGG     AMX0P=0X01  //P21
#define QIANCCD2   AMX0P=0X02  //P22
#define HOUCCD1    AMX0P=0X03  //P23
#define HOUGG      AMX0P=0X04  //P25
#define HOUCCD2    AMX0P=0X05  //P26


void light_gain(void);

void CCD_forward(int n,int JC);
void CCD_backward(int n,int JC);
void CCD_forward_Left(int n,int JC);
void CCD_forward_L(int n,int JC); 				
void CCD_forward_R(int n,int JC);  				
void CCD_backward_L(int n,int JC);
void CCD_backward_R(int n,int JC);  
void CCD_FOR_BOLANG(int n); 								
void CCD_BACK_BOLANG(int n);  
void CCD_forward_B(int n,int JC);
void CCD_backward_F(int n,int JC);
void CCD_forward_B_R(int n,int JC);
void CCD_forward_SP(int n,int JC); 
void CCD_forward_ss(); 	

#endif