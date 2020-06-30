#ifndef __UART_LIB__
#define __UART_LIB__


//in pic16f877a the rx is in RC7 and tx is in RC6
#define RX_tris TRISCbits.TRISC7
#define TX_tris TRISCbits.TRISC6


//functions declaration
void UART_init();
void UART_char(unsigned char dat);
void UART_printf(unsigned char *data);
unsigned char UART_read(void);
void putch(unsigned char dat);


//functions

void UART_init(){
    RX_tris = 1;
    TX_tris = 1;
    
    //TX configuration
    TXSTAbits.SYNC = 0;     //Async operation
    TXSTAbits.TX9 = 0;      //use 8 bits instead of 9
    TXSTAbits.BRGH = 1;     //high speed communication
    SPBRG = 64;             //9600...speed, depends of the clk (check data!)
    
    RCSTAbits.SPEN = 1;     //configure RC6 and RC7 as serial pins 
    TXSTAbits.TXEN = 1;     //enable transmission
    
    //RX configuration
    RCSTAbits.RX9 = 0;      //8 bits recption
    
    RCSTAbits.CREN = 1;     //enable continuous reception
}

void UART_write(unsigned char dat){
    TXREG = dat;        //put the data in the shift register
    while(!TXSTAbits.TRMT){} //We wait until the shift reg is empty
}

void UART_printf(unsigned char *data){
    while(*data){
        UART_write(*data);
        data++;
    }
}

unsigned char UART_read(void){
    //PIR1 contains a read only flag who gives alarm of a 
    //that the receiving shift register is full, then the data
    //could be read from RCREG
    //This also could be handled using the interruption in PIE.RCIE
    if(PIR1bits.RCIF){
        return RCREG;
    }
    else{
        return 0;
    }
}

//the following functions is for debug in the mplab console 
/*
void putch(unsigned char dat){
    UART_write(dat);
}
*/

#endif