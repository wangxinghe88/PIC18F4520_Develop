#include <p18cxxx.h>/*18F系列单片机头文件*/
#include "k18.h"/*HL-K18开发板头文件*/
#include "delay.h"

/*0-F共阴字形码表*/
const rom uchar DB[17]={0x3f  , 0x06 , 0x5b , 0x4f , 0x66 ,
		 0x6d ,0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c ,
		 0x39 , 0x5e , 0x79 , 0x71 , 0x00};

void LED4_display(unsigned int i)
{
	unsigned int a,bit1000,bit100,bit10,bit1;
	a=i;
	bit1000=a/1000;//提取千位
	a=a%1000;

	bit100=a/100;//提取百位
	a=a%100;

	bit10=a/10;//提取十位
	bit1=a%10;//提取个位
   		
	COL4=0; 
	PORTD=DB[bit1];
	COL1=1;   //个位的位选
	delayms(5);/*延时5mS*/

	COL1=0; 
	PORTD=DB[bit10];
	COL2=1;   //十位的位选
	delayms(5);/*延时5mS*/

	COL2=0; 
	PORTD=DB[bit100];
	COL3=1;   //百位的位选
	delayms(5);/*延时5mS*/

	COL3=0; 
	PORTD=DB[bit1000];
	COL4=1;   //千位的位选
	delayms(5);/*延时5mS*/

}