#include <stdio.h>
#include <time.h>
#include "config.h"
#include "lcd.h"
#include "time_lcd.h"

void main (void){
    lcd_init();
    //inicializacion del timer
    struct tm tp = {50,11,13,4,4,118,0,0,0};// = localtime(NULL);
    //tp->tm_sec  =50;            //segundos 0-59
    //tp->tm_min  =55;            //minutos 0-59
    //tp->tm_hour =23;            //horas 0-23
    //tp->tm_mday =22;            //dia del mes 1-31
    //tp->tm_mon  =3;             //mes 0-11
    //tp->tm_year =2018-1900;     //aos desde 1900
    //tp->tm_wday;              //dia de la semana (0=domingo)
    //tp->tm_yday;              //dia del anio 0-365
    //tp->tm_isdst;             //horario de verano
    clock = mktime(&tp);
    
    for(;;){
        show_time_by_clock(&tp);
        clock++;
        __delay_ms(1000);
    }
}
