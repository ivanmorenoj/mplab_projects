#include "config.h"
#include "lcd.c"
#include "lcd_status.c"

void main(void) {
    lcd_init();
    init_level();
	for(;;){
		for (byte i = 0; i < 16;__delay_ms(100), ++i)
			set_level(i);		
	}

}
