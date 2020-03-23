/*
 * File:   main.c
 * Author: seba
 *
 * Created on March 22, 2020, 5:13 PM
 */


#include <xc.h>
#include <pic16f628a.h>
#include "bits_head.h"
#include "uart_lib.h"

/*This micro has 10 interruptions
 * here we use the external b0 interruption
 *tmr0 overflow interruption.
 */

int counter = 0;

void interrupt ISR(){
    if(INTCONbits.T0IF){
        //check if the interrupt is trow by tmr0
        INTCONbits.T0IF = 0;    //we have to reset the flag 
        counter +=1;
        if(counter ==16){
            PORTBbits.RB5 = ~PORTBbits.RB5;
            counter = 0;
            }        
        }
        
        
    
    if(INTCONbits.INTF){
        //check if the interruption is trow by b0
        INTCONbits.INTF = 0;
        UART_printf("Hello\r\n");
    }   
 }


void main(void) {
    
    TRISBbits.TRISB5 = 0; // set b5 as output
    PORTBbits.RB5 = 0;
    
    TRISBbits.TRISB0 = 1; //should i set as an input?
    
    
    OPTION_REGbits.T0CS = 0;    //clk source for the tmr0 to internal ckl cycle, check!!!
    OPTION_REGbits.T0SE = 1;    //increment in the rising edge
    OPTION_REGbits.PSA = 0;     //select the prescaler to tmrs0 instead of WDT
    //set the prescaler value 111---> 1:256
    OPTION_REGbits.PS0 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;
    
    
    INTCONbits.T0IE = 1;    //allows the tmr0 interruption
    INTCONbits.INTE = 1;    //allows external interruptino in b0
    
    INTCONbits.T0IF = 0;    //rest the overflow flag for tmr0
    INTCONbits.INTF = 0;    //rest flag for intb0
    
    
    
    INTCONbits.GIE = 1;     //allows all the set interruptions
    /*When a overflow occurs in the tmr0 the bit T0IF is raised
     * the flag must be clean by software
     * in the same way INTF is raised if there is an interrupt
     * by the b0
     */
    
    
    
    ei();   //xc function, allows interruptions, di disble the interruptions..
    
    char data_rx;
    UART_init();
    NOP();
    while(1){
        data_rx = UART_read();
        if(data_rx==0x01){
            UART_printf("a\n");
        }
    }
    
    
    return;
}
