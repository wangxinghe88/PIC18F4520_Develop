#define CONFIG

#include "Delay.h"

#ifdef CONFIG
// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)
#endif

//??????1????S2????????S4?1234??S3???
//??????2??????????????P22 P7 ?? 1 VPP????
//??????3????5V J1??1-2 5V????
//????????????????????????????????
//??????????????PIC??????
//???WWW.HLMCU.COM
//QQ:121350852
//??????HL-K18 HJPIC V3.2
//?????V3.2
//???????????????????,?????????.???,???????????
//?????8×8??LED??????????????????????????10MHz?
#include <p18cxxx.h>
#include "k18.h"


/*??????????????????*/
/*???LEDDOT?????????????????????????????????????????C51???? */
const unsigned char TABLE[]={	
	0x81,0x91,0x91,0xff,0x91,0x91,0x91,0x01,0x00,
	0x91,0x92,0x94,0x0F8,0x94,0x92,0x91,0x11,0x00,
  	0x7F,0x40,0xDC,0x54,0x54,0x5C,0x43,0x7E,0x00,
  	0x1,0x1,0x1,0xFF,0x21,0x21,0x21,0x21,0x00,
};


const rom unsigned char COL_SEL_PORTA[]={0b00000000,0b00000000,0b00000000,0b00000000,0b00100000,0b00001000,0b00000100,0b00000010};
const rom unsigned char COL_SEL_PORTE[]={0b00000000,0b00000100,0b00000010,0b00000001,0b00000000,0b00000000,0b00000000,0b00000000};
/*???????????*/

void delay();

void main()
{
unsigned char i;
unsigned char time=0;
unsigned char col;
unsigned char col_start=0;/*???????????????????????????????????????*/

k18_init();/*HL-K18?????*/
PORTD=0X00;
TRISD=0X00;//??D????


while(1)
	{
	for (i=0;i<=7;i++)
 		{
 		PORTA=COL_SEL_PORTA[i];/*?????????*/
         PORTE=COL_SEL_PORTE[i];/*?????????*/
         if (i==0) COL8=1;/*?????????*/
         else COL8=0;
 		col=col_start+i;/*???????????????????????????*/
 		if (col>35) col=col-36;/*??????????????????*/
 		PORTD=TABLE[col];/*???????*/
 				
 		delay();/*??1mS*/
 		
 		if (i==0) time++;
 		if (time==10)
 			{
	 		 col_start++;
	 		 time=0;
	 		 }
 		if (col_start>35) col_start=col_start-36;/*??????????????????*/
		}
	} 
} 
 
void delay()/*??1mS*/
{
    unsigned char i;
    for(i=0;i<142;i++)
       {;}
}
