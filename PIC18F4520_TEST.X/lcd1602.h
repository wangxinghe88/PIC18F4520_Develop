/*********************************************************************
 *
 *                           LCD1602.H
 *
 *********************************************************************
 * �ļ���: LCD1602.H
 ********************************************************************/
#ifndef __LCD1602_H
#define __LCD1602_H


/*��Ƭ����LCD1602���������߶���*/
#define LCD_DATA      PORTD
#define TRIS_LCD_DATA TRISD
#define LCD_BUSY  PORTDbits.RD7


#define LCD_RS   PORTAbits.RA2   		/* PORT for RS */
#define TRIS_LCD_RS  DDRAbits.RA2    	/* TRIS for RS */

#define LCD_RW   PORTAbits.RA3   		/* PORT for RW */
#define TRIS_LCD_RW  DDRAbits.RA3    	/* TRIS for RW */

#define LCD_EN    PORTAbits.RA5   		/* PORT for EN */
#define TRIS_LCD_EN   DDRAbits.RA5    	/* TRIS for EN */


/*-------------------1602Һ�������-------------------*/

/*��ʼ������*/
#define DISP_CLR			0b00000001	/*����ʾ,��긴λ����һ����(��ַ00H��*/
#define CUR_HOME			0b00000010	/*��긴λ����귵�ص���һ����*/

/*������ʾģʽ����*/
#define CUR_AUTO_R			0b00000110	/*���ù�������ֲ�����Զ�����*/
#define CUR_AUTO_L			0b00000100	/*���ù�������ֲ�����Զ�����*/
#define DISP_AUTO_R		0b00000111 	/*������ʾ�����ֲ�����Զ�����*/
#define DISP_AUTO_L		0x00000101 	/*������ʾ�����ֲ�����Զ�����*/

/*��ʾ���ؿ���*/
#define DISP_ON			0b00001111	/*��ʾ��*/
#define DISP_OFF			0b00001011	/*��ʾ��*/
#define CUR_ON			0b00001111	/*��꿪*/
#define CUR_OFF			0b00001101	/*����*/
#define BLINK_ON			0b00001111	/*�����˸��*/
#define BLINK_OFF			0b00001110	/*�����˸��*/

/*������ʾ��λ*/
#define CUR_SHIFT_L		0b00010000	/*�������*/
#define CUR_SHIFT_R		0b00010100	/*�������*/
#define DISP_SHIFT_L		0b00011000	/*��ʾ����*/
#define DISP_SHIFT_R		0b00011100	/*��ʾ����*/


/*����ģʽ����*/
#define LCD_MODE_STD		0x38		/*1602��׼����ģʽ��8λ���ݴ��ͣ�2����ʾ���ַ�����5*7*/


/*�ַ�������RAM��ַ����*/
#define SET_ADDR_CGRAM			0x40	/*����CGRAM��ַ*/

/*���ݴ洢����ַ����*/
#define SET_ADDR_DDRAM			0x80	/*����DDRAM��ַ*/

/*�Զ����ַ�*/
#define USER_CHAR1				0x00/*�Զ����ַ�1:��*/
#define USER_CHAR2				0x01/*�Զ����ַ�2:��*/
#define USER_CHAR3				0x02/*�Զ����ַ�3:��*/
#define USER_CHAR4				0x03/*�Զ����ַ�4:��*/
#define USER_CHAR5				0x04/*�Զ����ַ�5:Ԫ*/
#define USER_CHAR6				0x05/*�Զ����ַ�6:��*/
#define USER_CHAR7				0x06/*�Զ����ַ�7:��*/
#define USER_CHAR8				0x07/*�Զ����ַ�8:С����ͼ��*/

/* ����ԭ��*/
void LCD_init(void)			;/*��ʼ��*/
void wait_until_LCDready(void)	;/*���æ��־��æ��ȴ�*/
void LCD_wrcmd(unsigned char cmd)		;/*д���������*/
void LCD_setxy(char x,char y)	;/*�趨��ʾλ�ã���x=1/2,��y=1~16����������*/
void LCD_wrchar(char str)		;/*д��Ҫ��ʾ���ַ�*/
void LCD_wrstr(const rom char *s);/*д��Ҫ��ʾ���ַ����������ú����൱��C18 ���е�putrsXLCD�������ӳ���洢��дһ���ַ�����LCD*/
void LCD_wrul(unsigned long num);/*д��Ҫ��ʾ���޷��ų�������*/
void LCD_wrlval(unsigned long num,unsigned char bits,unsigned char dp);/*д��Ҫ��ʾ�ĳ�����*/
void CG_Write(void);/*�����Զ����ַ���*/


#endif
