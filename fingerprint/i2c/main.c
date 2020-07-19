/*
 * File:   main.c
 * Author: seba
 *
 * Created on 18 de julio de 2020, 0:50
 */


#include "bit_conf.h"
#include "i2c_lib.h"
#include "eeprom_atc24c32.h"


int main(){
    TRISBbits.TRISB0 = 1; //B0 as input
    TRISBbits.TRISB1 = 1; //B1 as input 
    TRISBbits.TRISB2 = 0; //B2 as output
    TRISBbits.TRISB3 = 0; //B3 as output
    char flag = 0;
    char led3=0;
    i2c_init();
    __delay_ms(100);
    
    //i2c_start();
    i2c_wait();
    i2c_start();
    //led3 = i2c_send_byte(0xA0);
    //PORTBbits.RB3 = led3&0x01;
    //i2c_stop();
    //i2c_send_byte(0xBA);
    
    atc32_write_eeprom(0xAA, 0xCCDD);
    
    
    /*
    unsigned char status;
    do{
        status = i2c_line_status();
    } while(status);
    i2c_send_byte(0x44);
    */
    //i2c_send_byte(0xAB);
    //i2c_stop();
    //atc32_write_eeprom(0xAA, 0xCCDD);
    /*
    while(1){
        if(PORTBbits.RB0 && ~flag){
            atc32_write_eeprom(0x04, 0xAABB);
            flag = 1;
        }
        if(PORTBbits.RB1){
            flag = 0;
        }
    }
    */
    PORTBbits.RB2 = 1;
    while(1){}
    return 1;
}