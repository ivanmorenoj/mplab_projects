#include "config.h"
////
#define vT0L  0x78
#define vT0H  0xEC

unsigned int count=9950;
bit flag_t;
//
void setup();
void num_to_arr_num(unsigned char * ptr,unsigned int num,unsigned char len);
inline void clrf_ptr(unsigned char * ptr,unsigned char len,unsigned char v);
void wait_timer(unsigned char);
void show_count(unsigned char *);
inline unsigned char dec_to_disp(unsigned char num);
inline unsigned char select_disp(unsigned char dig);
//
void interrupt high_priority ISR(){
  if(PIR1bits.TMR1IF){
    TMR1H |= 0x80;
    PIR1bits.TMR1IF = 0;
    if(++count>9999)
        count=0;
  }
  if(INTCONbits.TMR0IF){
    TMR0L =  vT0L;
    TMR0H =  vT0H;
    INTCONbits.TMR0IF = 0;
    flag_t = 1;
  }
}
void main(void) {
    setup();
    unsigned char Display[8];
    for(;;){
      num_to_arr_num(Display,count,8);
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
  TMR1L = 0;
}
inline void clrf_ptr(unsigned char * ptr,unsigned char len,unsigned char v){
    while(--len)  *(ptr + len) = v;
}
void num_to_arr_num(unsigned char * ptr,unsigned int num,unsigned char len){
    for(clrf_ptr(ptr,len,11);num>9;*ptr++ = num%10,num/=10);
    *ptr = num%10;
}
void wait_timer(unsigned char n){
  for(;n;n--){
    while(!flag_t)  NOP();
    flag_t = 0;
  }
}
void show_count(unsigned char *ptr){
  for(unsigned char i = 0;i<8;i++){
    LATB = 0xFF;
    LATD = dec_to_disp(*ptr++);
    LATB = select_disp(i);
    wait_timer(1);
  }
}
inline unsigned char select_disp(unsigned char dig){
  return (unsigned char)~(1<<dig); //0-7
}
inline unsigned char dec_to_disp(unsigned char num){
  return *((unsigned char *)"\xC0\xF9\xA4\xB0\x99\x92\x82\xF8\x80\x98\xBF\xFF" + num);
}
