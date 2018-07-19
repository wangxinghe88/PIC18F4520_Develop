/*********************************************************************
 *
 *                           LCD1602.H
 *
 *********************************************************************
 * 文件名: LCD1602.H
 ********************************************************************/
#ifndef __LCD1602_H
#define __LCD1602_H


/*单片机与LCD1602连接数据线定义*/
#define LCD_DATA      PORTD
#define TRIS_LCD_DATA TRISD
#define LCD_BUSY  PORTDbits.RD7


#define LCD_RS   PORTAbits.RA2   		/* PORT for RS */
#define TRIS_LCD_RS  DDRAbits.RA2    	/* TRIS for RS */

#define LCD_RW   PORTAbits.RA3   		/* PORT for RW */
#define TRIS_LCD_RW  DDRAbits.RA3    	/* TRIS for RW */

#define LCD_EN    PORTAbits.RA5   		/* PORT for EN */
#define TRIS_LCD_EN   DDRAbits.RA5    	/* TRIS for EN */


/*-------------------1602液晶命令定义-------------------*/

/*初始化命令*/
#define DISP_CLR			0b00000001	/*清显示,光标复位到第一行首(地址00H）*/
#define CUR_HOME			0b00000010	/*光标复位，光标返回到第一行首*/

/*光标和显示模式设置*/
#define CUR_AUTO_R			0b00000110	/*设置光标在文字插入后自动右移*/
#define CUR_AUTO_L			0b00000100	/*设置光标在文字插入后自动左移*/
#define DISP_AUTO_R		0b00000111 	/*设置显示在文字插入后自动右移*/
#define DISP_AUTO_L		0x00000101 	/*设置显示在文字插入后自动左移*/

/*显示开关控制*/
#define DISP_ON			0b00001111	/*显示开*/
#define DISP_OFF			0b00001011	/*显示关*/
#define CUR_ON			0b00001111	/*光标开*/
#define CUR_OFF			0b00001101	/*光标关*/
#define BLINK_ON			0b00001111	/*光标闪烁开*/
#define BLINK_OFF			0b00001110	/*光标闪烁关*/

/*光标或显示移位*/
#define CUR_SHIFT_L		0b00010000	/*光标左移*/
#define CUR_SHIFT_R		0b00010100	/*光标右移*/
#define DISP_SHIFT_L		0b00011000	/*显示左移*/
#define DISP_SHIFT_R		0b00011100	/*显示右移*/


/*工作模式设置*/
#define LCD_MODE_STD		0x38		/*1602标准工作模式：8位数据传送，2行显示，字符点阵5*7*/


/*字符发生器RAM地址设置*/
#define SET_ADDR_CGRAM			0x40	/*设置CGRAM地址*/

/*数据存储器地址设置*/
#define SET_ADDR_DDRAM			0x80	/*设置DDRAM地址*/

/*自定义字符*/
#define USER_CHAR1				0x00/*自定义字符1:年*/
#define USER_CHAR2				0x01/*自定义字符2:月*/
#define USER_CHAR3				0x02/*自定义字符3:日*/
#define USER_CHAR4				0x03/*自定义字符4:￥*/
#define USER_CHAR5				0x04/*自定义字符5:元*/
#define USER_CHAR6				0x05/*自定义字符6:℃*/
#define USER_CHAR7				0x06/*自定义字符7:↑*/
#define USER_CHAR8				0x07/*自定义字符8:小喇叭图标*/

/* 函数原型*/
void LCD_init(void)			;/*初始化*/
void wait_until_LCDready(void)	;/*检测忙标志，忙则等待*/
void LCD_wrcmd(unsigned char cmd)		;/*写入控制命令*/
void LCD_setxy(char x,char y)	;/*设定显示位置，行x=1/2,列y=1~16的任意整数*/
void LCD_wrchar(char str)		;/*写入要显示的字符*/
void LCD_wrstr(const rom char *s);/*写入要显示的字符串常量，该函数相当于C18 库中的putrsXLCD函数，从程序存储器写一个字符串到LCD*/
void LCD_wrul(unsigned long num);/*写入要显示的无符号长整型数*/
void LCD_wrlval(unsigned long num,unsigned char bits,unsigned char dp);/*写入要显示的长变量*/
void CG_Write(void);/*建立自定义字符块*/


#endif
