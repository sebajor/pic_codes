/*
 * File:   hello.c
 * Author: seba
 *
 * Created on June 29, 2020, 2:52 AM
 */


#include "head.h"
#include "lcd.h"
//pic16f877a to test proteus

void main(void) {
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 1;
    //in order to use A0,A1,A7,A6 in lcd module as digital outputs
    //first we must enable the digital output (they are analog by default)
    ADCON1bits.PCFG = 0B0111; 
    
    __delay_ms(20);
    LCD_init();
    //__delay_ms(10);
    //LCD_clear();
    LCD_FIRST();
    LCD_data('a');
    //LCD_data('a');
    //LCD_data('a');
    //LCD_printf('Hello World!');
    //LCD_printf("Hello World!");
    while(1){
        if(PORTBbits.RB2){
            PORTBbits.RB1 = 1;
            LCD_clear();
            LCD_printf("Hello");
            //LCD_data('b');
            //LCD_printf('Hello');
        }
        else{
            PORTBbits.RB1=0;
        }
        PORTBbits.RB0 = 1;
        __delay_ms(100);
        PORTBbits.RB0 = 0;
        __delay_ms(100);
    }
    
    return;
}
