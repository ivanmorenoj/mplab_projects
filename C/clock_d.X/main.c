#include "config.h"
////
#define vT0L  0x78
#define vT0H  0xEC
#define REBOUND 100
//////////
typedef struct{
    char seg;
    char min;
    char hour;
    char blink;
} tm;
//
tm clock = {0,0,0,0};
unsigned int count;
unsigned char flagStatus;
char count_rbnd;
bit flag_t;
//
void setup();
void num_to_arr_num(unsigned char * ptr,unsigned int num,unsigned char len);
void wait_timer(unsigned char);
void show_count(unsigned char *);
void make_disp_time(unsigned char *ptr,tm * tm_ptr);
void pp_time(tm * tm_ptr);
char pp_tm(tm * tm_ptr,char type);
//
void interrupt high_priority ISR(){
  if(PIR1bits.TMR1IF){
    TMR1H |= 0x80;
    PIR1bits.TMR1IF = 0;
    if(!flagStatus)
      pp_time(&clock);
  }
  if(INTCONbits.TMR0IF){
    TMR0L =  vT0L;
    TMR0H =  vT0H;
    INTCONbits.TMR0IF = 0;
    flag_t = 1;
    ++count_rbnd;
    if(++count>499){
        count = 0;
      clock.blink = !clock.blink;
    }
  }
  if(!PORTAbits.RA1 && count_rbnd>REBOUND){
    count_rbnd = 0;
    while(!PORTAbits.RA1);
    if(!flagStatus){
      PIE1bits.TMR1IE = 0;
      flagStatus = 0x01;
    }else{
      flagStatus <<= 1;
      if(flagStatus & 0x08){
        PIE1bits.TMR1IE = 1;
        flagStatus = 0;
      }
    }
  }else if(flagStatus && !PORTAbits.RA5 && count_rbnd>REBOUND){
    count_rbnd = 0;
    pp_tm(&clock,flagStatus);
  }
}
void main(void) {
    setup();
    unsigned char Display[8];
    for(;;){
      make_disp_time(Display,&clock);
      show_count(Display);
    }
}
void setup(){
  INTCONbits.GIEH=0;         //Desactiva el sistema global de interrupciones
  ADCON1 = 0x0F;
  CMCON = 0x07;
  TRISA = 0xFF;
  TRISD = 0x00;
  TRISB = 0x00;
  LATA = LATB = 0xFF;
  T0CON = 0b10001000;        //Configura el timer0
  INTCONbits.TMR0IF = 0;     //Pone en cero la bandera de TMR0 para que no acceda
  INTCONbits.TMR0IE = 1;     //Habilita la interrupcion en TMR0
  INTCON2bits.TMR0IP = 1;    //Alta prioridad
  T1CON = 0b00001011;        //Configura el timer0
  PIR1bits.TMR1IF = 0;     //Pone en cero la bandera de TMR0 para que no acceda
  PIE1bits.TMR1IE = 1;     //Habilita la interrupcion en TMR0
  IPR1bits.TMR1IP = 1;    //Alta prioridad
  RCONbits.IPEN = 1;          //Habilita las prioridades
  INTCONbits.GIEL = 0;        //desabilita las interrupciones de baja prioridad
  INTCONbits.GIEH = 1;        //Habilita el sistema global de interrupciones
  flag_t = 1;
  flagStatus = 0;
}
void num_to_arr_num(unsigned char * ptr,unsigned int num,unsigned char len){
    for(;len;*(ptr + --len)=0);
    for(;num>9;*ptr++ = num%10,num/=10);
    *ptr = num%10;
}
void wait_timer(unsigned char n){
  for(;n;n--){
    while(!flag_t)  NOP();
    flag_t = 0;
  }
}
void show_count(unsigned char *ptr){
  const char * dectoDy = "\xC0\xF9\xA4\xB0\x99\x92\x82\xF8\x80\x98\xBF\xFF";
  for(unsigned char i = 0,a=1;i<8;a<<=1,i++){
    if(*ptr>11){
      LATD = *(dectoDy + (*ptr++ - 12)) & 0x7F;
    }else
      LATD = *(dectoDy + *ptr++) ;
    LATB = ~a;
    wait_timer(1);
  }
}
void make_disp_time(unsigned char *ptr,tm * tm_ptr){
  num_to_arr_num(ptr,tm_ptr->seg,2);
  num_to_arr_num(ptr+3,tm_ptr->min,2);
  num_to_arr_num(ptr+6,tm_ptr->hour,2);
  *(ptr + 2) = *(ptr + 5) = tm_ptr->blink? 10:11;
  if(flagStatus && tm_ptr->blink)
    for(char i = 0,j=1;j<=0x04;i+=3,j<<=1)
      if(j == flagStatus)
        for (char k = 0; k < 2; k++)
          *(ptr + i + k) +=12;
}
void pp_time(tm * tm_ptr){
  if(pp_tm(tm_ptr,1))
    if(pp_tm(tm_ptr,2))
      pp_tm(tm_ptr,4);
}
char pp_tm(tm * tm_ptr,char type){
  switch (type) {
    case 0x01:
      if(++tm_ptr->seg>59){
        tm_ptr->seg = 0;
        return 1;
      } break;
    case 0x02:
      if(++tm_ptr->min>59){
        tm_ptr->min = 0;
        return 1;
      } break;
      case 0x04:
      if(++tm_ptr->hour>23){
        tm_ptr->hour = 0;
        return 1;
      } break;
  }
  return 0;
}
