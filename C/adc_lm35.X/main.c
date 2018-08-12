/*
 * File:   main.c
 * Author: ivan-
 *
 * Created on 28 de mayo de 2018, 01:20 AM
 */


#include "config.h"

void setup();


void main(void) {
    setup();
    unsigned int val;
    //unsigned char numptr[4];
    for(;;){
        ADCON0bits.GO = 1;
        while(!ADCON0bits.GO);
        val = ADRESL | ADRESH<<8;
        LATB = ADRESL>>1;
        //ntan(numptr,val>>1,4);
        //for(char val = 100; val ;val--);
        //    show_count(numptr);
    }
}
void setup(){
    TRISD = 0x00;
    TRISC = 0b00111100;
    ADCON0 = 0b00000001;
    ADCON1 = 0b00001110;
    ADCON2 = 0b10111111; 
    LATC = 0x7F;
}
