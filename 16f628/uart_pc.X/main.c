/*
 * File:   main.c
 * Author: seba
 *
 * Created on March 21, 2020, 11:13 PM
 */


#include <xc.h>
#include "bit_head.h"
#include "uart_lib.h"



void main(void) {
    char data_rx;
    UART_init();
    NOP();
    UART_printf("Hello\n\r");
    while (1) {
        data_rx = UART_read(); // the data must send alredy packetized ie \x01
        if (data_rx == 0x01) {
            UART_printf("asd\n\r");
        }
        //if the signature is x00 every time the led is off
        if (data_rx == 0x02) {
            UART_printf("quecosasno\n\r");
        }
    }
    return; 
}
