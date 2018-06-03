#include "config.h"
#include "lcd.c"

void setup();
char kbd_getc();
const char vacio[] = "piso 1";
const char lleno[] = "piso 2";
const char completo[] = "piso 3";
void main(void) {
    char c;
    setup();
    lcd_init();
    for(;;){
        do{
            c=kbd_getc();
        }while(!c);
        if(c=='1'){
            send_byte(COMAND,0x01);
            __delay_ms(5);
            for(byte a=0;a<6;a++){
                send_byte(DATA,vacio[a]);
            }
        }
        if(c=='2'){
            send_byte(COMAND,0x01);
            __delay_ms(5);
            for(byte a=0;a<6;a++){
                send_byte(DATA,lleno[a]);
            }
        }
        if(c=='3'){
            send_byte(COMAND,0x01);
            __delay_ms(2);
            for(byte a=0;a<6;a++){
                send_byte(DATA,completo[a]);
            }
        }
        __delay_ms(250);
    }
}
void setup(){
    ADCON1 = 0x0F;
    CMCON = 0x07;
    TRISB = 0x0F;
    INTCON2bits.RBPU = 0;
}
char kbd_getc(){
    char c=0;
    LATB = 0x70;
    c = PORTBbits.RB3? (PORTBbits.RB2? (PORTBbits.RB1? (PORTBbits.RB0? 0 : 'A') : '3') : '2') : '1';
    if(c)return c;
    LATB = 0xB0;
    c = PORTBbits.RB3? (PORTBbits.RB2? (PORTBbits.RB1? (PORTBbits.RB0? 0 : 'B') : '6') : '5') : '4';
    if(c)return c;
    LATB = 0xD0;
    c = PORTBbits.RB3? (PORTBbits.RB2? (PORTBbits.RB1? (PORTBbits.RB0? 0 : 'C') : '9') : '8') : '7';
    if(c)return c;
    LATB = 0xE0;
    return c = PORTBbits.RB3? (PORTBbits.RB2? (PORTBbits.RB1? (PORTBbits.RB0? 0 : 'D') : '#') : '0') : '*';
} 

