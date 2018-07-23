#include <p18cxxx.h>/*18Fϵ�е�Ƭ��ͷ�ļ�*/
#include "k18.h"/*HL-K18������ͷ�ļ�*/
#include "delay.h"

/*0-F�����������*/
const rom uchar DB[17]={0x3f  , 0x06 , 0x5b , 0x4f , 0x66 ,
		 0x6d ,0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c ,
		 0x39 , 0x5e , 0x79 , 0x71 , 0x00};

void LED4_display(unsigned int i)
{
	unsigned int a,bit1000,bit100,bit10,bit1;
	a=i;
	bit1000=a/1000;//��ȡǧλ
	a=a%1000;

	bit100=a/100;//��ȡ��λ
	a=a%100;

	bit10=a/10;//��ȡʮλ
	bit1=a%10;//��ȡ��λ
   		
	COL4=0; 
	PORTD=DB[bit1];
	COL1=1;   //��λ��λѡ
	delayms(5);/*��ʱ5mS*/

	COL1=0; 
	PORTD=DB[bit10];
	COL2=1;   //ʮλ��λѡ
	delayms(5);/*��ʱ5mS*/

	COL2=0; 
	PORTD=DB[bit100];
	COL3=1;   //��λ��λѡ
	delayms(5);/*��ʱ5mS*/

	COL3=0; 
	PORTD=DB[bit1000];
	COL4=1;   //ǧλ��λѡ
	delayms(5);/*��ʱ5mS*/

}