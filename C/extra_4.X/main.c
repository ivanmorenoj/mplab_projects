/*
 * File:   main.c
 * Author: ivan-
 *
 * Created on 11 de junio de 2018, 08:20 AM
 */


#include "config.h"
#include "lcd.h"

void main(void) {
    ADCON1 = 0x0F;
    CMCON = 0x07;
    PORTD = 0xFF;
    lcd_init();
    for(;;){
        
    }
}
