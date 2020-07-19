#ifndef __ATC24C32__
#define __ATC24C32__

#ifndef __I2C_LIB__
#include "i2c_lib.h"
#endif

void atc32_write_eeprom(unsigned char data, unsigned short addr){
    unsigned char status;
    do{
        status = i2c_start();
    } while(status);
    
    i2c_send_byte(0xa0);    //addr of the eeprom
    i2c_send_byte(addr>>8); //send the higher half of the mem addr
    i2c_send_byte(addr &0xFF); //send the lower half of the mem addr
    i2c_send_byte(data);
    i2c_stop();
}

unsigned char atc32_read_eeprom(unsigned short addr){
    unsigned char status;
    do{
        status = i2c_start();
    } while(status);
    i2c_send_byte(0xa0);
    i2c_send_byte(addr>>8); //send the higher half of the mem addr
    i2c_send_byte(addr &0xFF); //send the lower half of the mem addr
    do{
        status = i2c_restart();
    } while(status);

    unsigned char data = i2c_recive_byte();
    i2c_stop();
    
    return data;
}

#endif