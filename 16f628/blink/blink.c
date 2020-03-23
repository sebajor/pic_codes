nclude <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#define _XTAL_FREQ 4000000      //this is the clk freq
                                //it is required for the library to make
                                //the delays

/*In order to stop the warnings change xc to the
90 version... that mus be enough
*/

void main(void) {
    TRISBbits.TRISB0 = 0;       //set B0 as output
    TRISBbits.TRISB1 = 1;       //set B1 as input
    PORTBbits.RB0 = 1;
    
    while(1){
        //implement a debouncer for B1

        if(PORTBbits.RB1==0){
            for(int i=0; i<20; i++){
                __delay_ms(5);
                }
            }
            if(PORTBbits.RB1==0){
                PORTBbits.RB0 = 1;
            }
        else{
            //this is the blinking code
            __delay_ms(1000);
            PORTBbits.RB0 = 1;      //set B0 in high
            __delay_ms(1000);
            PORTBbits.RB0 = 0;      //set B0 in low
        }
    }
    return;
}

