/*
*   Libreria para el manejo de una lcd 16x2 a 4 bits
*   Ivan Moreno
*/
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
void send_nibble(byte comand,byte data){    // envia el nibble bajo del puerto
    RS = comand;  NOP();                    //si es 0 la comand_lcd si no data_lcd
    ENABLE = 1;   NOP();                    //se establece 1 el enable
    output_lat(data);  NOP();               //saca los datos por el puerto antes definido
    ENABLE = 0;                             
    for(byte i=0;i<20;i++) NOP();           //se coloca una pausa
}
void send_byte(byte comand,byte data){//envia solo el nibble bajo
    send_nibble(comand,data>>4);    // desplaza los 4 bits del nibble alto al bajo y los envia
    send_nibble(comand,data);       //envia el nibble bajo del puerto 
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

