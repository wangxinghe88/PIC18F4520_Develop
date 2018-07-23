#include <p18cxxx.h>
#include "k18.h"

//k18???????
void k18_init(void)
{
  ADCON1=0b00001111;                            //?????????????
  
  CMCON=0b00000111;/*???????*/
  INTCON2bits.RBPU=0;/*??B????*/

/* k18 ??????????? */

TRIS_AN=IN;  	/* AN*/


COL1=0;    			/* COL1*/
TRIS_COL1=OUT;  

COL2=0;    			/* COL2*/
TRIS_COL2=OUT; 

COL3=0;    			/* COL3*/
TRIS_COL3=OUT; 

COL4=0;    			/* COL4*/
TRIS_COL4=OUT; 

COL5=0;    			/* COL5*/
TRIS_COL5=OUT; 

COL6=0;    			/* COL6*/
TRIS_COL6=OUT; 

COL7=0;    			/* COL7*/
TRIS_COL7=OUT; 

COL8=0;    			/* COL8*/
TRIS_COL8=OUT; 

 
BZ=0;    			/* BZ*/
TRIS_BZ=OUT; 

TRIS_IR=IN;   			/* IR*/
   	
TRIS_SW0=IN; 		/* SW0*/
   	
TRIS_SW1=IN;  	/* SW1*/
    	
TRIS_SW2=IN;  	/* SW2*/
  		
TRIS_SW3=IN; 		/* SW3*/

}

