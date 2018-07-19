
#include <p18f4520.h>
#include "k18.h"
#include "lcd1602.h"
void MSDelay(unsigned int itime);
#define Dsensor PORTCbits.RC1
#define buzzer PORTBbits.RB7

void main(void)
{
    TRISCbits.TRISC1 = 1;
    TRISBbits.TRISB7 = 0;
    while(1)
    {
           while(Dsensor != 1)
       {
           buzzer = 0;
           MSDelay(2);
           buzzer = 1;
           MSDelay(2);
       }
    }

}

void MSDelay(unsigned int itime)
{
    unsigned int i; unsigned int j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 15; j++);
}