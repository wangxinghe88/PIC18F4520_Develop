/*********************************************************************
 *
 *                           LCD1602.C
 *
 *********************************************************************
 * �ļ���: LCD1602.C
 * ����: 2*16Һ��ģ����������Ӧ��ʱֻ��Ҫ����Ӳ�����ӷ�ʽ���ʵ��޸ģ����������а�����ͷ�ļ��������ü����򵥵ĺ���ʵ�ֹ��ܣ�ʵ���˼򻯱��
 ********************************************************************/

/*����ʵ��*/
#include <p18cxxx.h>
#include <stdlib.h>
#include "k18.h"
#include "lcd1602.h"
#include "delay.h"
				
const rom char cgtab[64]={0x08,0x0f,0x12,0x0f,0x0a,0x1f,0x02,0x02,
					0x0f,0x09,0x0f,0x09,0x0f,0x09,0x11,0x00,
					0x1f,0x11,0x11,0x1f,0x11,0x11,0x1f,0x00,
					0x11,0x0a,0x04,0x1f,0x04,0x1f,0x04,0x00,
					0x0e,0x00,0x1f,0x0a,0x0a,0x0a,0x13,0x00,
					0x18,0x18,0x07,0x08,0x08,0x08,0x07,0x00,
					0x04,0x0a,0x15,0x04,0x04,0x04,0x04,0x00,
					0x01,0x03,0x1d,0x15,0x1d,0x03,0x01,0x00}; /*�ꡢ�¡��ա�����Ԫ���桢����С����ͼ��*/
					

		
/*����һ��LCDģ���ʹ������*/
/*�ú���ֻ�ڱ��ļ���ʹ�ã����ᱻ�����ļ����ã���˷��ڱ��ļ�����ǰ�棬����H�ļ���������*/
void LCD_E_toggle(void)
{
	LCD_EN=0;
	Nop();
	Nop();
	Nop();
	Nop();
 	LCD_EN=1;
	Nop();
	Nop();
	Nop();
	Nop();
}

void LCD_init(void)
{
   	ADCON1=0x0F;/*�������ž�����Ϊ����IO��*/
   	Delay10Ms(10);/*��ʱ100ms*/
   	TRIS_LCD_RW=0;/*���õ�Ƭ��LCD��������ȫΪ���*/
	TRIS_LCD_RS=0;
	TRIS_LCD_EN=0;
   	LCD_wrcmd(LCD_MODE_STD);/*LCD��׼����ģʽ��8λ���ݴ��ͣ�2����ʾ���ַ�����5*7*/
   	LCD_wrcmd(DISP_OFF);/*��ʾ�ر�*/
    	LCD_wrcmd(DISP_CLR);/*����*/ 
    /*�����͹���λ��Ҫ�ϳ���ʱ��*/
   	LCD_wrcmd(CUR_AUTO_R);/*���ù�������ֲ�����Զ�����*/
   	LCD_wrcmd(DISP_ON	& CUR_OFF & BLINK_OFF);/*��ʾ�����޹��, ��겻��˸*/
   	//LCD_wrcmd(DISP_ON	& CUR_ON & BLINK_ON);/*��ʾ�������, �����˸*/
   	CG_Write();/*�����Զ����ַ���*/
}

//void LCD_wrcmd(Uchar cmd)/*д���������*/
void LCD_wrcmd(Uchar cmd)/*д���������*/
{
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	wait_until_LCDready();
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	TRIS_LCD_DATA=0x00;	/*��Ƭ����LCD���ݿ�����Ϊȫ���*/
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_EN=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_RS=0;
	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_RW=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_DATA=cmd;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_EN=1;
   	Nop();/****/
   	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
   	LCD_EN=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
}

void LCD_wrchar(char str)/*д��Ҫ��ʾ���ַ�*/
{
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	wait_until_LCDready();
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	TRIS_LCD_DATA=0x00;	/*��Ƭ����LCD���ݿ�����Ϊȫ���*/
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_EN=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_RS=1;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_RW=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_DATA=str;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
   	LCD_EN=1;
   	Nop();/****/
   	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
   	LCD_EN=0;
   	Nop();/****/
	Nop();
	Nop();
	Nop();
}

