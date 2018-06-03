/*
 * File:   main.c
 * Author: ivan-
 *
 * Created on 28 de mayo de 2018, 01:20 AM
 */


#include "config.h"

const unsigned char dectoDy[] =
{0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0x88,0x03,0xC6,0xA1,0x86,0x8E};
const unsigned char latval[] =
{0x7F,0xBF,0xFE,0xFD};

void setup();
void show_count(unsigned char *ptr);
void ntan(unsigned char * ptr,unsigned int num,unsigned char len);

void main(void) {
    setup();
    unsigned int val;
    unsigned char numptr[4];
    for(;;){
        ADCON0bits.GO = 1;
        while(!ADCON0bits.GO);
        val = ADRESL | ADRESH<<8;
        ntan(numptr,val>>1,4);
        for(char val = 100; val ;val--);
            show_count(numptr);
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
void show_count(unsigned char *ptr){
  for(unsigned char i = 0;i<4;++i){
    LATC = *(latval + i);
    LATD = *(dectoDy + *(ptr + i));
    __delay_ms(5);
  }
}
void ntan(unsigned char * ptr,unsigned int num,unsigned char len){
    unsigned char index = 0;
    for(;len>0;*(ptr + --len)=0);
    for(;num>9;*(ptr + index++) = num%10,num/=10);
    *(ptr + index) = num%10;
}