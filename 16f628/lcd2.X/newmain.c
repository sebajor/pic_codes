/*
 * File:   newmain.c
 * Author: seba
 *
 * Created on June 23, 2020, 11:45 PM
 */


#include <xc.h>
#include "lcd2.h"
#include "lcd2_lib.h"

void main(void) {
    LCD_init();
    LCD_clear();
    LCD_FIRST();
    LCD_printf("Hello World!");
    
    while(1){
        
    }
    return;
}
