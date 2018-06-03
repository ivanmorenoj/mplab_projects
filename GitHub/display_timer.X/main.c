/*
 * File:   main.c
 * Author: ivan
 *
 * Created on May 26, 2018, 1:46 PM
 */
#include "config.h"
#define TL  0x58
#define TH  0x9E

const unsigned char dectoDy[] =
{0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0x88,0x03,0xC6,0xA1,0x86,0x8E};
const unsigned char latval[] =
{0x7F,0xBF,0xFE,0xFD};

unsigned int count=0;
unsigned char count_t=0;
unsigned char numDisplay[4];
bit flag_t;

void setup();
void ntan(unsigned char * ptr,unsigned int num,unsigned char len);
void wait_timer(unsigned char);
void show_count(unsigned char *);

void interrupt high_priority ISR(){
  if(INTCONbits.TMR0IF){
    TMR0L =  TL;
    TMR0H =  TH;
    INTCONbits.TMR0IF = 0;
    flag_t = 1;
    if(++count_t>199){
        count_t = 0;
        if(++count>9999)
          count = 0;
    }
  }
}
void main(void) {
    setup();
    for(;;){
      ntan(numDisplay,count,4);
      show_count(numDisplay);
    }
}

void setup(){
  INTCONbits.GIEH=0;         //Desactiva el sistema global de interrupciones

  ADCON1 = 0x0F;
  CMCON = 0x07;

  TRISD = 0x00;
  TRISC = 0b00111100;

  T0CON = 0b10001000;        //Configura el timer0

  INTCONbits.TMR0IF = 0;     //Pone en cero la bandera de TMR0 para que no acceda
  INTCONbits.TMR0IE = 1;     //Habilita la interrupcion en TMR0
  INTCON2bits.TMR0IP = 1;    //Alta prioridad

  RCONbits.IPEN = 1;          //Habilita las prioridades
  flag_t = 1;

  INTCONbits.GIEL = 0;        //desabilita las interrupciones de baja prioridad
  INTCONbits.GIEH = 1;        //Habilita el sistema global de interrupciones

}
void ntan(unsigned char * ptr,unsigned int num,unsigned char len){
    unsigned char index = 0;
    for(;len>0;*(ptr + --len)=0);
    for(;num>9;*(ptr + index++) = num%10,num/=10);
    *(ptr + index) = num%10;
}

void wait_timer(unsigned char n){
  for(;n;n--){
    while(!flag_t);
    flag_t = 0;
  }
}
void show_count(unsigned char *ptr){
  for(unsigned char i = 0;i<4;++i){
    LATC = *(latval + i);
    LATD = *(dectoDy + *(ptr + i));
    wait_timer(1);
  }
}
