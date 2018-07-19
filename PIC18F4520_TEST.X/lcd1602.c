/*********************************************************************
 *
 *                           LCD1602.C
 *
 *********************************************************************
 * 文件名: LCD1602.C
 * 描述: 2*16液晶模块驱动程序，应用时只需要根据硬件连接方式作适当修改，在主程序中包含其头文件即可以用几个简单的函数实现功能，实现了简化编程
 ********************************************************************/

/*函数实现*/
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
					0x01,0x03,0x1d,0x15,0x1d,0x03,0x01,0x00}; /*年、月、日、￥、元、℃、↑、小喇叭图标*/
					

		
/*产生一个LCD模块的使能脉冲*/
/*该函数只在本文件内使用，不会被其他文件调用，因此放在本文件的最前面，不在H文件中声明了*/
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
   	ADCON1=0x0F;/*所有引脚均设置为数字IO脚*/
   	Delay10Ms(10);/*延时100ms*/
   	TRIS_LCD_RW=0;/*设置单片机LCD控制引脚全为输出*/
	TRIS_LCD_RS=0;
	TRIS_LCD_EN=0;
   	LCD_wrcmd(LCD_MODE_STD);/*LCD标准工作模式：8位数据传送，2行显示，字符点阵5*7*/
   	LCD_wrcmd(DISP_OFF);/*显示关闭*/
    	LCD_wrcmd(DISP_CLR);/*清屏*/ 
    /*清屏和光标归位需要较长的时间*/
   	LCD_wrcmd(CUR_AUTO_R);/*设置光标在文字插入后自动右移*/
   	LCD_wrcmd(DISP_ON	& CUR_OFF & BLINK_OFF);/*显示开，无光标, 光标不闪烁*/
   	//LCD_wrcmd(DISP_ON	& CUR_ON & BLINK_ON);/*显示开，光标, 光标闪烁*/
   	CG_Write();/*建立自定义字符块*/
}

//void LCD_wrcmd(Uchar cmd)/*写入控制命令*/
void LCD_wrcmd(Uchar cmd)/*写入控制命令*/
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
   	TRIS_LCD_DATA=0x00;	/*单片机的LCD数据口设置为全输出*/
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

void LCD_wrchar(char str)/*写入要显示的字符*/
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
   	TRIS_LCD_DATA=0x00;	/*单片机的LCD数据口设置为全输出*/
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

void LCD_setxy(char x,char y) /*设定显示位置，行x=1/2,列y=1~16的任意整数*/
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


void LCD_wrstr(const rom char *s)/*写入要显示的字符串*/
{
 for(;*s!='\0';s++)LCD_wrchar(*s);
}


void LCD_wrul(unsigned long num)/*写入要显示的无符号长整型数*/
{
	char str[11];/*无符号长整型数转换为字符串是10个，所以需要11个单元存储*/
	int i=0;
	int j=0;
	ultoa(num,str);/*将无符号长整型数转换为字符串*/
	LCD_wrcmd(CUR_AUTO_L);/*设置光标在文字插入后自动左移*/
	while(str[i]!='\0')/*搜索字符串结束符*/
		{
		i++;	
		}
	while(i>0)/*显示前面的有效数字*/
		{
		i--;
		LCD_wrchar(str[i]);
		j++;
		}
	while(j<10)/*往前写满10位，也就是前面都写空格*/
		{
		LCD_wrchar(0x20);	
		j++;
		}
	LCD_wrcmd(CUR_AUTO_R);/*设置光标在文字插入后自动右移*/
}


void LCD_wrlval(unsigned long num,unsigned char bits,unsigned char dp)/*写入要显示的长变量*/
{
	char str[11];/*无符号长整型数转换为字符串是10个，所以需要11个单元存储*/
	int i=0;
	int j=0;
	ultoa(num,str);/*将无符号长整型数转换为字符串*/
	LCD_wrcmd(CUR_AUTO_L);/*设置光标在文字插入后自动左移*/
	while(str[i]!='\0')/*搜索字符串结束符*/
		{
		i++;	
		}
	if (i>bits)/*要显示的数据比规定的显示位数多，数据显示溢出*/
		{
		while(j<bits)/*往前写满规定的位数，也就是前面都写空格，直到规定的位数*/
			{
			LCD_wrchar('-');	/*规定的位全部写-，表示数据溢出*/
			j++;
			if (j==dp) LCD_wrchar('.');/*插入小数点*/
			}
		}
	else
		{
		while(i>0)/*显示前面的有效数字*/
			{
			i--;
			LCD_wrchar(str[i]);
			j++;
			if (j==dp) LCD_wrchar('.');/*插入小数点*/
			}
		while(j<bits)/*往前写满规定的位数，也就是前面都写空格，直到规定的位数*/
			{
			if (j==dp) LCD_wrchar('.');/*插入小数点*/
			if (j<=dp) LCD_wrchar('0');/*小数点前后补0字符*/	
			else LCD_wrchar(0x20);	/*小数点前后补空字符*/
			j++;
			}
		}
	LCD_wrcmd(CUR_AUTO_R);/*设置光标在文字插入后自动右移*/
}


void wait_until_LCDready(void) /*检测忙标志，忙则等待*/
{
  	LCD_EN=0;/*此句必须加，否则后面RS RW输出电平后，液晶屏出现光标复位的现象*/
	LCD_RS=0;
	TRIS_LCD_DATA=0x0ff;/*设置单片机LCD数据引脚全为输入*/
	LCD_RW=1;
	LCD_EN=1;/*读状态的时候，E始终保持高电平即可*/
	Nop();
	Nop();
	Nop();
	Nop();
    	while(LCD_BUSY==1);/*LCD忙，则原地等待*/
     LCD_EN=0;
}



void CG_Write(void)/*建立自定义字符块*/
{
	int i;
	LCD_wrcmd(SET_ADDR_CGRAM);/*字符发生器CGRAM地址设置*/
	for(i=0;i<64;i++)
		{
		LCD_wrchar(cgtab[i]);
		};
}