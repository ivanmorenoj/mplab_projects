/*
*   Libreria para el manejo de una lcd 16x2 a 4 bits
*   Ivan Moreno
*/
#ifndef LCD_H_
#define LCD_H_

#define ENABLE          LATCbits.LC0    //pin de enable 
#define TRISENABLE      TRISCbits.RC0   //pin de tris enable
#define RS              LATCbits.LC1    //pin de rs
#define TRISRS          TRISCbits.RC1   //tris de rs

#define output_lat(x)   LATD = 0x0F & x     //salida de dato low nibble LATD
#define set_tris_port() TRISD = 0xF0        //Tris del puerto

#define COMAND  0                           //0 para modo comando
#define DATA    1                           //1´para modo dato 

typedef unsigned char byte; //renombra la variable unsigned char como byte

unsigned const byte init_str[4] = {0x28, 0xc, 0x1, 0x6};
/* 
*   0x28 --- Display a 4 bits con 2 lineas
*   0xc  --- Display on,subrrallado off, parpadeo apagado
*   0x1  --- limpiar el display
*   0x6  --- incremento,display shift off
*/

static void send_nibble(byte,byte);    // envia el nibble bajo del puerto

void send_byte(byte,byte);//envia solo el nibble bajo
void set_sgram_byte(byte,byte *);    //envia un caracter a la sgram, dir 0-7
void lcd_gotoxy(byte,byte);    //va a la posicion x,y de la lcd
void lcd_init();   //Rutina de inicializacion de la lcd se llama antes d epoder usarla 

/*
*   Funcion para el manejo de printf
*   \a sirve para establecer el cursor en la posicion 1,1
*   \f sirve para limpiar y establecer el cursor en la posicion 1,1
*   \n sirve para establece el cursor en la posicion 1,2
*   si no hay ninguna de las anteriores se establece el caracter 
*/
void putch(char);

#endif