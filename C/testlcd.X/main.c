#include "config.h"

 
#define ENABLE  LATCbits.LC0
#define RS      LATCbits.LC1

#define COMAND  0
#define DAT     1

#define _XTAL_FREQ 20000000

#include <xc.h>


unsigned const INIT_STRING[4] = {0x28, 0xc, 0x1, 0x6};
    //0x28 --- Display a 4 bits con 2 lineas
    //0xc  --- Display on,subrrallado off, parpadeo apagado
    //0x1  --- limpiar el display
    //0x6  --- incremento,display shift off

unsigned char anima[3][8] = 
{{0b01110,0b10001,0b01110,0b10101,0b01110,0b00100,0b01010,0b10001},
 {0b01110,0b10001,0b01110,0b00100,0b11111,0b00100,0b01010,0b01010},
 {0b01110,0b10001,0b01110,0b00100,0b01110,0b10101,0b00100,0b01110}
};


void setup();
void output_data(unsigned char);
void send_byte(unsigned char, unsigned char);
void send_nibble(unsigned char, unsigned char);
void dic(unsigned int t);
void lcd_init();
void set_sgram_char(unsigned char,unsigned char *);
void lcd_gotoxy(unsigned char x, unsigned char y);


void main(void) {
    setup();
    unsigned char my_name[] = "Ivan  Moreno";
    unsigned char i;
    //__delay_ms(100);
    lcd_init();
    
    lcd_gotoxy(3,1);
    for(i=0;i<12;i++)
        send_byte(DAT,my_name[i]);

    set_sgram_char(0,anima[1]);

    lcd_gotoxy(0,2);

    for (i = 0; i < 0x10; i++)
        send_byte(DAT,0);
    
    

    for(;;){
        for (i = 0; i < 3; i++){
            for(int j=0;j<500;__delay_ms(1),++j);
            set_sgram_char(0,anima[i]);
        }
        
    }
        

    return;
}
void lcd_init(){
    unsigned char i;
    output_data(0x00);
    
    __delay_ms(15);

    for (i = 0; i < 3;__delay_ms(5), ++i)
        send_nibble(COMAND,3);
    send_nibble(COMAND,2);
    
    __delay_ms(5);
    
    for (i = 0; i < 4; __delay_ms(5),++i)
        send_byte(COMAND,INIT_STRING[i]);
    __delay_ms(1);
}
void output_data(unsigned char data){
    LATD = 0x0F & data>>4; //nibble alto
    LATA = 0x0F & data;
}
void send_nibble(unsigned char comand,unsigned char data){
    ENABLE = 0;
    RS = (comand != 0);
    NOP();
    ENABLE = 1;
    NOP();
    LATD = 0x0F & data;
    NOP();
    ENABLE = 0;
    dic(20);
}
void send_byte(unsigned char comand,unsigned char data){
    send_nibble(comand,data>>4);
    send_nibble(comand,data);
}
void set_sgram_char(unsigned char dir,unsigned char *ptr){
    unsigned char i;

    dir <<= 3;
    dir &= 0x38;
    
    send_byte(COMAND, 0x40 | dir);
    for(i=0; i<8; i++)
       send_byte(DAT, *ptr++);
    
}
void setup(){
    ADCON1 = CMCON = 0x0F;
    TRISD = TRISA = 0xF0;
    TRISC = 0xFC;
    LATC = LATD = LATA = 0x00;
}
void dic(unsigned int t){
    while(t--)
        NOP();
}
void lcd_gotoxy(unsigned char x, unsigned char y)
{
   unsigned char address;
   
   address = y!=1? 0x40:0;

   address += x-1;
   send_byte(COMAND,0x80|address);
}
