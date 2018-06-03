/*
 * File:   main.c
 * Author: ivan-
 *
 * Created on 3 de mayo de 2018, 11:41 PM
 */
#include "config.h"

unsigned char cuenta = 0;
unsigned char semaforo = 0;

void setup();
void interrupt high_priority encoder(){
    if(INTCONbits.INT0IF && INTCON2bits.INTEDG0){
        INTCONbits.INT0IF = 0;
        __delay_ms(1);
        if(PORTBbits.RB0 == PORTBbits.RB1){
            INTCON2bits.INTEDG0 = 0;
            cuenta++;
        }
    }
    else if(INTCONbits.INT0IF && !INTCON2bits.INTEDG0){
        INTCONbits.INT0IF = 0;
        __delay_ms(1);
        if(PORTBbits.RB0 == PORTBbits.RB1){
            INTCON2bits.INTEDG0 = 1;
            semaforo = 1;
        }

    }
}

void main(void) {
    setup();    
    while(1){
        if(semaforo){
            LATB = cuenta << 4;
            semaforo = 0;
        }
    }
}
void setup(){
    INTCONbits.GIEH=0;          //Desactiva el sistema global de interrupciones

    TRISB = 0x0F;
    LATB = 0x00;

    INTCONbits.INT0IF = 0;     //Pone en cero la bandera de INT1 para que no acceda
    INTCONbits.INT0IE = 1;     //Habilita la interrupcion en INT1
    
    INTCON2bits.INTEDG0 = 1;    //Detecta el flanco de bajada

    RCONbits.IPEN = 0;          //Habilita las prioridades
    
    INTCONbits.GIE = 1;        //Habilita el sistema global de interrupciones
}
