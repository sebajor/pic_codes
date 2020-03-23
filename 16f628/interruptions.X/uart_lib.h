void UART_init(){
    TRISBbits.TRISB1 = 1;   //set B1 as 1 (TX)
    TRISBbits.TRISB2 = 1;   //set B2 as 1 (RX)  REVIEW!!!!!
    //register TXSTA is transmit status and control register
    
    //TX configuration
    TXSTAbits.SYNC = 0;     //UART instead of USART
    TXSTAbits.TX9 = 0;      //8 bit communication
    TXSTAbits.BRGH = 1;     //high speed communication
    SPBRG = 25;             // speed 9600 kBaud
    RCSTAbits.SPEN = 1;     //enable the serial function of the registers
    TXSTAbits.TXEN = 1;     //enable transmission
 
    
    //RX configuration
    RCSTAbits.CREN = 1;     //continue receiving on
}

void send_char(unsigned char dat){
    TXREG = dat;
    while(TXSTAbits.TRMT==0){};
    /*We have a shift reg TSR, it is loaded using
     *the reg TXREG, when the transfer to TSR is ready
     *the TRMT is raised and the UART communication occurs.
     */
}

void UART_printf(unsigned char* array){
    while(*array != 0x00){
        send_char(*array);
        array ++;
    }
}

char UART_read(void){
    /*PIR1 reg handles the interruptions
    There is a shift reg RSR, when is full the RCIF raise up
    this indicate that data is in transfer to the register RCREG*/
    if(PIR1bits.RCIF==1){
        return RCREG;
    }           
    else{
        return 0;
    }
}
