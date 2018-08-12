/*
 * File:   main.c
 * Author: ivan-
 *
 * Created on 10 de junio de 2018, 11:07 PM
 */

#include "config.h"
#include "lcd.h"
#include <stdio.h>

void setup();
char kbd_getc();

void main(void) {
    setup();
    lcd_init();
    
    char c;
    for(;;){
        do{
            c=kbd_getc();
            __delay_ms(100);
        }while(!c);
        printf("\f%c",c);
    }
}
void setup(){
    ADCON1 = 0x0F;
    CMCON = 0x07;
    TRISB = 0x0F;
    //INTCON2bits.RBPU = 0;
}
char kbd_getc(){
    char c=0;
    PORTB = 0x70;
    c = PORTBbits.RB3? (PORTBbits.RB2? (PORTBbits.RB1? (PORTBbits.RB0? 0 : 'A') : '3') : '2') : '1';
    if(c)return c;
    PORTB = 0xB0;
    c = PORTBbits.RB3? (PORTBbits.RB2? (PORTBbits.RB1? (PORTBbits.RB0? 0 : 'B') : '6') : '5') : '4';
    if(c)return c;
    PORTB = 0xD0;
    c = PORTBbits.RB3? (PORTBbits.RB2? (PORTBbits.RB1? (PORTBbits.RB0? 0 : 'C') : '9') : '8') : '7';
    if(c)return c;
    PORTB = 0xE0;
    c = PORTBbits.RB3? (PORTBbits.RB2? (PORTBbits.RB1? (PORTBbits.RB0? 0 : 'D') : '#') : '0') : '*';
    return c;
} 

