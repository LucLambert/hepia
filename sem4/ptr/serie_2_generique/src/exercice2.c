/*
 * exercice2.c
 *
 *  Created on: Mar 1, 2022
 *      Author: luclaptop
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "uart.h"
#include "lcd.h"

void wait_20ms(){
	int stop = LPC_TIM0->TC + 500000;
	while(LPC_TIM0->TC<stop){};
}


/*int main(void)
{
	LPC_TIM0->TCR = 1;			// start timer 0, default freq. with __USE_CMSIS: 25 MHz

	init_lcd();

	uint16_t w, h;
	uint16_t* im = read_bmp_file("cheval.bmp", &w, &h);

	lcd_filled_rectangle(0, 0, 239, 319, LCD_BLACK);

	long cpt=0;
	uint16_t x=0,y=0;

	while(1){
		lcd_filled_rectangle(x, y, x+w, y+h, LCD_BLACK);
		x=cpt%200;
		y=(uint16_t)(290 - 290*(fabs(sin(3.14*cpt/40))));
		display_bitmap16(im, x, y, w, h);
		cpt++;
		wait_20ms();
	}
	return 0;
}*/
