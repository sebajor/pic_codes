#include "mcc_generated_files/mcc.h"
#include "i2c1_head.h"
#include "eeprom_24c32.h"

void main(void)
{
    // Initialize the device
    char eeprom_val;
    char uart_char;
    SYSTEM_Initialize();
    EUSART1_Initialize();
    i2c_init();
    while (1)
    {
        if(EUSART1_is_rx_ready()){
            uart_char = EUSART1_Read();
            if(uart_char=='w'){
                while(1){
                    if(EUSART1_is_rx_ready()){
                        break;
                    }
                }
                uart_char = EUSART1_Read();
                printf("writing eeprom\r\n");
                //now we are going to write the eeprom
                for(int i=0; i<1024; i++){
                    printf("sendig data to eemprom\r\n");
                    atc32_write_eeprom(uart_char, (unsigned short)i);
                    __delay_ms(5);
                }    
            }
            if(uart_char=='r'){
                //read the eeprom
                printf("reading eeprom\r\n");
                for(int i=0;i<1024; i++){
                    eeprom_val = atc32_read_eeprom((unsigned short) i);
                    printf("%c \r\n", eeprom_val);
                    __delay_ms(5);
                }
            }
            else{
                printf('%c', uart_char);
            }
        }       
    }
}
