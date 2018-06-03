/*
*	Libreria para el mostrar el tiempo en una lcd 16x2
*	Ivan Moreno
*/
#ifndef TIME_LCD_H_
#define TIME_LCD_H_

time_t clock;	//variable para cada de reloj cada segundo
	// variables para cada mes
static const char *mTs[]={
    "Ene","Feb","Mar","Abr","May","Jun",
    "Jul","Ago","Sep","Oct","Nov","Dic"};
	//variables para cada dia
static const char *dTs[]={
	"Do","Lu","Ma","Mi","Ju","Vi","Sa"};
/*
*	Muestra el timpo, en una pantalla lcd 16x2, se necesita lcd.h
*	se necesita haber inicializado la lcd, lo hace a travez de clock 
*/
void show_time_by_clock(struct tm *);

#endif