#include "config.h"

#define I0F INTCONbits.INT0IF
#define EG0 INTCON2bits.INTEDG0
#define I1F INTCON3bits.INT1IF
#define EG1 INTCON2bits.INTEDG1
#define PRES    40

byte flag=0,level=0;
char Nstep=0;
void setup();

void interrupt high_priority ext0(){
    /*byte pcl = PCL;
    byte pch = PCH;
    byte wtmp = WEREG;
    byte stmp = STATUS;
    */

    __delay_ms(1);
    if(I0F){
        I0F = 0;
        EG0 = !EG0;
        //__delay_ms();
        if(PORTBbits.RB0 != PORTBbits.RB1)
            Nstep++;
        else
            Nstep--;
    }
    if (Nstep>PRES){
        Nstep = 0;
        flag = 1;
        level = ++level & 0x0F;
    }else if(Nstep<PRES){
        Nstep = 0;
        flag = 1;
        level = --level & 0x0F;
    }
}
void main(void) {
    setup();
	for(;;){
        if(flag){
            flag = 0;
            LATB = level << 4;
            set_level(level);
            __delay_ms(250);
         }
	}

}
void setup(){
    INTCONbits.GIEH=0;          //Desactiva el sistema global de interrupciones

    TRISB = 0x0F;
    LATB = 0;

    INTCONbits.INT0IF = 0;     //Pone en cero la bandera de INT1 para que no acceda
    INTCONbits.INT0IE = 1;     //Habilita la interrupcion en INT1

    INTCON2bits.INTEDG0 = 0;    // 0 descendente, 1 ascendente

    INTCON3bits.INT1IF = 0;     //Pone en cero la bandera de INT2 para que no acceda
    INTCON3bits.INT1IE = 0;     //Habilita la interrupcion en INT2
    INTCON3bits.INT1IP = 1;     //La establece como de baja prioridad

    INTCON2bits.INTEDG2 = 1;    // 0 descendente, 1 ascendente

    RCONbits.IPEN = 1;          //Habilita las prioridades

    lcd_init();
    init_level();
    __delay_ms(100);
    INTCONbits.GIEL = 0;
    INTCONbits.GIEH = 1;        //Habilita el sistema global de interrupciones
}
