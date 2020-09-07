#ifndef __I2C1_LIB__
#define __I2C1_LIB__

#include <xc.h>

//bit ports of i2c
#define SCL PORTCbits.RC3       //serial clock
#define SDA PORTCbits.RC4       //serial data

#define SCL_tris TRISCbits.TRISC3
#define SDA_tris TRISCbits.TRISC4

//functions declaration



//functions
void i2c_init(){
    SDA_tris = 1;   //SDA configured as input
    SCL_tris = 1;   //SCL configured as input
    
    
    /*
    SSPSTATbits.SMP = 1; //standard speed
    SSPSTATbits.CKE = 0; //we dont use SMBUS
    SSPSTATbits.P = 0;   //must be clear at the initialization
    SSPSTATbits.S = 0;   //must be clear at the initialization
    SSPSTATbits.R_W = 0; //no tranmission in progress
    SSPSTATbits.BF = 0  //the buffer is empty 
    */
    //this could be shorted as 
    SSP1STAT = 0x80;
    SSP1CON1 = 0x08;
    SSP1CON2 = 0x00;
    SSP1ADD  = 0x03;
    SSP1CON1bits.SSPEN = 0;
}


unsigned char i2c_line_status(){
    //if((SSP1CON2&0b00011111)|| SSP1STATbits.R_W){
    if(SSP1STATbits.R_W){
        //busy state
        return 1;   
    }
    else{
        //idle state
        return 0;
    }
}

unsigned char i2c_start(){
    //try to send a start condition
    //1 : busy line
    //0 : start signal sent
    unsigned char state = i2c_line_status();
    if(state){
        return 1;
    }
    SSP1CON2bits.SEN = 1;
    return 0;   
}


unsigned char i2c_restart(){
    //try to set a
    //repeated start condition
    //1 : busy line
    //0 : repeated start signal enabled
    unsigned char state = i2c_line_status();
    if(state){
        return 1;
    }
    SSP1CON2bits.RSEN = 1;
    return 0;   
}

void i2c_wait(){
    //infinite loop waiting for a free i2c bus
    //use it with carefulness!!!
    
    unsigned char status;
    do{
        status = i2c_line_status();
    } while(status);
}

unsigned char i2c_stop(){
    //try to send a stop condition
    unsigned char state = i2c_line_status();
    if(state){
        return 1;
    }
    SSP1CON2bits.PEN = 1;
    return 0;
}

unsigned char i2c_send_byte(unsigned char data){
    //sends a byte; returns the acknowledge status
    //you had to have started the transmission
    //when you select a slave address the last bit in data
    //says if you are attempting to read or write
    //0x01 --> read and 0x00 --> write
    
    unsigned char status;
    do{
        status = i2c_line_status();
    } while(status);
    SSP1BUF = data;
    return SSP1CON2bits.ACKSTAT;    
}


unsigned char i2c_recive_byte(){
    unsigned char status;
    do{
        status = i2c_line_status();
    } while(status);
    SSP1CON2bits.RCEN = 1;   //reinitialize the i2c communication;
                            //previously you had to have send the addr
                            //of the slave.
    do{
        status = i2c_line_status();
    } while(status);
    unsigned char recv = SSP1BUF;    
    do{
        status = i2c_line_status();
    } while(status);
    
    SSP1CON2bits.ACKDT = 1;  //acknowledge... check the data says that is 0 to ack
    SSP1CON2bits.ACKEN = 1;  //enable send the acknowledge to the slave
                            //and ended the communication;
    return recv;
}   
#endif