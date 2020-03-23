
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "head_bits.h"
#include "UART_pic16f628.h"


void main(void) {
    char data_rx;
    TRISBbits.TRISB0 = 0;       //set B0 as output
    PORTBbits.RB0 = 0;
    
    UART_init();
    NOP();
    UART_printf("Hello");
    while(1){  
        data_rx = UART_read();  // the data must send alredy packetized ie \x01
        if(data_rx == 0x01){
            /*
            for(int i=0; i<30; i++){
                send_char('b');
                send_char('\n');
             
            
            }*/
            PORTBbits.RB0 =1;
            UART_printf("asd");
        }
        //if the signature is x00 every time the led is off
        if(data_rx == 0x02){
            PORTBbits.RB0 =0;
        }
    }
         
        /*
        if(data_rx ==1){
            //PORTBbits.RB0 = 1;
            UART_printf("L\ne\nd\no\nn\n");
        }
        if(data_rx == 0){
            //PORTBbits.RB0 = 0;
        }
    }*/
    
    
    
    
    //this part works fine... the rest i am not sure...
    /*
    UART_init();
    while(1){
        send_char('h');
        send_char('\n');
        send_char('o');
        send_char('\n');
        send_char('l');
        send_char('\n');
        send_char('a');
        send_char('\n');
    }
    */
    
    return;
}
