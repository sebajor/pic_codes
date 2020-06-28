#ifndef __LCD_LIB__

#include <stdlib.h>
#include <stdint.h>
#include <xc.h>


//previously you have to had defined the XTAL_FREQ


//Modify this definitions to change the pin to use
#define D4          PORTAbits.RA1
#define D5          PORTAbits.RA0
#define D6          PORTAbits.RA7
#define D7          PORTAbits.RA6
#define RS          PORTBbits.RB5       //0 means instruction, 1 means data
#define EN          PORTBbits.RB4

#define TRIS_D4     TRISAbits.TRISA1
#define TRIS_D5     TRISAbits.TRISA0
#define TRIS_D6     TRISAbits.TRISA7
#define TRIS_D7     TRISAbits.TRISA6
#define TRIS_RS     TRISBbits.TRISB5
#define TRIS_EN     TRISBbits.TRISB4


#define NO_CURSOR 0X0C
#define INCREMENT 0x06
#define FIRST_LINE 0X02
#define SECOND_LINE 0xC0
#define LCD_CLEAR   0X01


//functions instantiation

void LCD_init();
void LCD_write(unsigned char dat);
void LCD_cmd(unsigned char dat);
void LCD_data(unsigned char dat);
void LCD_clear(void);
void LCD_FIRST(void);
void LCD_SECOND(void);
void LCD_printf(unsigned char *data);


//function definitions

void LCD_init(){
    TRIS_D4 = 0;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    TRIS_EN= 0;
    TRIS_RS = 0;
    
    __delay_ms(5);
    
    LCD_cmd(0x28);
    LCD_cmd(NO_CURSOR);
    LCD_data('s');
    LCD_cmd(INCREMENT);
    LCD_data('d');
    LCD_cmd(0x80);
    __delay_ms(100);
}

void LCD_write(unsigned char dat){
    if(dat & (1<<4)) D4 = 1;    else D4 = 0;
    if(dat & (1<<5)) D5 = 1;    else D5 = 0;
    if(dat & (1<<6)) D6 = 1;    else D6 = 0;
    if(dat & (1<<7)) D7 = 1;    else D7 = 0;
    EN = 1;
    __delay_ms(6);
    EN = 0;
    __delay_ms(1);
    
    dat = (dat<<4);
    if(dat & (1<<4)) D4 = 1;    else D4 = 0;
    if(dat & (1<<5)) D5 = 1;    else D5 = 0;
    if(dat & (1<<6)) D6 = 1;    else D6 = 0;
    if(dat & (1<<7)) D7 = 1;    else D7 = 0;
    EN = 1;
    __delay_ms(6);
    EN = 0;
    __delay_ms(1);          
}

void LCD_cmd(unsigned char dat){
    RS=0;
    LCD_write(dat);
}

void LCD_data(unsigned char dat){
    RS=1;
    LCD_write(dat);
}

void LCD_clear(void){
    LCD_cmd(LCD_CLEAR);
    __delay_ms(2);
}

void LCD_FIRST(void){
    LCD_cmd(FIRST_LINE);
    __delay_ms(2);
}

void LCD_SECOND(void){
    LCD_cmd(SECOND_LINE);
    __delay_ms(2);
}

void LCD_printf(unsigned char *data){
    while(*data){
        LCD_data(*data);
        data++;
    }
}

#endif