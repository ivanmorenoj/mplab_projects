#include "config.h"
#include "lcd.c"

byte animation[3][8] = {
 {0b01110,0b10001,0b01110,0b10101,0b01110,0b00100,0b01010,0b10001},
 {0b01110,0b10001,0b01110,0b00100,0b11111,0b00100,0b01010,0b01010},
 {0b01110,0b10001,0b01110,0b00100,0b01110,0b10101,0b00100,0b01110}};

void main(void) {
    ADCON1 = 0x0F;  //configura los bits para
    CMCON = 0x07;
    
    byte my_name[] = "Ivan  Moreno";
    byte i;
    lcd_init();
    lcd_gotoxy(3,1);
    for(i=0;i<12;i++)
        send_byte(DATA,my_name[i]);
    set_sgram_byte(0,animation[1]);
    lcd_gotoxy(1,2);
    for (i = 0; i < 0x10; i++)
        send_byte(DATA,0);
    for(;;){
        for (i = 0; i < 3; i++){
            for(int j=0;j<500;__delay_ms(1),++j);
            set_sgram_byte(0,animation[i]);
        }
    }
}
