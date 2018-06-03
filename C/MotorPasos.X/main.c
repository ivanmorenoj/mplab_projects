/*
 * File:   main.c
 * Author: ivan-
 * Created on 5 de abril de 2018, 02:56 AM
 */

#include "config.h"

#define clear_output()      LATB=0
#define COMPLETE            4
#define MEDIUM              8

typedef unsigned char byte;
typedef unsigned long Lbyte;

const byte complete_step[4]={0x01,0x02,0x04,0x08};
const byte medium_step[8]={0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09};

byte Step=0;

void setup();
void move_step(long,byte);
void next_step(byte,byte);
void delay(Lbyte);
void set_step(byte);
void full_turn(long);

void main(void) {
    setup();
    for(;;){
        full_turn(4096);
        for (byte i = 1; i <= 11; ++i)
            full_turn(341*i);        
    }
    return;
}
void setup(){
    TRISB = 0xF0;
    LATB = 0;
}
void delay(Lbyte t){
    while(t--)
        __delay_ms(1);
}
void next_step(byte dir,byte type){
    Step = dir? (Step>=type-1? 0 : Step+1) : (Step<=0? type-1 : Step-1);
    set_step(type);
}
void move_step(long HowMany,byte type){            
    if(HowMany>0)
        while(HowMany--)
            next_step(1,type);
    else
        while(HowMany++)
            next_step(0,type);
}
void set_step(byte type){
    LATB = 0x0F & (type==COMPLETE? complete_step[Step] : medium_step[Step]);
    __delay_ms(2);
}
void full_turn(long steps){
    move_step(steps*-1,MEDIUM);//horario
    delay(250);
    move_step(steps,MEDIUM);
    delay(250);
}