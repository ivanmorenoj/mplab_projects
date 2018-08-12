/*
 * File:   main.c
 * Author: ivan-
 *
 * Created on 11 de junio de 2018, 08:05 AM
 */


#include "config.h"

void main(void) {
    ADCON1 = 0x0F;
    CMCON = 0x07;
    TRISA = 0;
    TRISB = 0xFF;
    TRISD = 0x00;
    LATD = 0;
    char a= 0;
    for(;;){
        while(PORTBbits.RB0)
            __delay_ms(1);
        __delay_ms(200);
        LATD = ++a;
        if(a<50)
            LATA = 0x01;
        else if(a<70)
            LATA = 0x02;
        else
            LATA = 0x04;
            
    }
}
