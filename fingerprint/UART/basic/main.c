/*
 * File:   main.c
 * Author: seba
 *
 * Created on June 30, 2020, 1:24 AM
 */


#include "head.h"
#include "uart_lib.h"

void main(void) {
    unsigned char rx_data;
    TRISBbits.TRISB1 = 0;
    UART_init();
    UART_printf("Hello\r\n");    
    while(1){
        rx_data = UART_read();
        if(rx_data=='1'){
            PORTBbits.RB1 = 1;
            UART_write(rx_data);
            UART_write(0x0D); //carriage retrun ascii
        }
        if(rx_data=='0'){
            PORTBbits.RB1= 0;
            UART_write(rx_data);
            UART_write(0x0D); //carriage retrun ascii
        }
    }
    return;
}
