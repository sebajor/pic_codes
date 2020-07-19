#ifndef __I2C_LIB__
#define __I2C_LIB__

#include <xc.h>

//bit ports of i2c
#define SCL PORTCbits.RC3       //serial clock
#define SDA PORTCbits.RC4       //serial data

#define SCL_tris TRISCbits.TRISC3
#define SDA_tris TRISCbits.TRISC4

//functions declaration

void i2c_init();


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
    SSPSTAT = 0b10000000;
    /*
    SSPCONbits.SSPM = 0b1000;   //i2c master mode running at (fosc/(4*sspadd+1)))
    SSPCONbits.SSPEN = 1;       //i2c enable--> take care about the terminations!
     */
    //this could be short, and also clears the flags of the reg
    SSPCON=0b00101000;
    SSPCON2 = 0x00;         //register full of flags, we reset all of them
    
    SSPADD = 25;              //SSPADD=(f_clk/(4*100*10**3))-1  
                              //100Kbps , in our case f_clk=10*10**6
}


unsigned char i2c_line_status(){
    if((SSPCON2&0b00011111)|| SSPSTATbits.R_W){
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
    SSPCON2bits.SEN = 1;
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
    SSPCON2bits.RSEN = 1;
    return 0;   
}

void i2c_wait(){
    //infinite loop waiting for a free i2c bus
    //use it with careful
    
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
    SSPCON2bits.PEN = 1;
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
    SSPBUF = data;
    return SSPCON2bits.ACKSTAT;    
}


unsigned char i2c_recive_byte(){
    unsigned char status;
    do{
        status = i2c_line_status();
    } while(status);
    SSPCON2bits.RCEN = 1;   //reinitialize the i2c communication;
                            //previously you had to have send the addr
                            //of the slave.
    do{
        status = i2c_line_status();
    } while(status);
    unsigned char recv = SSPBUF;    
    do{
        status = i2c_line_status();
    } while(status);
    
    SSPCON2bits.ACKDT = 1;  //acknowledge... check the data says that is 0 to ack
    SSPCON2bits.ACKEN = 1;  //enable send the acknowledge to the slave
                            //and ended the communication;
    return recv;
}   
#endif