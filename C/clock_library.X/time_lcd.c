#include <stdio.h>
#include <time.h>
#include "config.h"
#include "lcd.h"
#include "time_lcd.h"

void show_time_by_clock(struct tm * timer){
    timer = localtime(&clock);	//se da valores a la estructura a partir de clock
    printf("\a    %02d:%02d:%02d\n %s %02d %s %d",timer->tm_hour,timer->tm_min,timer->tm_sec,
            dTs[timer->tm_wday],timer->tm_mday,mTs[timer->tm_mon],timer->tm_year+1900);
    //	Se impreme en el formato especificado y se guarda en buf
}