void LCD_setxy(char x,char y) /*�趨��ʾλ�ã���x=1/2,��y=1~16����������*/
{
    	char temp;
    	if(x==1)
  	{
	  	temp=0x80+y-1;
  		LCD_wrcmd(temp);
  	}
 	else
  	{
	  	temp=0xC0+y-1;
  		LCD_wrcmd(temp);
  	}
}


void LCD_wrstr(const rom char *s)/*д��Ҫ��ʾ���ַ���*/
{
 for(;*s!='\0';s++)LCD_wrchar(*s);
}


void LCD_wrul(unsigned long num)/*д��Ҫ��ʾ���޷��ų�������*/
{
	char str[11];/*�޷��ų�������ת��Ϊ�ַ�����10����������Ҫ11����Ԫ�洢*/
	int i=0;
	int j=0;
	ultoa(num,str);/*���޷��ų�������ת��Ϊ�ַ���*/
	LCD_wrcmd(CUR_AUTO_L);/*���ù�������ֲ�����Զ�����*/
	while(str[i]!='\0')/*�����ַ���������*/
		{
		i++;	
		}
	while(i>0)/*��ʾǰ�����Ч����*/
		{
		i--;
		LCD_wrchar(str[i]);
		j++;
		}
	while(j<10)/*��ǰд��10λ��Ҳ����ǰ�涼д�ո�*/
		{
		LCD_wrchar(0x20);	
		j++;
		}
	LCD_wrcmd(CUR_AUTO_R);/*���ù�������ֲ�����Զ�����*/
}


void LCD_wrlval(unsigned long num,unsigned char bits,unsigned char dp)/*д��Ҫ��ʾ�ĳ�����*/
{
	char str[11];/*�޷��ų�������ת��Ϊ�ַ�����10����������Ҫ11����Ԫ�洢*/
	int i=0;
	int j=0;
	ultoa(num,str);/*���޷��ų�������ת��Ϊ�ַ���*/
	LCD_wrcmd(CUR_AUTO_L);/*���ù�������ֲ�����Զ�����*/
	while(str[i]!='\0')/*�����ַ���������*/
		{
		i++;	
		}
	if (i>bits)/*Ҫ��ʾ�����ݱȹ涨����ʾλ���࣬������ʾ���*/
		{
		while(j<bits)/*��ǰд���涨��λ����Ҳ����ǰ�涼д�ո�ֱ���涨��λ��*/
			{
			LCD_wrchar('-');	/*�涨��λȫ��д-����ʾ�������*/
			j++;
			if (j==dp) LCD_wrchar('.');/*����С����*/
			}
		}
	else
		{
		while(i>0)/*��ʾǰ�����Ч����*/
			{
			i--;
			LCD_wrchar(str[i]);
			j++;
			if (j==dp) LCD_wrchar('.');/*����С����*/
			}
		while(j<bits)/*��ǰд���涨��λ����Ҳ����ǰ�涼д�ո�ֱ���涨��λ��*/
			{
			if (j==dp) LCD_wrchar('.');/*����С����*/
			if (j<=dp) LCD_wrchar('0');/*С����ǰ��0�ַ�*/	
			else LCD_wrchar(0x20);	/*С����ǰ�󲹿��ַ�*/
			j++;
			}
		}
	LCD_wrcmd(CUR_AUTO_R);/*���ù�������ֲ�����Զ�����*/
}


void wait_until_LCDready(void) /*���æ��־��æ��ȴ�*/
{
  	LCD_EN=0;/*�˾����ӣ��������RS RW�����ƽ��Һ�������ֹ�긴λ������*/
	LCD_RS=0;
	TRIS_LCD_DATA=0x0ff;/*���õ�Ƭ��LCD��������ȫΪ����*/
	LCD_RW=1;
	LCD_EN=1;/*��״̬��ʱ��Eʼ�ձ��ָߵ�ƽ����*/
	Nop();
	Nop();
	Nop();
	Nop();
    	while(LCD_BUSY==1);/*LCDæ����ԭ�صȴ�*/
     LCD_EN=0;
}



void CG_Write(void)/*�����Զ����ַ���*/
{
	int i;
	LCD_wrcmd(SET_ADDR_CGRAM);/*�ַ�������CGRAM��ַ����*/
	for(i=0;i<64;i++)
		{
		LCD_wrchar(cgtab[i]);
		};
}