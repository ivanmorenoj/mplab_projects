#include "config.h"
#include "lcd.c"
#include <stdio.h>


const char monthdays[12]={31,28,31,30,31,30,31,31,30,31,30,31};
const char month[12][4]={
	{"ENE"},{"FEB"},{"MAR"},{"ABR"},{"MAY"},{"JUN"},{"JUL"},{"AGO"},{"SEP"},{"OCT"},{"NOV"},{"DIC"}
};
char DataStr[22];

typedef struct time_s{
    unsigned char 	seg;	//segundos 0-59
    unsigned char 	min;	//minutos 0-59
    unsigned char 	hour;	//horas 0-23
    unsigned char 	day;	//dias	1-30,31
    unsigned char	month;	//meses 1-12
    int 	year;	//anios desde 2000->anio bisiesto
} Time;
Time Gtime;

char LeapYear(int year){
	return year%4? 1:0;
}
void set_time(char s,char m,char h,
			  char d,char mo,int y){ //Si se coloca nada, default -> 1-1-2018 00:00:00
		Gtime.seg = s;
		Gtime.min = m;
		Gtime.hour = h;
		Gtime.day = d;
		Gtime.month = mo;
		Gtime.year = y;
}
void increment_seg(){
	if(Gtime.seg++>=59){
		Gtime.seg=0;
		if(++Gtime.min>59){
			Gtime.min=0;
			if(++Gtime.hour>23){
				Gtime.hour=0;
				if(++Gtime.day>(Gtime.month!=2? monthdays[Gtime.month-1] :28 + LeapYear(Gtime.year))){
					Gtime.day=1;
					if(++Gtime.month>12){
						Gtime.month=1;
						++Gtime.year;						
					}
				}
			}
		}
	}
}

void show_data(){
	sprintf(DataStr,"%2d:%2d:%2d %2d:%s:%d",Gtime.hour,Gtime.min,Gtime.seg,Gtime.day,month[Gtime.month-1],Gtime.year);
	lcd_gotoxy(5,1);
	for (char i = 0; i < 20; ++i){
		if(i==8)lcd_gotoxy(2,2);
		send_byte(DATA,DataStr[i]);
        increment_seg();
	}

}

void main(void) {
    lcd_init();
    set_time(59,59,23,28,2,2018);    
    for(;;){
        show_data();
        increment_seg();
        __delay_ms(1000);
    }
}