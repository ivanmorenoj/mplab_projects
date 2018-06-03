#include "config.h"
#include "lcd.h"

static void send_nibble(byte comand,byte data){    // envia el nibble bajo del puerto
    RS = comand;  NOP();                    //si es 0 la comand_lcd si no data_lcd
    ENABLE = 1;   NOP();                    //se establece 1 el enable
    output_lat(data);  NOP();               //saca los datos por el puerto antes definido
    ENABLE = 0;                             
    for(byte i=0;i<20;i++) NOP();           //se coloca una pausa
}
void send_byte(byte comand,byte data){//envia solo el nibble bajo
#ifdef LOW_NIBBLE
    send_nibble(comand,data>>4);    // desplaza los 4 bits del nibble alto al bajo y los envia
    send_nibble(comand,data);       //envia el nibble bajo del puerto 
#else
    send_nibble(comand,data);
    send_nibble(comand,data<<4);
#endif
}
void set_sgram_byte(byte dir,byte *ptr){    //envia un caracter a la sgram, dir 0-7
    dir <<= 3;                              //se recorre 3 bits a la izquierda
    dir &= 0x38;                            //solo se perimten los bits<5:3>
    send_byte(COMAND, 0x40 | dir);          //or para poder establecer el comando
    for(byte i=0; i<8; i++)                      
       send_byte(DATA, *ptr++);             //se envia el contenido del apuntador
}
void lcd_gotoxy(byte x, byte y){    //va a la posicion x,y de la lcd
   byte dir = y!=1? 0x40:0;         //0x40 para la segunda linea 0 para la primera
   dir += x-1;                      //se suma la posicion x
   send_byte(COMAND,0x80|dir);      //0x80 para establecer un comado de direccion
}
void lcd_init(){   //Rutina de inicializacion de la lcd se llama antes d epoder usarla 
    byte i;                                 //variable auxiliar
    set_tris_port();                        //establece e/s del puerto
    TRISENABLE  = TRISRS = 0;               //establece como salida enable y rs
    ENABLE = RS = 0;                        //inicializa en 0 el valor de enable y rs
    output_lat(0x00);                       //establece en 0 el puerto
    __delay_ms(15);                         
    for (i = 0; i < 3;__delay_ms(5), ++i)   //ciclo de 3 veces con un delay de 5ms por ciclo
        send_nibble(COMAND,3);              //envia en forma de comando el 3
    send_nibble(COMAND,2);                  //envia en forma de comando el 2
    __delay_ms(5); 
    for (i = 0; i < 4; __delay_ms(5),++i)   //ciclo de 4 veces con pausas de 5ms 
        send_byte(COMAND,init_str[i]);      //envia la cadena de inicializacion
    __delay_ms(1); 
}
void putch(char c){
    switch(c){
        case '\a':  //primera posicion 
            lcd_gotoxy(1,1);    break;
        case '\f':  //limpiar pantalla y cursor home
            send_byte(COMAND,1);    
            __delay_ms(2);      break;
        case '\n':  //mover la posicion a 1,2
            lcd_gotoxy(1,2);    break;
        default:
            send_byte(DATA,c); //poner un dato
    }
}
